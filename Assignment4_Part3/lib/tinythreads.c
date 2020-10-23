/*
 * The code below has been developed by Johan Nordlander and Fredrik Bengtsson at LTU.
 * Part of the code has been also developed, modified and extended to ARMv8 by Wagner de Morais and Hazem Ali.
*/

#include <setjmp.h>
#include "tinythreads.h"
#include "piface.h"
#include <stdio.h>
#include <stdarg.h>
#include "rpi-interrupts.h"

#define PUTTOLDC(fmt, args...){ \
	char s[100]; \
    sprintf(s, fmt, ##args); \
    piface_putsx(s); \
}

__attribute__(( always_inline )) static inline void enable() {
  __asm volatile("cpsie i \n"); //AIF
}

__attribute__(( always_inline )) static inline void disable(){
  __asm volatile("cpsid i \n"); //AIF
}

#define DISABLE()       disable()
#define ENABLE()        enable()
#define NULL            0
#define STACKSIZE       1024
#define NTHREADS        20
#define MAXINT          0x7fffffff
#define RUN 			1
#define STOP 			0

#define SETSTACK(buf,a) *((unsigned int *)(buf)+8) = (unsigned int)(a) + STACKSIZE - 4;

struct thread_block {
    void (*function)(int);   						// code to run
    int arg;                 						// argument to the above
    thread next;             						// For use in linked lists
    jmp_buf context;         						// Machine state
    char stack[STACKSIZE];   						// Execution stack space
    unsigned int Period_Deadline;		// Absolute Period and Deadline of the thread
    unsigned int Rel_Period_Deadline;	// Relative Period and Deadline of the thread
};

struct thread_block threads[NTHREADS];
struct thread_block tasks[NTHREADS];    //used to keep track of the tasks and their info

struct thread_block initp;
struct thread_block mainp;

thread taskQ   = tasks;
thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &initp;

int initialized = 0;
int countTask = 0;

static void initialize(void) {
    int i;

    initp.Period_Deadline = MAXINT;
    initp.Rel_Period_Deadline = MAXINT;
    initp.arg = -1;
    initp.function = NULL;

    for (i=0; i<NTHREADS-1; i++)
    {
        threads[i].next = &threads[i+1];
        threads[i].Period_Deadline = MAXINT;
        threads[i].Rel_Period_Deadline = MAXINT;
        threads[i].function = NULL;
        threads[i].arg = i;

        tasks[i].next = &threads[i+1];
        tasks[i].Period_Deadline = MAXINT;
        tasks[i].Rel_Period_Deadline = MAXINT;
        tasks[i].function = NULL;
        tasks[i].arg = i;
    }
    threads[NTHREADS-1].next = NULL;
    tasks[NTHREADS-1].next = NULL;
    initialized = 1;
}

// You might want to change enqueue with insertion sort. Depending on how you
// implement EDF, it might improve the sorting.
static void enqueue(thread p, thread *queue) {
	p->next = NULL;
	if (*queue == NULL) { //empty
			*queue = p;
			return;
	}
	else if((*queue)->Period_Deadline > p->Period_Deadline){ //check aginst the head for highest deadline
		p->next = *queue;
		*queue = p;
		return;
	}
	else{ //loop to find where to put it
		thread q = *queue;
		while ((q->next !=NULL) && q->next->Period_Deadline < p->Period_Deadline){
			q = q->next;
		}
		p->next=q->next;
		q->next=p;
	}
}

static thread dequeue(thread *queue) {
    thread p = *queue;
    if (*queue) {
        *queue = (*queue)->next;
    } else
    {
        PUTTOLDC("ops%s", "!!");
    }
    return p;
}

static thread removeLast(thread *queue) { //new
    thread p = *queue;
		thread last;
		if(!(*queue)){ PUTTOLDC("ops22%s", "!!2");	}
    while (p->next->next) {
        p = p->next;
    }
		last =p->next;
		p->next=NULL;
    return last;
}

static void dispatch(thread next) {
    if (setjmp(current->context) == 0) {
        current = next;
        longjmp(next->context,1);
    }
}

int findTask(unsigned int deadline, unsigned int rel_deadline, void (* function)(int), int arg) //find if task is in the taskQ
{
    thread q =taskQ;
    int found = 0;
    while(q != NULL)
    {
        if ((q->function == function) &&
            (q->arg == arg) &&
            (q->Rel_Period_Deadline == rel_deadline)){
            found = 1;
            break;
        }
        q = q->next;
    }
    return found;
}

void spawnWithDeadline(unsigned int deadline, unsigned int rel_deadline, void (* function)(int), int arg) {
	thread newp;
	DISABLE();
	if (!initialized){ initialize(); }

	if(!findTask(deadline, rel_deadline, function, arg)){ //this is the key= make place in the taskQ
		newp = removeLast(&taskQ);
		newp->function = function;
		newp->arg = arg;
		newp->next = NULL;
		newp->Period_Deadline=deadline;
		newp->Rel_Period_Deadline=rel_deadline;
		enqueue(newp, &taskQ);
	}

	newp = removeLast(&freeQ);
	newp->function = function;
	newp->arg = arg;
	newp->next = NULL;
	newp->Period_Deadline=deadline;
	newp->Rel_Period_Deadline=rel_deadline;

	if (setjmp(newp->context) == 1) {
			ENABLE();
			current->function(current->arg);
			while(readyQ==NULL){ }  //suggestion .. and it works not
			DISABLE();
			enqueue(current, &freeQ);
			dispatch(dequeue(&readyQ));
	}
	SETSTACK(&newp->context, &newp->stack);
	enqueue(newp, &readyQ);
	ENABLE();

}

void yield(void) {
    DISABLE();
	if (readyQ != NULL){
		thread p = dequeue(&readyQ);
        enqueue(current, &readyQ);
        dispatch(p);
	}
    ENABLE();
}

void lock(mutex *m) {
	if(m->locked == 0){ m->locked =1; }
	else if(m->locked >= 1){
	DISABLE();
	enqueue(current, &m->waitQ);
	m->locked = (m->locked) + 1;
	if (readyQ != NULL){
		thread p = dequeue(&readyQ);
		dispatch(p);
	}
	ENABLE();
	}
}

void unlock(mutex *m) {
	if(m->locked >=1){
	if(m->waitQ !=NULL){
			DISABLE();
			m->locked = (m->locked) - 1;
			thread temp = dequeue(&m->waitQ);
			enqueue(current, &readyQ);
			dispatch(temp);
			ENABLE();
	}
	else{m->locked=0;}
	}
}

int findTaskReadyQ(unsigned int deadline, unsigned int rel_deadline, void (* function)(int), int arg) //NEW another for readyQ
{
    thread q = readyQ;
    int found = 0;
    while(q != NULL)
    {
        if ((q->function == function) &&
            (q->arg == arg) &&
            (q->Rel_Period_Deadline == rel_deadline)){
            found = 1;
            break;
        }
        q = q->next;
    }
    return found;
}

void sortReadyQ(void){
	thread newQ;
	while(readyQ != NULL){

		enqueue(dequeue(&readyQ), &newQ);
	}
	readyQ =newQ;

	/*
	while(newQ !=NULL){
		enqueue(dequeue(&readyQ), &newQ);
		enqueue(newQ, &readyQ);
	}
	*/
}

void generate_Periodic_Tasks() {
// To be implemented!!!
// Remember, taskQ points to asked that have been spawned
// You generate tasks according to their period, if the task is not running,
// or if you not find the task in the readyQ (findTask)
// The implementation will be similar to Part 2, but here you have to adjust the
// absolute deadline.
	thread q = taskQ;
	while(q != NULL){
		if(ticks % q->Rel_Period_Deadline == 0){
			if(!findTaskReadyQ(q->Period_Deadline, q->Rel_Period_Deadline, q->function, q->arg) ){ // || !(current==q)
				q->Period_Deadline = q->Period_Deadline + q->Rel_Period_Deadline;
				spawnWithDeadline(q->Period_Deadline , q->Rel_Period_Deadline, q->function, q->arg );
			}
		}
		q = q->next;
	}
}
void scheduler_RR(){

}

void scheduler_RM(){

}

void scheduler_EDF(){
    // To be implemented!!!
	sortReadyQ();
	DISABLE();
	if(readyQ !=NULL){
		thread p = dequeue(&readyQ);
		dispatch(p);
	}
	ENABLE();
}

void scheduler(){
    scheduler_EDF();
}

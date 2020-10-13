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
    if (*queue == NULL) {
        *queue = p;
    } else {
        thread q = *queue;
        while (q->next)
            q = q->next;
        q->next = p;
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

static void dispatch(thread next) {
    if (setjmp(current->context) == 0) {
        current = next;
        longjmp(next->context,1);
    }
}

void spawn(void (* function)(int), int arg) {
    thread newp;
    DISABLE();
    if (!initialized) initialize();

    newp = dequeue(&freeQ);
    newp->function = function;
    newp->arg = arg;
    newp->next = NULL;
    if (setjmp(newp->context) == 1) {
        ENABLE();
        current->function(current->arg);
        DISABLE();
        enqueue(current, &freeQ);
        dispatch(dequeue(&readyQ));    
    }
    SETSTACK(&newp->context, &newp->stack);
    enqueue(newp, &readyQ);
    ENABLE();
}

void spawnWithDeadline(unsigned int deadline, unsigned int rel_deadline, void (* function)(int), int arg) {
    // To be implemented!!!
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
    // Put here the corresponding implementation results from Part 1
}

void unlock(mutex *m) {
    // Put here the corresponding implementation results from Part 1
}

int findTask(unsigned int deadline, unsigned int rel_deadline, void (* function)(int), int arg)
{
    thread q = taskQ;
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

void generate_Periodic_Tasks() {
// To be implemented!!!
// Remember, taskQ points to asked that have been spawned
// You generate tasks according to their period, if the task is not running, 
// or if you not find the task in the readyQ (findTask)
// The implementation will be similar to Part 2, but here you have to adjust the 
// absolute deadline.
}
void scheduler_RR(){
    
}

void scheduler_RM(){

}

void scheduler_EDF(){
    // To be implemented!!!
}

void scheduler(){
    scheduler_EDF();
}




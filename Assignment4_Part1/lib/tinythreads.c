/*
 * The code below has been developed by Johan Nordlander and Fredrik Bengtsson at LTU.
 * Part of the code has been also developed, modified and extended to ARMv8 by Wagner de Morais and Hazem Ali.
*/

#include <setjmp.h>
#include "tinythreads.h"
#include <stdio.h>
#include <stdarg.h>
#include "rpi-interrupts.h"
#include "piface.h"

__attribute__(( always_inline )) static inline void enable_interrupts() {
  __asm volatile("cpsie i \n"); //AIF???
}

__attribute__(( always_inline )) static inline void disable_interrupts() {
  __asm volatile("cpsid i \n"); //AIF???
}

#define DISABLE()       disable_interrupts()
#define ENABLE()        enable_interrupts()
#define NULL            0
#define STACKSIZE       1024
#define NTHREADS        10
#define MAXINT          0x7fffffff
#define RUN 			1
#define STOP 			0

#define SETSTACK(buf,a) *((unsigned int *)(buf)+8) = (unsigned int)(a) + STACKSIZE - 4;

struct thread_block {
    void (*function)(int);   // code to run
    int arg;                 // argument to the above
    thread next;             // for use in linked lists
    jmp_buf context;         // machine state
    char stack[STACKSIZE];   // execution stack space
};

struct thread_block threads[NTHREADS];

struct thread_block initp;

thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &initp;

int initialized = 0;

static void initialize(void) {
    int i;
    for (i=0; i<NTHREADS-1; i++)
        threads[i].next = &threads[i+1];
    threads[NTHREADS-1].next = NULL;

    initialized = 1;
}

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
    } else {
        // Empty queue, kernel panic!!!
        while (1) ;  // not much else to do...
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

void yield(void) {
    DISABLE();
	if (readyQ != NULL){
		thread p = dequeue(&readyQ);
		enqueue(current, &readyQ);
		dispatch(p);
	}
    ENABLE();
}


void lock(mutex *m) { //JOHAN changed 16:20 -14/10/2020
    // To be implemented!!!
    //if its 0 -> you can use this resource
    //if its 1 you can use it becasue it already locked(being used)
    if(m->locked == 1){
      //add task to waitingQ if they cant run
      m->waitQ =current; //thread waitQ;
      thread p = dequeue(&readyQ);
      dispatch(p);
    }
    else{ m->locked =1;}

    count++;
}

void unlock(mutex *m) { //JOHAN changed 16:20 -14/10/2020
    // To be implemented!!!
    if(m->locked==1){
      if(m->waitQ != NULL){
          dispatch(m->waitQ);
          m->waitQ=NULL;
      }
      m->locked=0;
    }
}

void generate_Periodic_Tasks(){
}

void scheduler_RR(){
  yield();
	//piface_putc((int)'a');

}

void scheduler_RM(){

}

void scheduler_EDF()
{

}

void scheduler(){
	/*
	while(1) {
		piface_putc((int)'a');
	}
	*/
    scheduler_RR();
}

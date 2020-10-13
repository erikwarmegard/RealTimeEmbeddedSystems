/*
 * The code below has been developed by Johan Nordlander and Fredrik Bengtsson at LTU.
*/
/*
 *
 * tinythreads.h
 *
 */

#ifndef _TINYTHREADS_H
#define _TINYTHREADS_H

struct thread_block;
typedef struct thread_block *thread;
void spawn(void (*code)(int), int arg);
void yield(void);

void spawnWithDeadline(unsigned int deadline, unsigned int rel_deadline, void (* function)(int), int arg);

struct mutex_block {
    int locked;
    thread waitQ;
};
typedef struct mutex_block mutex;

#define MUTEX_INIT {0,0}
void lock(mutex *m);
void unlock(mutex *m);

void generate_Periodic_Tasks();
void scheduler_RR();
void scheduler_RM();
void scheduler_EDF();
void scheduler();

#endif


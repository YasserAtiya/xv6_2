#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


int 
sys_setpriority(void)
{
  int oldpriority;
  int newpriority;

  //Get current priority for the given process
  oldpriority = proc->priority;
  
  //uses argint to get new priority from user space
  if(argint(0, &newpriority) < 0)
    return -1; //Attaches top of stack to pid
  
  if(newpriority < 0 && newpriority > 200)
  {
    cprintf("%s \n", "The priority is outside the permited bounds.");
    return oldpriority;
  }

  //set current priority to the new priority
  proc->priority = newpriority;
  
  //if priority is now lower than original, reschedule
  if(newpriority < oldpriority)
    yield();

  //return the old priority
  return oldpriority;
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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


// return the cpu id of current process
int
sys_getcpuid(void)
{
    return getcpuid();
}


// change the priority of process
int
sys_chpri(void)
{
    int pid, prio;
    // Get the first argument as PID
    // Get the second argument as Priority
    // return -1 if either one of them is negative
    if(argint(0, &pid) < 0 || argint(1, &prio) < 0)
        return -1;

    return chpri(pid, prio);
}


// return share variable
int
sys_sh_var_read(void)
{
    return sh_var_for_sem_demo;
}


// write the argument (if not negetive) to the share variable
// return share variable
int
sys_sh_var_write(void)
{
    int n;
    if(argint(0, &n) < 0) 
        return -1;
    sh_var_for_sem_demo = n;
    return sh_var_for_sem_demo;
}



// allocate slab
int sys_salloc(void)
{
    int sz;
    if(argint(0, &sz) < 0) return -1;
    return (int)salloc(sz);
}


// free slab
int sys_sfree(void)
{
    int va;
    if(argint(0, &va) < 0) return -1;
    return sfree((void*)va);
}


int sys_cow_fork(void)
{
    return cow_fork();
}



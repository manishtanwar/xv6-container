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
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
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
    if(myproc()->killed){
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

int
sys_create_container(void){
  return create_container();
}

int
sys_destroy_container(void){
  int container_id;
  if(argint(0, &container_id) < 0)
    return 0;
  return destroy_container(container_id);
}

int
sys_join_container(void){
  int container_id;
  if(argint(0, &container_id) < 0)
    return 0;
  return join_container(container_id);
}

int
sys_leave_container(void){
  return leave_container();
}

int
sys_memory_log_on(void){
  return memory_log_on();
}

int
sys_memory_log_off(void){
  return memory_log_off();
}

int
sys_scheduler_log_on(void){
  return scheduler_log_on();
}

int
sys_scheduler_log_off(void){
  return scheduler_log_off();
}

int
sys_container_malloc(void){
  int nbytes;
  if(argint(0, &nbytes) < 0)
    return 0;
  return container_malloc(nbytes);
}

int sys_ps(void){
  ps_print_list();
  return 1;
}
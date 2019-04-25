struct{
  struct spinlock lock;
  struct container container[NPROC];
  int allocated[NPROC];               
} container_table;
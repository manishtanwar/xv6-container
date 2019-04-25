#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
	int c1 = create_container();
	int c2 = create_container();
	int c3 = create_container();


	if(fork() == 0){
		join_container(c1);
		sleep(20);
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(c1);
		sleep(20);
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(c1);
        printf(1,"On Container %d:\n",c1);
		ps();
		leave_container();
		exit();
	}

	if(fork() == 0){
		join_container(c2);
		sleep(70);
        printf(1,"On Container %d:\n",c2);
		ps();
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(c3);
		sleep(100);
        printf(1,"On Container %d:\n",c3);
		ps();
		leave_container();
		exit();
	}

	sleep(400);
	destroy_container(c1);
	destroy_container(c2);
	destroy_container(c3);
	int i;
    for(i=0;i<5;i++) wait();
	exit();
}
// user_ps_testcase
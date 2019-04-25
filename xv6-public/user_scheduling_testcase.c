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
        // sleep(60);
		while(1);
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(c1);
		// sleep(55);
		while(1);
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(c1);
        // sleep(50);
		while(1);
		leave_container();
		exit();
	}

	if(fork() == 0){
		join_container(c2);
		while(1);
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(c3);
		while(1);
		leave_container();
		exit();
	}
    sleep(10);
	scheduler_log_on();
	sleep(10);
	scheduler_log_off();

	destroy_container(c1);
	destroy_container(c2);
	destroy_container(c3);
	
    int i;
    for(i=0;i<5;i++) wait();
	exit();
}
// user_scheduling_testcase
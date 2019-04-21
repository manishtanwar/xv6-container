#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
	create_container();
	create_container();
	create_container();

	if(fork() == 0){
		join_container(1);
		sleep(50);
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(1);
		sleep(50);
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(1);
		sleep(30);
		ps();
		leave_container();
		exit();
	}

	if(fork() == 0){
		join_container(2);
		sleep(35);
		ps();
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(3);
		sleep(30);
		ps();
		leave_container();
		exit();
	}
	scheduler_log_on();
	sleep(5);
	scheduler_log_off();

	// sleep(100);
	destroy_container(1);
	destroy_container(2);
	destroy_container(3);
	wait();
	exit();
}
// user_test_assig3
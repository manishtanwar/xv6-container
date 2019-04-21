#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
	// printf(1,"log : %d\n",scheduler_log_on());
	// create_container();
	// create_container();
	// printf(1,"join : %d\n",join_container(1));
	// sleep(10);

	// int a = fork();
	// if(a == 0){
	// 	sleep(10);
	// 	printf(1,"join2 : %d\n",join_container(2));
	// 	printf(1,"leave : %d\n",leave_container());
	// 	printf(1,"join3 : %d\n",join_container(2));
	// 	sleep(10);
	// }
	// sleep(20);
	// if(a > 0) wait();

	create_container();
	create_container();
	create_container();
	ps();

	if(fork() == 0){
		join_container(1);
		sleep(50);
		ps();
		exit();
	}
	if(fork() == 0){
		join_container(1);
		sleep(50);
		ps();
		exit();
	}
	if(fork() == 0){
		join_container(1);
		sleep(50);
		ps();
		exit();
	}

	if(fork() == 0){
		join_container(2);
		sleep(35);
		ps();
		exit();
	}
	if(fork() == 0){
		join_container(3);
		sleep(30);
		ps();
		exit();
	}
	// scheduler_log_on();
	// int i = 0;
	// while(i<1e8) i++;
	// scheduler_log_off();
	wait();
	exit();
}
// user_test_assig3
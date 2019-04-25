#include "types.h"
#include "stat.h"
#include "user.h"

char *argv[] = {"ls"};

void go(){
    exec("sh", argv);

	int pid = getpid();
	char filename[6] = "file00";
	filename[4] = pid / 10 + '0';
	filename[5] = pid % 10 + '0';
	// printf(1,"%s \n", filename);
	open(filename, 0x200);

	int fd = open(filename, 0x002);
	char msg[15] = "Modified by :00";
	msg[13] = pid / 10 + '0';
	msg[14] = pid % 10 + '0';
	write(fd,msg,15);
}

int
main(void)
{
	create_container();
	create_container();
	create_container();

	if(fork() == 0){
		join_container(1);
		sleep(200);
		go();
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(1);
		sleep(220);
		go();
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(1);
		sleep(30);
		ps();
		sleep(40);
		exec("ls", argv);
		sleep(40);
		go();
		leave_container();
		exit();
	}

	if(fork() == 0){
		join_container(2);
		sleep(70);
		ps();
		sleep(40);
		exec("ls", argv);
		sleep(40);
		go();
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(3);
		sleep(100);
		ps();
		sleep(40);
		exec("ls", argv);
		sleep(40);
		go();
		leave_container();
		exit();
	}
	scheduler_log_on();
	sleep(5);
	scheduler_log_off();

	sleep(400);
	destroy_container(1);
	destroy_container(2);
	destroy_container(3);
	wait();
	exit();
}
// user_test_assig3
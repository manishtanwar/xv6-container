#include "types.h"
#include "stat.h"
#include "user.h"

char *argv[] = {"ls"};
char *argv1[] = {"cat","my_file",0};

#define O_RDONLY  0x000
#define O_WRONLY  0x001
#define O_RDWR    0x002
#define O_CREATE  0x200

void go(){
    exec("sh", argv);

	int pid = getpid();
	char filename[6] = "file00";
	filename[4] = pid / 10 + '0';
	filename[5] = pid % 10 + '0';
	// printf(1,"%s \n", filename);
	open(filename, O_CREATE);

	int fd = open(filename, O_WRONLY);
	char msg[15] = "Modified by :00";
	msg[13] = pid / 10 + '0';
	msg[14] = pid % 10 + '0';
	write(fd,msg,15);

    sleep(50);
    exec("cat", argv);
}

int
main(void)
{
	int c1 = create_container();
	int c2 = create_container();
	int c3 = create_container();

	if(fork() == 0){
		join_container(c1);
		sleep(200);
		go();
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(c1);
		sleep(220);
		go();
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(c1);
		sleep(30);
        printf(1,"ls on cid : %d\n",c1);
		exec("ls", argv);
		sleep(40);
		go();
		leave_container();
		exit();
	}

	if(fork() == 0){
		join_container(c2);
		sleep(70);
        printf(1,"ls on cid : %d\n",c2);
		exec("ls", argv);
		sleep(40);
		go();
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(c3);
		sleep(100);
        printf(1,"ls on cid : %d\n",c3);
		exec("ls", argv);
		sleep(40);
		go();
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
// user_ls_testcase
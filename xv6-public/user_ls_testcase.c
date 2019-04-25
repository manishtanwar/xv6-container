#include "types.h"
#include "stat.h"
#include "user.h"

char *argv[] = {"ls"};
char *argv1[] = {"cat","my_file",0};

#define O_RDONLY  0x000
#define O_WRONLY  0x001
#define O_RDWR    0x002
#define O_CREATE  0x200

void f1(){
    int pid = getpid();
	char filename[6] = "file00";
	filename[4] = pid / 10 + '0';
	filename[5] = pid % 10 + '0';
	// printf(1,"%s \n", filename);
	open(filename, O_CREATE);
}

void go(){
    int pid = getpid();
    printf(1,"\n\npid : %d\n\n",pid);
    open("my_file", O_CREATE);
	int fd = open("my_file", O_RDWR);
	char msg[16] = "Modified by :00\n";
	msg[13] = pid / 10 + '0';
	msg[14] = pid % 10 + '0';
	write(fd,msg,16);
    sleep(200);
    int f = fork();
    // printf(1,"\n\ncid : %d\n\n",get_cid());
    if(f == 0) exec("cat", argv1);
    wait();
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
        f1();
		go();
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(c1);
		sleep(220);
        f1();
		go();
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(c1);
		sleep(30);
        printf(1,"ls on cid : %d\n",c1);
        int f = fork();
    	if(f==0) exec("ls", argv);
        wait();
		sleep(60);
        f1();
        printf(1,"ls on cid : %d\n",c1);
        f = fork();
    	if(f==0) exec("ls", argv);
        wait();
		go();
		leave_container();
		exit();
	}

	if(fork() == 0){
		join_container(c2);
		sleep(70);
        printf(1,"ls on cid : %d\n",c2);
		int f = fork();
    	if(f==0) exec("ls", argv);
        wait();
		sleep(80);
        f1();
        printf(1,"ls on cid : %d\n",c2);
        f = fork();
    	if(f==0) exec("ls", argv);
        wait();
		go();
		leave_container();
		exit();
	}
	if(fork() == 0){
		join_container(c3);
		sleep(100);
        printf(1,"ls on cid : %d\n",c3);
		int f = fork();
    	if(f==0) exec("ls", argv);
        wait();
		sleep(100);
        f1();
        printf(1,"ls on cid : %d\n",c3);
        f = fork();
    	if(f==0) exec("ls", argv);
        wait();
		go();
		leave_container();
		exit();
	}

	sleep(1000);
	destroy_container(c1);
	destroy_container(c2);
	destroy_container(c3);
	int i;
    for(i=0;i<5;i++) wait();
	exit();
}
// user_ls_testcase
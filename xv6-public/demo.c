#include "types.h"
#include "stat.h"
#include "user.h"

char *argv[] = {"ls"};

#define O_RDONLY  0x000
#define O_WRONLY  0x001
#define O_RDWR    0x002
#define O_CREATE  0x200

void tc_ls(){
	open("a", O_CREATE);
	int f = fork();
	if(f==0) exec("ls", argv);
	sleep(100);
	printf(1,"\n\n");

	create_container();
	join_container(1);

	// opening in write mode to create copy of file
	open("a", O_WRONLY);

	f = fork();
	if(f == 0) exec("ls", argv);
	sleep(100);
	printf(1,"\n\n");
	leave_container();
	
	printf(1,"cid : %d\n", get_cid());
	exec("ls", argv);
	exit();
}

void tc_file_system(){
	open("a", O_CREATE);
	int wfd = open("a", 1);
	write(wfd, "hey", 3);
	int c1 = create_container();
	int c2 = create_container();

	int f = fork();
	if(f == 0){
		join_container(c1);
		int rfd = open("a", O_RDONLY);
		// printf(1,"rfd : %d\n",rfd);
		char *msg;
		msg = (char *)malloc(10);
		int b = read(rfd,msg,10);
		printf(1,"read : %d, %s\n",b,msg);
		open("a", O_RDWR);

		int wfd = open("a", O_WRONLY);
		rfd = open("a", O_RDONLY);
		b = read(rfd,msg,10);
		printf(1,"read : %d, %s\n",b,msg);

		write(wfd, "cont1", 5);
		rfd = open("a", O_RDONLY);
		b = read(rfd,msg,10);
		printf(1,"read : %d, %s\n",b,msg);

		leave_container();
		exit();
	}

	f = fork();
	if(f == 0){
		sleep(150);
		join_container(c2);
		int rfd = open("a", O_RDONLY);
		// printf(1,"rfd : %d\n",rfd);
		char *msg;
		msg = (char *)malloc(10);
		int b = read(rfd,msg,10);
		printf(1,"read : %d, %s\n",b,msg);
		open("a", O_RDWR);

		int wfd = open("a", O_WRONLY);
		rfd = open("a", O_RDONLY);
		b = read(rfd,msg,10);
		printf(1,"read : %d, %s\n",b,msg);

		write(wfd, "cont2", 5);
		rfd = open("a", O_RDONLY);
		b = read(rfd,msg,10);
		printf(1,"read : %d, %s\n",b,msg);

		// newfile in c2
		open("b", O_CREATE);

		leave_container();
		exit();
	}
	wait();
	wait();
	destroy_container(c1);
	destroy_container(c2);
	exec("ls", argv);
	exit();
}

int
main(void)
{
	tc_file_system();
}
#include "types.h"
#include "stat.h"
#include "user.h"

char *argv[] = {"ls"};

int
main(void)
{
	open("a", 0x200);
	int f = fork();
	if(f==0) exec("ls", argv);
	sleep(100);
	printf(1,"\n\n");
	// // printf(1,"bahar open : %d\n",op);
	// int wfd = open("a", 1);
	// // int a = 1;
	// write(wfd, "hey", 3);

	create_container();
	join_container(1);

	open("a", 0x200);

	f = fork();
	if(f == 0) exec("ls", argv);
	sleep(100);
	printf(1,"\n\n");
	leave_container();
	
	printf(1,"cid : %d\n", get_cid());
	exec("ls", argv);
	// // printf(1,"andar open : %d\n",op1);
	// // int rfd = open("a", 0);
	// open("a", 0x200);
	
	// int wri = open("a", 1);
	// write(wri, "here", 4);
	// int rfd = open("a", 0);
	// printf(1,"rfd : %d\n",rfd);
	// write(wfd, "there", 5);

	
	// // printf(1,"rfd : %d, wfd : %d\n",rfd,wfd);
	// // printf(1,"wrote : %d\n",a);
	// char *msg;
	// msg = (char *)malloc(10);
	// int b = read(rfd,msg,10);
	// printf(1,"read : %d, %s\n",b,msg);

	// // leave_container();
	// // rfd = open("a", 0);
	// // msg[0] = '1';
	// // b = read(rfd,msg,3);
	// // printf(1,"read : %d, %s\n",b,msg);

	// // char *ch = (char *)malloc(3);
	// // int b = read(rfd,ch,3);
	// // printf(1,"%d %d %s\n",a,b,ch);
	// printf(1,"here\n");
	exit();
}
#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
	// create_container();
	// join_container(1);
	open("a", 0x200);
	int rfd = open("a", 0);
	int fd = open("a", 1);
	// int a = 1;
	int a = write(fd, "hey", 3);

	char *ch = (char *)malloc(3);
	int b = read(rfd,ch,3);
	printf(1,"%d %d %s\n",a,b,ch);
	exit();
}
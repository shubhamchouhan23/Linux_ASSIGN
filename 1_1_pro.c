//One program to write strings to shared memory.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc,char* argv[])
{
	//int count;
	const int SIZE = 4096;
	const char* name = "OS";
	//count = argc-1;
	//char* array[count];

/*for(int i=0;i<count;i++)
{
array[i]=argv[i];
}
*/
	char* message_0 = argv[1];
	char* message_1 = argv[2];


	int shm_fd;

	void* ptr;

	
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	
	ftruncate(shm_fd, SIZE);

	
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	//for(int i=1;i<count;i++)
	sprintf(ptr," \n %s %s \n ", message_0,message_1);
	//printf("%p",ptr);
	printf("Reverse String :");
	for(int i=strlen(argv[1])-1;i>-1;i--){
	printf("%c",argv[1][i]);
	}
	printf(" ");
	for(int i=strlen(argv[1])-1;i>-1;i--){
	printf("%c",argv[2][i]);
	}
	printf("\n");
	printf("Number of Arguments passed : %d",argc-1);
	
	
	
	ptr += strlen(message_0);
	sprintf(ptr, "%s", message_1);
	ptr += strlen(message_1);

	return 0;
}


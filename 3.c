#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>


pthread_mutex_t my_mutex;

void *thread_A_Z(void *arg)
{
	pthread_mutex_lock(&my_mutex);
   int num;
   FILE *fptr;
   fptr = fopen("temp.txt","a");

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
    char c;
    for (c = 'A'; c <= 'Z'; ++c)
        fprintf(fptr,"%c",c);

   
   fclose(fptr);

   pthread_mutex_unlock(&my_mutex);
}

void *thread_a_z(void *arg)
{
	pthread_mutex_lock(&my_mutex);
   int num;
   FILE *fptr;
   fptr = fopen("temp.txt","w");

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
    char c;
    for (c = 'a'; c <= 'z'; ++c)
        fprintf(fptr,"%c",c);

   
   fclose(fptr);	


	
	
	pthread_mutex_unlock(&my_mutex);
}

int main()
{	
	pthread_t thread1, thread2;

	pthread_mutex_init(&my_mutex,NULL);

	pthread_create(&thread1, NULL, thread_A_Z, NULL);
	pthread_create(&thread2, NULL, thread_a_z, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_exit(thread_A_Z);
	pthread_exit(thread_a_z);
		
	return 0;
}

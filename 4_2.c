#include<stdio.h>
#include<pthread.h>
#include<string.h>

    int a= 1;
void *thread1(void *arg){
a = (int)arg;
while(1)
{
a++;
printf("%d\n",a);
}
    return 0;
}
int main(int argc, char** argv){
    pthread_t t1;
    void *res;
    int ret = pthread_create(&t1,NULL,thread1,argv[1]);
    printf("message from main:\n");
    printf("thread returned:%ld",pthread_self());

//printf("%d",a);
    pthread_join(t1,NULL);
    //pthread_exit(NULL);//null and 0 both will do here
    //printf("this will not be executed as code is terminated\n");
    return 0;
}

#include<stdio.h>
#include<pthread.h>
#include<string.h>

    int a= 1;
void *thread1(void *arg){
while(1)
{
a++;
printf("%d",a);
}
    return 0;
}
int main(void){
    pthread_t t1;
    void *res;
    int ret = pthread_create(&t1,NULL,thread1,"\nthread applied\n");
    printf("message from main:\n");
    printf("thread returned:%ld",pthread_self());
    pthread_join(t1,NULL);
    
    return 0;
}

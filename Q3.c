#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include<semaphore.h>
#include <stdlib.h>
int a;
int b;
int c;
int result;
sem_t sm1 ,sm2,sm3, sm4;
void f1()
{
    printf("Enter a and b:");
    scanf("%i %i" ,&a,&b);
}

void f2()
{   do
    {
    printf("Enter c[1-4]:");
    scanf("%i", &c);

    }
    while(c<1 || c>4);
}
void f3()
{

    if(c==1)
    {
        result = a + b;
    }

    if(c==2)
    {
        result = a - b;
    }

    if(c==3)
    {
        result = a * b;
    }
    if(c==4)
    {
        result = a / b;
    }

}

void *myThread(void *arg)
{
    sem_wait(&sm1);
     f1();
    sem_post(&sm2);
    pthread_exit(NULL);

}

void *myThread1(void *arg)
{
     sem_wait(&sm2);
     sem_wait(&sm3);

     f2();
     sem_post(&sm1);
     sem_post(&sm4);

    pthread_exit(NULL);

}
void *myThread2(void *arg)
{
    sem_wait(&sm4);

     f3();
   sem_post(&sm3);
    pthread_exit(NULL);

}





int main()
{
   pthread_t tid;
   pthread_t tid1;
   pthread_t tid2;
  sem_init(&sm1 ,0, 1);
  sem_init(&sm2 ,0, 0);
  sem_init(&sm3 ,0, 1);
  sem_init(&sm4 ,0, 0);



   pthread_create(&tid, NULL, myThread,NULL);
   pthread_create(&tid1, NULL, myThread1,NULL);
   pthread_create(&tid2, NULL, myThread2,NULL);

   pthread_join(tid1, NULL);
   pthread_join(tid, NULL);
   pthread_join(tid2, NULL);
   printf("Result = %i\n",result);

   return 0;
}
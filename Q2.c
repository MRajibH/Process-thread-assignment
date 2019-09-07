#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include<semaphore.h>
#include <stdlib.h>

sem_t sm1 ,sm2,sm3,sm4;

void f1(void)
{
   printf("This");

}

void f2(void)
{
   printf("is");

}

void f3(void)
{
   printf("Summer");

}
void f4(void)
{
   printf("2019\n");

}
void f5(void)
{
   printf(" ");
}

void *myThread(void *arg)
{
   sem_wait(&sm1);
   sem_wait(&sm3);
   f1();
   sem_post(&sm2);
   sem_post(&sm4);
   sem_wait(&sm1);
   sem_wait(&sm3);
   f3();
   sem_post(&sm2);
   sem_post(&sm4);
   sem_wait(&sm1);
   sem_wait(&sm3);

  pthread_exit(NULL);


}


//Thread 2

void *myThread1(void *arg)
{  sem_wait(&sm2);
  sem_wait(&sm3);
   f2();
   sem_post(&sm1);
   sem_post(&sm4);
   sem_wait(&sm2);
   sem_wait(&sm3);
   f4();
   sem_post(&sm1);
   sem_post(&sm3);
 pthread_exit(NULL);

}


//Thread 3
void *myThread2(void *arg)
{
   sem_wait(&sm4);
   f5();
   sem_post(&sm3);
   sem_wait(&sm4);
   f5();
   sem_post(&sm3);
   sem_wait(&sm4);
   f5();
   sem_post(&sm3);
   //sem_wait(&sm4);

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

   return 0;
}









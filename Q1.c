#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct thread_data {

   int n;
   int result;

} thread_data;
int a;    //a ,b is used as global data
int b;
//Thread 1
void *myThread(void *arg)
{
   thread_data *tdata=(thread_data *)arg;


   int n=tdata->n;
   int result= n*(n+a);

   tdata->result=result;
   printf("Result1 = %d", tdata->result);
   pthread_exit(NULL);
}
//Thread 2
void *myThread1(void *arg)
{
   thread_data *tdata=(thread_data *)arg;


   int n=tdata->n;
   int result= n*(n+a)*(n-b);

   tdata->result=result;
   printf("Result2 = %d", tdata->result);
   pthread_exit(NULL);
}
//Thread 3
void *myThread2(void *arg)
{
   printf("Done");
   pthread_exit(NULL);
}

//Thread 4
void *myThread3(void *arg)
{
   printf("\n");
   pthread_exit(NULL);
}
int main()
{
   pthread_t tid;
   pthread_t tid1;
   pthread_t tid2;
   pthread_t tid3;
   thread_data tdata;
   printf("Enter n, a ,b repectively here: ");
   scanf("%i %i %i",&tdata.n,&a,&b);


   pthread_create(&tid, NULL, myThread, (void *)&tdata);
   pthread_join(tid, NULL);
   pthread_create(&tid3, NULL, myThread3, NULL);

   pthread_create(&tid1, NULL, myThread1, (void *)&tdata);
   pthread_join(tid1, NULL);
   pthread_create(&tid3, NULL, myThread3, NULL);


   pthread_create(&tid2, NULL, myThread2, NULL);
   pthread_join(tid2, NULL);

   pthread_create(&tid3, NULL, myThread3, NULL);




   return 0;
}
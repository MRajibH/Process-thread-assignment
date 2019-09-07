#include <pthread.h> // for pthread_create, pthread_join, pthread_exit
#include <stdio.h> // for printf
#include <stdlib.h> // for exit
#include<semaphore.h>
#define NUM 1000000
sem_t sm;            // changes
int res = 0;
void* count(void *a)
{
   sem_wait (&sm);   //changes
 int i, tmp;
 for(i = 0; i < NUM; i++)
 {

 tmp = res; /* copy the global res locally */
 tmp = tmp+1; /* increment the local copy */
 res = tmp; /* store the local value into the global res */

 }
 sem_post (&sm);      //changes
 return 0;
}
int main(int argc, char * argv[])
{
 sem_init(&sm, 0, 1);    //changes
 pthread_t tid1, tid2;
 if(pthread_create(&tid1, NULL, count, NULL))
 {
 printf("\n ERROR while creating thread 1");
 exit(1);
 }
 if(pthread_create(&tid2, NULL, count, NULL))
 {
 printf("\n ERROR while thread 2");
 exit(1);
 }
 if(pthread_join(tid1, NULL)) /* wait for the thread 1 to finish */
 {
 printf("\n ERROR while joining thread 1");
 exit(1);
 }
 if(pthread_join(tid2, NULL)) /* wait for the thread 2 to finish */
 {
 printf("\n ERROR while joining thread 2");
 exit(1);
 }
 if (res < 2 * NUM)
 {
 printf("\n BOOM! res is [%d], should be %d\n", res, 2*NUM);
 }
 else
 {
 printf("\n OK! res is [%d]\n", res);
 }

 pthread_exit(NULL);
}
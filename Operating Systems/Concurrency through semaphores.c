#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int input1, input2, input3;
int sum = 0;
int product = 0;
sem_t sem;

void getInput()
{

  for (int i = 0; i < 10; i++)
  {
    // TODO Complete code here
    printf("Enter 3 numbers\n");
    scanf("%d", &input1);
    scanf("%d", &input2);
    scanf("%d", &input3);
    sum = input1 + input2 + input3;
    product = input1 * input2 * input3;
    sem_post(&sem);
    usleep(500);
  }
}

void outputSumProduct()
{

  for (int i = 0; i < 10; i++)
  {
    sem_wait(&sem);
    printf("Sum: %d Product: %d\n", sum, product);
  }
}

int main()
{
  pthread_t thread1;
  pthread_t thread2;

  // initialize semaphore
  sem_init(&sem, 0, 0);

  pthread_create(&thread1, NULL, (void *)getInput, NULL);
  pthread_create(&thread2, NULL, (void *)outputSumProduct, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("Completed\n");
  sem_destroy(&sem);

  return 0;
}

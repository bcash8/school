#include <stdio.h>
#include <unistd.h>

int main()
{
  pid_t pid;
  int x = 0;
  int y = 0;
  int z = 0;
  printf("Hello C World\n");

  x = 5;
  y += 2;
  pid = fork();
  if (pid == 0)
  { // Child
    x += 3;
    y += 3;
    z += 3;
    printf("Hello from Child\n");
    printf("Child Forked PID Value = %i\n", pid);
    printf("Child PID: %i\n", getpid());
    printf("Child values: %i, %i, %i\n", x, y, z);
  }
  else if (pid < 0)
  { // Error
  }
  else
  { // Parent
    x += 2;
    y += 2;
    z += 2;
    printf("Hello from Parent\n");
    printf("Parent Forked PID Value = %i\n", pid);
    printf("Parent PID: %i\n", getpid());
    printf("Parent values: %i, %i, %i\n", x, y, z);
  }
  return 0;
}

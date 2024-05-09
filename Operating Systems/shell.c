#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define commandSize 100

int main()
{
  char cmd[commandSize];
  char path[commandSize];
  char cwd[1024];

  printf("Welcome to the worst shell you have ever used\n");

  while (1)
  {
    getcwd(cwd, sizeof(cwd));
    printf("%s: ", cwd);
    fgets(cmd, sizeof(cmd), stdin);
    cmd[strcspn(cmd, "\n")] = '\0'; // remove new line character

    if (strncmp(cmd, "cd ", 3) == 0)
    {
      strcpy(path, cmd + 3);
      if (chdir(path) != 0)
      {
        perror("An error occured when switching directories\n");
        return 1;
      }
    }
    else if (strncmp(cmd, "quit", 4) == 0)
    {
      printf("Goodbye.\n");
      return 0;
    }
    else
    {
      pid_t pid = fork();
      if (pid == 0)
      {
        char* args[20];
        int i = 0;
        int arg_index = 0;
        while (cmd[i] != '\0' && arg_index < 20 && i < sizeof(cmd))
        {
          while (cmd[i] == ' ' || cmd[i] == '\n') //Skip empty characters
            i++;

          if (cmd[i] == '\0') // End of string
            break;

          args[arg_index++] = cmd + i; //Set the pointer for the start of the argument

          while (cmd[i] != ' ' && cmd[i] != '\n' && cmd[i] != '\0') //Continue until the end of the aregument is found
            i++;

          cmd[i++] = '\0'; //Set the null terminater so that the argument is ended.
        }
        args[arg_index] = NULL; // Add null to the end of the array 

        execvp(args[0], args);
        exit(0);
      }
      else if (pid > 0)
      {
        waitpid(pid, NULL, NULL);
      }
    }
  }

  return 0;
}

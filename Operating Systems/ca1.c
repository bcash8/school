#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  printf("Hello C World\n");
  __pid_t pid = getpid();
  printf("This is PID %d speaking\n", pid);

  DIR *dir;
  struct dirent *entry;

  dir = opendir("/proc");
  if (dir == NULL)
  {
    perror("Error opening directory");
    return 1;
  }

  while ((entry = readdir(dir)) != NULL)
  {
    int pid = atoi(entry->d_name);
    if (pid > 0)
    {
      char path[269]; // 256 d_name + 5 /proc + 8 /cmdline
      snprintf(path, sizeof(path), "/proc/%d/cmdline", pid);
      FILE *file = fopen(path, "r");
      if (file == NULL)
        continue;

      char *line = NULL;
      size_t len = 0;
      ssize_t read;

      int pidLen = strlen(entry->d_name);
      while ((read = getline(&line, &len, file)) != -1)
      {
        printf("%d", pid);
        for (int i = 0; i < 10 - pidLen; i++) //Pad the line with extra spaces to justify the command.
        {
          printf(" ");
        }
        printf("%s\n", line);
      }

      free(line);
      fclose(file);
    }
  }

  return 0;
}

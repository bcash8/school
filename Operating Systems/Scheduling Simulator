#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int **deepClone(int **table, int rows, int cols);
void freeTable(int **tbl, int rows);
int **createArray(int n, int c);
void simulate(int **table, int n);
int allProcessesFinished(int **table, int n, int t);
int fcfs(int **table, int n);
int sjf(int **table, int n);
int srt(int **table, int n);

int main(int argc, char *argv[])
{
  if (argc != 5 && argc != 1)
  {
    printf("Invalid command line arguments. Expected [n] [k] [min_time] [max_time].\n");
    return 1;
  }
  int n = 10;
  int k = 100;
  int minTime = 7;
  int maxTime = 15;

  if (argc == 5)
  {
    n = atoi(argv[1]);
    k = atoi(argv[2]);
    minTime = atoi(argv[3]);
    maxTime = atoi(argv[4]);
  }

  printf("%d %d %d %d\n", n, k, minTime, maxTime);

  int **table = createArray(n, 5);
  if (table == NULL)
  {
    return 1;
  }

  srand(time(NULL));

  printf("PID     Active  Arrival Total   Remain  Turnaround\n");
  for (int i = 0; i < n; i++)
  {
    int arrivalTime = rand() % k;
    int cpuTime = rand() % maxTime + minTime;
    table[i][0] = 0;
    table[i][1] = arrivalTime;
    table[i][2] = cpuTime;
    table[i][3] = cpuTime;
    table[i][4] = 0;
    printf("%-*d%-*d%-*d%-*d%-*d%-*d\n", 8, i, 8, 0, 8, arrivalTime, 8, cpuTime, 8, cpuTime, 8, 0);
  }

  simulate(table, n);
  freeTable(table, n);

  return 0;
}

// Simulation Functions
void simulate(int **table, int n)
{
  for (int i = 0; i < 3; i++)
  {
    int **simulationTable = deepClone(table, n, 5);
    int t = 0;

    while (!allProcessesFinished(simulationTable, n, t))
    {
      for (int j = 0; j < n; j++)
      {
        if (simulationTable[j][1] == t)
        {
          simulationTable[j][0] = 1;
        }
      }
      
      int processToRun = -1;
      switch (i)
      {
      case 0: processToRun = fcfs(simulationTable, n);
        break;
      case 1: processToRun = sjf(simulationTable, n);
        break;
      case 2: processToRun = srt(simulationTable, n);
        break;
      }

      if (processToRun > -1)
      {
        simulationTable[processToRun][3]--;
        if (simulationTable[processToRun][3] == 0)
        {
          simulationTable[processToRun][0] = 0;
          simulationTable[processToRun][4] = t - simulationTable[processToRun][1];
        }
      }
      printf("Time: %d - PID: %d\n", t, processToRun);
      t++;
    }

    int sum = 0;
    for (int j = 0; j < n; j++)
    {
      sum += simulationTable[j][4];
    }
    float avg = (float)sum / n;

    switch (i)
    {
    case 0: printf("FCFS - %f\n", avg);
      break;
    case 1: printf("SJF - %f\n", avg);
      break;
    case 2: printf("SRT - %f\n", avg);
      break;
    default:
      break;
    }

    freeTable(simulationTable, n);
  }
}

int fcfs(int **table, int n)
{
  int minTime = -1;
  int processIndex = -1;

  for (int i = 0; i < n; i++)
  {
    if (table[i][0] && (table[i][1] < minTime || minTime == -1))
    {
      minTime = table[i][1];
      processIndex = i;
    }
  }
  return processIndex;
}

int sjf(int **table, int n)
{
  int shortest = -1;
  int process = -1;
  for (int i = 0; i < n; i++)
  {
    if (table[i][0] && (table[i][2] < shortest || shortest == -1))
    {
      process = i;
      shortest = table[i][2];
    }
  }

  return process;
}

int srt(int **table, int n)
{
  int shortest = -1;
  int process = -1;
  for (int i = 0; i < n; i++)
  {
    if (table[i][0] && (table[i][3] < shortest || shortest == -1))
    {
      process = i;
      shortest = table[i][3];
    }
  }

  return process;
}

int allProcessesFinished(int **table, int n, int t)
{
  for (int i = 0; i < n; i++)
  {
    if (table[i][3] >= 1 || table[i][1] > t)
    {
      return 0;
    }
  }
  return 1;
}

// Utility Functions
int **createArray(int n, int c)
{
  int **table = (int **)malloc(n * sizeof(int *));
  if (table == NULL)
  {
    printf("Failed to allocate memory");
    return NULL;
  }

  for (int i = 0; i < n; i++)
  {
    table[i] = (int *)malloc(c * sizeof(int));
    if (table[i] == NULL)
    {
      for (int j = 0; j < i; j++) {
        free(table[j]);
      }
      free(table);
      printf("Failed to allocate memory");
      return NULL;
    }
  }

  return table;
}

void freeTable(int **tbl, int rows)
{
  for (int i = 0; i < rows; i++)
  {
    free(tbl[i]);
  }

  free(tbl);
}

int **deepClone(int **table, int rows, int cols)
{
  int **newTable = createArray(rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      newTable[i][j] = table[i][j];
    }
  }

  return newTable;
}

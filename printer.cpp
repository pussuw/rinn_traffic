#include "printer.h"

pthread_mutex_t print_mutex;

void init_print(void)
{
  pthread_mutex_init(&print_mutex, NULL);
}

void mycerr(const char * fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  pthread_mutex_lock(&print_mutex);
  vfprintf (stderr, fmt, args);
  pthread_mutex_unlock(&print_mutex);
  va_end (args);
}

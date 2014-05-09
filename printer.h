#ifndef PRINTER_H_
#define PRINTER_H_

#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
     
void init_print(void);
     
void mycerr(const char * fmt, ...);

#endif

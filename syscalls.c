#include <sys/stat.h>
#include <sys/times.h>
#include <stdio.h>
#include <errno.h>
#include "uart.h"

#ifndef __PICOLIBC_VERSION__
#undef errno
extern int errno;
#endif

void _exit(__attribute__((unused)) int exit_code){
    while(1){}
}

int _close(__attribute__((unused)) int file) {
  return -1;
}

char *__env[1] = { 0 };
char **environ = __env;

int _execve(__attribute__((unused)) char *name, __attribute__((unused)) char **argv, __attribute__((unused)) char **env) {
  errno = ENOMEM;
  return -1;
}

int _fork(void) {
  errno = EAGAIN;
  return -1;
}

int _fstat(__attribute__((unused)) int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}

int _getpid(void) {
  return 1;
}

int _isatty(__attribute__((unused)) int file) {
  return 1;
}

int _kill(__attribute__((unused)) int pid, __attribute__((unused)) int sig) {
  errno = EINVAL;
  return -1;
}

int _link(__attribute__((unused)) char *old, __attribute__((unused)) char *new) {
  errno = EMLINK;
  return -1;
}

int _lseek(__attribute__((unused)) int file, __attribute__((unused)) int ptr, __attribute__((unused)) int dir) {
  return 0;
}

int _open(__attribute__((unused)) const char *name, __attribute__((unused)) int flags, __attribute__((unused)) int mode) {
  return -1;
}

int _read(__attribute__((unused)) int file, __attribute__((unused)) char *ptr, __attribute__((unused)) int len) {
  return 0;
}

#ifdef __PICOLIBC_VERSION__
void* _sbrk(int incr) {
  extern char __heap_start;
  extern char __heap_end;
  static char* heap_pointer;
  char* prev_heap_pointer;
  char* heap_end;
  heap_end =  &__heap_end;

  if(heap_pointer ==0 ){
    heap_pointer = &__heap_start;
  }
  prev_heap_pointer = heap_pointer;
  if (heap_pointer+incr >= heap_end){
    while(1){/*heap and stack collision*/}
  }

  heap_pointer += incr;
  return (void*)prev_heap_pointer;

}

#else

register char * stack_ptr asm("sp");
void* _sbrk(int incr) {
  extern char __bss_end__;
  static char *heap_end;
  char *prev_heap_end;
 
  if (heap_end == 0) {
    heap_end = &__bss_end__;
  }
  prev_heap_end = heap_end;
  if (heap_end + incr > stack_ptr) {
    while (1)
    {
        // Heap and stack collision
    }
  }

  heap_end += incr;
  return (void*) prev_heap_end;
}

#endif

int _stat(__attribute__((unused)) char *file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}

int _times(__attribute__((unused)) struct tms *buf) {
  return -1;
}

int _unlink(__attribute__((unused)) char *name) {
  errno = ENOENT;
  return -1; 
}

int _wait(__attribute__((unused)) int *status) {
  errno = ECHILD;
  return -1;
}

int _write(int file, char *ptr, int len) {
  (void) file;
  
  for (int i = 0; i < len; i++)
  {
    uart_write_char(*ptr++);
  }
  
  return len;
}

#if defined(__PICOLIBC_VERSION__)

int _putc(char c, FILE *file){
	(void) file;		/* Not used in this function */
	uart_write_char(c);		/* Defined by underlying system */
	return c;
}

int _getc(FILE *file){
  unsigned char c;
	(void) file;		/* Not used in this function */
	c = uart_read_char();		/* Defined by underlying system */
	return c;
}


FILE __stdio = FDEV_SETUP_STREAM(_putc, _getc, NULL, _FDEV_SETUP_RW);
FILE *const stdin = &__stdio;
__strong_reference(stdin, stdout);
__strong_reference(stdin, stderr);
#endif
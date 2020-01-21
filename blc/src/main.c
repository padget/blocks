#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../../experimental/memory.h"

#define SRC_FILENAME "examples/add.blocks"
#define FILE_READMODE "r"

memory mem;

typedef struct argument
{
  char* type;
  char* value;
} argument;

typedef struct command
{
  char* name;
  argument* bargs;
  argument* eargs;
} command;

typedef struct commands 
{
  command* begin;
  command* end;
} commands ;

void readfile(FILE* file, char** buffer);
void parsesource(const char* src, commands* cmds);

int main()
{
  mem_init(&mem, 10);

  FILE* fsrc = fopen(SRC_FILENAME, FILE_READMODE); 

  if (fsrc)
  {
    commands cmds;
    char* src = NULL;
    readfile(fsrc, &src);
    parsesource(src, &cmds);
  
  }

  mem_destroy(&mem); 
}

typedef const char* errormsg;

void exit_if_enomem(void* ptr, errormsg msg)
{
  if (ptr==NULL&&errno==ENOMEM)
  {
    perror(msg);
    mem_destroy(&mem);
    exit(EXIT_FAILURE);
  }
}

void readfile(FILE* file, char** buffer) 
{
  fseek(file, 0L, SEEK_END);
  unsigned size = ftell(file);
  fseek(file, 0L, SEEK_SET);

  char* tmp = (char*)malloc(sizeof(char)*size+1);
  char* begin = tmp;

  exit_if_enomem(tmp, "can't read file because not enough memory");

  int c; 
  while ((c=getc(file))!=EOF)
  {
    *tmp = (char)c;
    tmp++;
  }

  *tmp = '\0';
  *buffer = begin;
}

void parsesource(const char* src, commands* cmds)
{
}

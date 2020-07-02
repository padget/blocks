#ifndef __blocks_std_io_h__
#define __blocks_std_io_h__

#include <stdio.h>
#include <stdint.h>

#include "string.h"

/// /////// ///
/// FILE RO ///
/// /////// ///

typedef FILE* file_t;

struct file_ro 
{
  file_t file;
};

typedef struct file_ro filero;

filero filero_open(string_r filename);
uint64_t filero_size(filero f);
void filero_close(filero f);
int filero_read(filero f);
string_rw filero_readall(filero f);

/// /////// ///
/// FILE RW ///
/// /////// ///

struct file_rw 
{
  file_t file;
};

typedef struct file_rw filerw;

filerw filerw_open(string_r filename);
void filerw_close(filerw f);
char filerw_read(filerw f);
string_rw filerw_readall(filerw f);
void filerw_write(filerw f, string_r str);

#endif
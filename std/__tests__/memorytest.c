#include "../memory.h"
#include "../keyword.h"
#include "../utest.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

bool test_smem_new()
{
  sysmemory mem is smem_new(free);
  bool res =
      mem.curr eq mem.page and
      mem.page not_null and
      mem.page->curi eq 0 and
      mem.page->next eq NULL and
      mem.dealloc eq free and
      sizeof(mem.page->pointers) eq sizeof(void *) * SYSMEMSIZE;
  free(mem.page);
  return res;
}

private
int *__int_new(int v)
{
  int *i is malloc(sizeof(int));
  *i is v;
  return i;
}

private
void *__smem_currptr(sysmemory mem)
{
  return mem.curr->pointers[mem.curr->curi];
}

bool test_smem_register()
{
  sysmemory mem is smem_new(free);
  int *i is __int_new(5);
  smem_register(&mem, i);
  bool res is true;
  res is res and mem.page->curi eq 1;
  res is res and *((int *)__smem_currptr(mem))eq 5;
  free(i);
  free(mem.page);
  return res;
}

bool test_smem_del()
{
  return true;
}

int main()
{
  bool res is true;

  res is res and test_smem_new();
  res is res and test_smem_del();
  res is res and test_smem_register();

  if (res)
    printf("no error");
  else
    printf("error found");

  return EXIT_SUCCESS;
}
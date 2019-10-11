#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "file.h"
#include "macro.h"
#include "srange.h"

void blocks_free(void *ptr) { free(ptr); }
void blocks_println(const char *text) { printf("%s\n", text); }
void blocks_printsr(const blocks_srange *range) {
  char *begin = range->begin;
  char *end = range->end;
  while (begin < end) {
    putchar(*begin);
    ++begin;
  }
}

int main(int argc, char const *argv[]) {
  blocks_println("Hello world");
  FILE *f = NULL;
  blocks_srange range;
  blocks_srange name;
  blocks_srange args[10];
  command c = {.name = name, .args = {.begin = args, .end = args + 9}};

  if (blocks_fopen("examples/main.blocks", &f) != FILE_NO_ERROR) {
    blocks_println("une erreur est suérvenu lors de l'ouverture du fichier");
    return EXIT_FAILURE;
  }

  if (blocks_build_buffer(f, &range) != FILE_NO_ERROR) {
    blocks_println("un soucis dans la préparation du buffer");
    return EXIT_FAILURE;
  }

  if (blocks_freadall(f, &range) != FILE_NO_ERROR) {
    blocks_println("un soucis dans la lecture du fichier");
    blocks_free(range.begin);
    blocks_fclose(f);
    return EXIT_FAILURE;
  }

  blocks_println(range.begin);
  if (blocks_detect_command(&range, &c) != COMMAND_NO_ERROR)
    blocks_println("un soucis de detection de commande");

  printf("nom de la commande");
  blocks_printsr(&c.name);
  printf("\n");

  blocks_free(range.begin);
  blocks_fclose(f);

  return EXIT_SUCCESS;
}

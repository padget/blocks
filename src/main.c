#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "srange.h"
#include "command.h"
#include "file.h"
#include "macro.h"

void blocks_free(void *ptr) { free(ptr); }
void blocks_println(const char *text) { printf("%s\n", text); }

int main(int argc, char const *argv[]) {
  blocks_println("Hello world");
  FILE *f = NULL;
  blocks_srange range;
  command c;

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
  else {
    {
      char *begin = c.name.begin;
      while (begin != c.name.end) {
        putc(*begin, stdout);
        begin++;
      }
    }
    printf("nb args %d \n", c.args.length);
    {
      int index = 0;
      blocks_srange *r = NULL;
      while (index < c.args.length) {
        r = &(c.args.args[index]);
        {
          char *begin = r->begin;
          while (begin != r->end) {
            putc(*begin, stdout);
            begin++;
          }
        }
        index++;
      }
    }
  }
  blocks_free(range.begin);
  blocks_fclose(f);

  return EXIT_SUCCESS;
}

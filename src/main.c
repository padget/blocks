#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "blocks_algorithm.h"
#include "file.h"
#include "macro.h"

struct srange_t {
  char *begin;
  char *end;
};

typedef struct srange_t name_t;
typedef struct srange_t arg_t;

/* Cette structure est une commande.
   Une commande comporte un nom et au maximum 4 arguments.
   si sur une ligne on detecte plus de 4 arguments, il s'agit d'une erreur de
   compilation.
  */
struct command_t {
  name_t n;
  arg_t a1;
  arg_t a2;
  arg_t a3;
  arg_t a4;
};

char *integer(char *begin, char *end) {
  contract_notnull(begin);
  contract_notnull(end);

  while ('0' <= *begin && *begin <= '9')
    begin++;
  return begin;
}

char *number(char *begin, char *end) {
  contract_notnull(begin);
  contract_notnull(end);

  return integer(begin, end);
}

char *argument(char *begin, char *end) {
  contract_notnull(begin);
  contract_notnull(end);

  return number(begin, end);
}

char *name(char *begin, char *end) {
  contract_notnull(begin);
  contract_notnull(end);

  while ('a' <= *begin && *begin <= 'z')
    begin++;
  return begin;
}

/* dans cette fonction je vais faire la construction d'une
   commande à partir d'une ligne de chaine de caractere
   pour cette première version je vais partir de l'hypothèse que
   ma ligne commence sans espace et qu'elle termine par un '\n'
*/
struct command_t build_command(char *begin, char *end) {
  contract_notnull(begin);
  contract_notnull(end);
  precond(begin != end);
  precond(*end == '\n' || *end == '\0');

  struct command_t c;

  char *cursor = begin;
  /* il me faut une fonction pour detecter les noms. */
  /* un nom est une suite de lettre minuscule exclusivement */
  /* cette fonction va renvoyer le pointeur vers la fin du nom */
  /* sachant que l'on connait le début du nom. IL y aura donc un */
  /* nom que si le pointeur de début est différent du pointeur de la fin */

  /* TODO Entre deux token il faut bien penser à bypasser les espaces*/
  
  cursor = name(begin, end);
  /* Nous vérifions maintenant qu'un nom a été detecté,
     sinon la ligne est malformée
  */
  if (cursor == begin) {
    puts("expected a name at the beginning of the command");
    return;
  }

  c.n.begin = begin;
  c.n.end = cursor;

  /* Nous avons une command avec un nom,
     regardons si les suivant sont des nombres qui servent d'argument
     à la commande */
  begin = cursor;
  cursor = argument(begin, end);

  if (cursor == begin) {
    puts("la commande n'a pas d'argument");
    return;
  }

  c.a1.begin = begin;
  c.a1.end = cursor;

  /* on vient de trouver un premier argument,
     essayons de voir s'il y a un deuxième argument*/
  begin = cursor;
  cursor = argument(begin, end);

  if (cursor == begin) {
    puts("la commande a un seul argument");
    return;
  }

  c.a2.begin = begin;
  c.a2.end = cursor;

  /* on vient de trouver un premier argument,
   essayons de voir s'il y a un deuxième argument*/
  begin = cursor;
  cursor = argument(begin, end);

  if (cursor == begin) {
    puts("la commande a un seul argument");
    return;
  }

  c.a3.begin = begin;
  c.a3.end = cursor;

  /* on vient de trouver un premier argument,
     essayons de voir s'il y a un deuxième argument*/
  begin = cursor;
  cursor = argument(begin, end);

  if (cursor == begin) {
    puts("la commande a un seul argument");
    return;
  }

  c.a4.begin = begin;
  c.a4.end = cursor;

  /* Nous avons donc une commande avec nom et quatre arguments*/
  return c;
}

int main(int argc, char const *argv[]) {
  char *buffer = NULL;
  blocks_io_file_to_buffer("examples/main.blocks", &buffer);
  /* j'ai tout dans un buffer. j'ai un pointeur sur le premier élément et je
   * connais la valeur du dernier élémnent.*/
  /* je peux donc itérer sur chaque caractère pour construire les commandes.*/
  /* construisons d'abord une simple commande sans gestion d'erreur. */
  /* une commande est un nom: nombre* */

  free(buffer);
  return EXIT_SUCCESS;
}

#ifndef __blocks_argument_h__
# define __blocks_argument_h__

# include "string.h"
# include <stdbool.h>

typedef struct
{
  char** args;
  size_t size;
} 
arguments;

/**
 * Construction d'une liste d'arguments à
 * partir des arguments fournis au programmes
 * au lancement de ce dernier.
 *
 * @param argv valeurs des arguments passés
 * @param argc nombre d'arguments passés
 * @return une liste d'arguments construites
 * sur la base des arguments passés
 */
arguments args_from_argv(char** argv, size_t size);

/**
 * Determinine si un argument en particulier existe
 * en fonction du nom passé en paramètre.
 *
 * @param args valeurs des arguments passés
 * @param name nom du paramètre recherché
 * @return true si la paramètre à été trouvé, 
 * false sinon
 */
bool args_exists(arguments* args, const char* name);

/**
 * Trouve dans la liste des arguments passés le
 * paramètre dont le nom est name. 
 *
 * @param args valeurs des arguments passés
 * @param name nom du paramètre que l'on veut 
 * retourné
 * @return l'argument dont le nom est name ou NULL
 * s'il n'est pas présent dans la liste
 */
char* args_find(arguments* args, const char* name);

/**
 * Trouve la valeur de l'argument dont le nom
 * est passé en paramètre dans la liste des 
 * arguments passés.
 *
 * @param args valeurs des arguments passés
 * @param name nom de l'argument dont on veut
 * la valeur
 * @return la valeur de l'argument dont le nom
 * est name. NULL si la valeur n'est pas présente
 */
char* args_value(arguments* args, const char* name);

/**
 * Trouve l'index de l'argument dont le nom 
 * est passsé dans la liste des arguments args.
 *
 * @param args valeurs des arguments passés
 * @param name nom de l'argument que l'on recherche
 * @return l'index de l'argument dont le nom est
 * passé en paramètre
 */
int args_pfind(arguments* args, const char* name);

/**
 * Un argument reprent le nom et la valeur d'un argument passé en paramètre.
 */
typedef struct
{
  char* name;
  char* value;
}
argument;

/**
 * Construit un argument si le nom d'argument passé
 * est trouvé dans la liste.
 *
 * @param args valeurs des arguments passés
 * @param name nom de l'argument que l'on veut construire
 * @return un argument construit si le nom est 
 * trouvé dans la liste des arguments passés. 
 */
argument args_argument(arguments* args, const char* name);


#endif

#ifndef __blocks_argument_h__
# define __blocks_argument_h__

# include "string.h"
# include <stdbool.h>


/**
 * arguments représente les arguments reçus
 * par le processus principal.
 * 
 * @param args la liste des valeurs des arguments
 * @param size la taille de la liste des arguments
 */ 
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
 * Determine si un argument en particulier existe
 * en fonction du nom passé en paramètre à l'emplacement
 * spécifique précisé.
 *
 * @param args valeurs des arguments passés
 * @param name nom du paramètre recherché
 * @param index localisation de l'argument
 * @return true si le paramètre existe à l'
 * emplacement indiqué
 */
bool args_exists_at(arguments* args, const char* name, int index);

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
 * Retourne l'argument situé à la localisation
 * indiqué par l'index passé en paramètre.
 *
 * @param args valeurs des arguments passés
 * @param index localisation recherchée
 * @return argument à la localisation index
 */
char* args_at(arguments* args, size_t index);

/**
 * Retourne un sous-ensemble des arguments passés
 * à partir d'un index de départ également passé.
 *
 * @param args valeurs des arguments passés
 * @param index index de départ à partir duquel va
 * démarrer le sous ensemble voulu
 * @return le sous ensemble d'arguments commençant
 * à partir de l'index.
 */
arguments args_subrange(arguments* args, int index);

/**
 * Un argument reprent le nom et la valeur 
 * d'un argument passé en paramètre.
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

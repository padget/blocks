#include "command_builder.h"
#include <stdlib.h>

#define  CMD_NAME_MAX 50
#define ARG_NAME_MAX 50
#define ARGS_MAX 10
#define CMDS_MAX 10000

// a command name is 50 length max;
// a argument name is 50 length max;
// there are 10 max argument per command;
// there are 10 000 max command per source;

// 
// [
//  [10000(50 + 10*2*50)] = 10Mo OK
// ]
//
// Nous obtenons une mémoire préconstruite
// de 10mo environs
//
// POur optimiser cela nous pouvons parcourir une 
// fois le fichier pour compte le nombre de 
// ligne dans celui ci (nombre de \n)
//
// Pour optimiser cela encore plus, on peut
// regarder si chacune de ces lignes est 'vide' 
// ou non. Mais cela veut dire parcourir le fichier
// dans sa globalité une seconde fois (on regarde une
// seconde fois pour chacune de ses lignes).
//

commands build_commands(char* source)
{

  char* memory = 
  
  while (*source != '\0')
  {
    // # build one command
    // ## build a name command
    //
  }
}


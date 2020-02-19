#include "command_builder.h"
#include <stdlib.h>
#include <stdio.h>

#define EOS '\0'
#define EOL '\n'

bool cnoteos(char *c)
{
	return c != NULL && *c != EOS;
}

bool cnoteol(char *c)
{
	return c != NULL && *c != EOL;
}

bool cisblank(char *c)
{
	return c != NULL && (*c == ' ' || *c == '\t');
}

bool cisdigit(char* c)
{
	return c != NULL && '0' <= *c && *c <= '9';
}

bool cislower(char* c)
{
	return c != NULL && 'a' <= *c && *c <= 'z';
}

void blc_cmds_init_cstr(int nb, blc_command *cmds)
{
	int i = 0;

	while (i < nb)
	{
		cmds[i].name[0] = EOS;

		int j = 0;
		while (j < ARGS_MAX)
		{
			cmds[i].args[j].type[0] = EOS;
			cmds[i].args[j].value[0] = EOS;
			++j;
		}

		i++;
	}
}

blc_command *
blc_cmds_init(size_t nb)
{
	size_t s_cmd = sizeof(blc_command);
	size_t s_cmds = nb * s_cmd;

	blc_command *cmds = malloc(s_cmds);
	blc_cmds_init_cstr(nb, cmds);

	return cmds;
}

char *overblank(char *c)
{
	while (cisblank(c))
		c++;
	return c;
}

char *overcmdname(char *c)
{
	while (cislower(c))
		c++;
	if (c != NULL && *c == ':')
		c++;
	return c;
}

char *overargnumber(char *c)
{
	while (cisdigit(c))
		c++;
	return c;
}

char *untileol(char *c)
{
	while (cnoteos(c) && cnoteol(c))
		c++;
	return c;
}

bool isblankline(char *b, char *e)
{
	while (b != e)
	{
		if (cisblank(b))
			b++;
		else
			break;
	}

	return b == e;
}

char *overblanklines(char *c)
{
	char *b = c;
	char *e = c;

	while (isblankline(b, e = untileol(b)))
	{
		b = e + 1;
		printf("je saute une ligne vide\n");
	}
	return b;
}

void copy(char *b, char *e, char *buf)
{
	while (b != e)
	{
		*buf = *b;
		++buf;
		++b;
	}

	*buf = '\0';
}

bool checkcmdname(char *b, char *e)
{
	int s = e - b;
	bool not_empty = 0 < s && s < CMD_NAME_MAX;
	bool start_letter = not_empty && cislower(b);
	bool end_colon = not_empty && *(e - 1) == ':';
	return start_letter && end_colon;
}

bool checkargnumber(char *b, char *e)
{
	int s = e - b;
	return 0 < s && s < ARG_VALUE_MAX;
}

void blc_cmds_fill(size_t nb, blc_command *cmds, char *src)
{
	size_t i = 0;

	while (cnoteos(src) && i < nb)
	{
		char *bol = overblanklines(src);
		char *eol = untileol(bol);

		bol = overblank(bol);

		char *bname = bol;
		char *ename = bol;

		ename = overcmdname(ename);

		if (checkcmdname(bname, ename))
			copy(bname, ename, cmds[i].name);
		else
			// TODO error
			return;

		bol = ename;
		bol = overblank(bol);

		size_t j = 0;
		char *bargs = bol;
		char *eargs = eol;

		while (bargs != eargs && j < ARGS_MAX)
		{
			char *bnb = bargs;
			char *enb = bargs;

			enb = overargnumber(enb);

			if (checkargnumber(bnb, enb))
				copy(bnb, enb, cmds[i].args[j].value);
			else
				// TODO erreur
				return;

			enb = overblank(enb);

			++j;
			bargs = enb;
		}

		if (j == ARGS_MAX && bargs != eargs)
			// TODO ERROR
			return;

		++i;

		if (*eol == EOS)
			src = eol;
		else
			src = eol + 1;
	}

	if (i == nb && cnoteos(src))
		// TODO ERROR
		return;
}

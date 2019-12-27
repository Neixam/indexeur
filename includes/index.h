/* ************************************************************************** */
/*                                                                            */
/*                              index.h                                       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDEX_H
# define INDEX_H
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

typedef struct  celpos
{
    int             position;
    struct celpos   *suivant;
}               Celpos,
                *Listepos; /* pour les positions des mots*/

typedef struct  celmot
{
    char        *mot;
    Listepos    positions;
}               Celmot;   /* pour les mots et l'acces aux positions */

typedef struct  cellule
{
    Celmot          *valeur;
    struct cellule  *suivant;
}               Cellule,
                *Liste;   /* pour les listes chainées de mots*/

typedef struct  entrer
{
    int     flag;
    FILE    *content;
    char    *name;
}               Entrer;

int     ft_strchr(char *s, int c);
int     menu(void);
int     option_flag(char arg, Entrer *data);
int     put_error(int type_error);
int     start_index(Entrer data);
int     traite_argument(int ac, char **av, Entrer *data);

char	*ft_strdup(char *s);
char	*ft_strstr(char *s1, char *s2);

#endif
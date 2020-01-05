/* ************************************************************************** */
/*                                                                            */
/*                                 lst.c                                      */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

Listepos    alloue_lst_pos(int position)
{
    Listepos    ret;

    if ((ret = (Listepos)malloc(sizeof(Celpos))) == NULL)
        return (NULL);
    ret->position = position;
    ret->suivant = NULL;
    return (ret);
}

Celmot      alloue_cell_mot(char *mot, int position)
{
    Celmot  ret;

    if ((ret.positions = alloue_lst_pos(position)) == NULL)
    {
        ret.mot = NULL;
        return (ret);
    }
    ft_convert_case(mot);
    if ((ret.mot = ft_strdup(mot)) == NULL)
    {
        free(ret.positions);
        ret.positions = NULL;
        return (ret);
    }
    return (ret);
}

Liste       alloue_lst(char *mot, int position)
{
    Liste   ret;
    Celmot  test;

    test = alloue_cell_mot(mot, position);
    if (test.mot == NULL || test.positions == NULL)
        return (NULL);
    if ((ret = (Liste)malloc(sizeof(Cellule))) == NULL)
        return (NULL);
    if ((ret->valeur = (Celmot*)malloc(sizeof(Celmot))) == NULL)
        return (NULL);
    *(ret->valeur) = test;
    ret->suivant = NULL;
    return (ret);
}

int         mot_in_lst(Liste lst, char *mot)
{
    int     i;

    for (i = 0; lst != NULL; lst = lst->suivant)
    {
        if (strcmp(lst->valeur->mot, mot) == 0)
            return (i);
        i++;
    }
    return (-1);
}

int         ajout_position(Listepos *pos, int position)
{
    Listepos    tmp;
    Listepos    tmp2;

    for (tmp = *pos; (*pos) && ((*pos)->suivant); *pos = (*pos)->suivant)
    {
        tmp2 = (*pos)->suivant;
        if (position >= (*pos)->position && position <= tmp2->position)
        {
            if (!((*pos)->suivant = alloue_lst_pos(position)))
                return (1);
            (*pos)->suivant->suivant = tmp2;
            *pos = tmp;
            return (0);
        }
    }
    if (!((*pos)->suivant = alloue_lst_pos(position)))
        return (1);
    *pos = tmp;
    return (0);
}

int     ajout_mot(Liste *lst, char *mot, int position)
{
    int     i;
    Liste   tmp;
    Liste   tmp2;

    if (!(*lst))
    {
        if (!((*lst) = alloue_lst(mot, position)))
            return (1);
        return (0);
    }
    if ((i = mot_in_lst(*lst, mot)) != -1)
    {
        for (tmp = *lst; i > 0; *lst = (*lst)->suivant)
            i--;
        if (ajout_position(&((*lst)->valeur->positions), position))
        {
            *lst = tmp;
            return (1);
        }
        *lst = tmp;
        return (0);
    }
    if (strcmp(mot, (*lst)->valeur->mot) < 0)
    {
        tmp = *lst;
        if (!((*lst) = alloue_lst(mot, position)))
            return (1);
        (*lst)->suivant = tmp;
        return (0);
    }
    for (tmp = *lst; (*lst) && ((*lst)->suivant); *lst = (*lst)->suivant)
    {
        tmp2 = (*lst)->suivant;
        if (strcmp(mot, (*lst)->valeur->mot) > 0 && strcmp(mot, tmp2->valeur->mot) < 0)
        {
            if (!((*lst)->suivant = alloue_lst(mot, position)))
                return (1);
            (*lst)->suivant->suivant = tmp2;
            *lst = tmp;
            return (0);
        }
    }
    if (!((*lst)->suivant = alloue_lst(mot, position)))
        return (1);
    *lst = tmp;
    return (0);
}

int     compte_mot(Liste lst)
{
    int     i;

    for (i = 0; lst; lst = lst->suivant)
        i++;
    return (i);
}
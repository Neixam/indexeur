/* ************************************************************************** */
/*                                                                            */
/*                               index.c                                      */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int     add_to_tab(Liste *lst1, Liste lst2)
{
    Liste   tmp;

    if ((*lst1) == NULL)
    {
        if (!(*lst1 = (Liste)malloc(sizeof(Cellule))))
            return (1);
        (*lst1)->valeur = lst2->valeur;
        (*lst1)->suivant = NULL;
        return (0);
    }
    for (tmp = *lst1; (*lst1)->suivant; *lst1 = (*lst1)->suivant);
    if (!((*lst1)->suivant = (Liste)malloc(sizeof(Cellule))))
        return (1);
    (*lst1)->suivant->valeur = lst2->valeur;
    (*lst1)->suivant->suivant = NULL;
    (*lst1) = tmp;
    return (0);
}

int     index_mot(Liste lst, Entrer data)
{
    Liste   *tab_hache;
/*    Liste   tmp;
    Listepos tmp2;*/
    int     len;
    int     i;

    len = compte_mot(lst) / 5;
    if ((tab_hache = (Liste*)malloc(sizeof(Liste) * len)) == NULL)
        return (1);
    for (i = 0; i < len; i++)
        tab_hache[i] = NULL;
    for (tmp = lst; tmp; tmp = tmp->suivant)
        if (add_to_tab(&tab_hache[hache(tmp->valeur->mot) % len], tmp))
            return (1);
/*    for (i = 0; i < len; i++)
    {
        printf("%d => ", i);
        if (tab_hache[i] == NULL)
            printf("NULL");
        else
            for (tmp = tab_hache[i]; tmp; tmp = tmp->suivant)
            {
                printf("%s pos : ", tmp->valeur->mot);
                for (tmp2 = tmp->valeur->positions; tmp2; tmp2 = tmp2->suivant)
                    printf("%d ", tmp2->position);
                if (tmp->suivant)
                    printf("--> ");
            }
        printf("\n");
    }*/
    return (0);
}

int     start_index(Entrer data)
{
    char    buff[BUFF_SIZE];
    int     i;
    int     j;
    int     len;
    char    *mot;
    Liste   lst;
/*    Liste   tmp;
    Listepos tmp2;*/

    lst = NULL;
    for (data.octet = 0; ft_fgets_phrase(buff, BUFF_SIZE, data.content);
        data.octet += len)
    {
        ft_convert_case(buff);
        len = strlen(buff);
        for (i = 0; i < len; i++)
        {
            if (buff[i] >= 'a' && buff[i] <= 'z')
            {
                for (j = 0; i + j < len && buff[i + j] >= 'a' &&
                            buff[i + j] <= 'z'; j++);
                if ((mot = ft_strndup(&buff[i], j)) == NULL)
                    return (1);
                if (ajout_mot(&lst, mot, data.octet))
                    return (1);
                i += j;
                free(mot);
            }
        }
    }
/*    for (tmp = lst; tmp; tmp = tmp->suivant)
    {
        printf("mot => %s => pos : ", tmp->valeur->mot);
        for (tmp2 = tmp->valeur->positions; tmp2; tmp2 = tmp2->suivant)
            printf("%d ", tmp2->position);
        printf("\n");
    } */
    if (index_mot(lst, data))
        return (1);
    return (0);
}
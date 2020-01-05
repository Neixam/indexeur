/* ************************************************************************** */
/*                                                                            */
/*                               index.c                                      */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

void    libere_pos(Listepos pos)
{
    if (pos->suivant != NULL)
        libere_pos(pos->suivant);
    free(pos);
    pos = NULL;
}

void    libere_mot(Celmot *val)
{
    if (val->positions != NULL)
        libere_pos(val->positions);
    free(val->mot);
    free(val);
    val = NULL;
}

void    libere_lst(Liste lst)
{
    if (lst->valeur != NULL)
        libere_mot(lst->valeur);
    if (lst->suivant != NULL)
        libere_lst(lst->suivant);
    free(lst);
}

void    libere_lst_tab(Liste lst)
{
    if (lst != NULL)
    {
        libere_lst_tab(lst->suivant);
        lst->valeur = NULL;
        free(lst);
    }
}

void    libere_espace(Liste *tab, int N, Liste lst, Entrer *data)
{
    int     i;

    libere_lst(lst);
    for (i = 0; i < N; i++)
        libere_lst_tab(tab[i]);
    if (data->name != NULL)
    {
        free(data->name);
        data->name = NULL;
    }
    if (data->content != NULL)
    {
        fclose(data->content);
        data->content = NULL;
    }
    if (data->mot != NULL)
    {
        free(data->mot);
        data->mot = NULL;
    }
}

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
    Liste   tmp;
    int     len;
    int     i;

    len = compte_mot(lst) * 3;
    if ((tab_hache = (Liste*)malloc(sizeof(Liste) * len)) == NULL)
        return (1);
    for (i = 0; i < len; i++)
        tab_hache[i] = NULL;
    for (tmp = lst; tmp; tmp = tmp->suivant)
        if (add_to_tab(&tab_hache[hache(tmp->valeur->mot) % len], tmp))
            return (1);
/*    put_S(tab_hache, len);*/
/*    put_vide(tab_hache, len); */
    if (traite_tab_flag(tab_hache, len, data, lst))
        return (1);
    libere_espace(tab_hache, len, lst, &data);
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

    lst = NULL;
    for (data.octet = 0; ft_fgets_phrase(buff, BUFF_SIZE, data.content) != 0;
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
    if (index_mot(lst, data))
        return (1);
    return (0);
}
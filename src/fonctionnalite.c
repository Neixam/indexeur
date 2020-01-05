/* ************************************************************************** */
/*                                                                            */
/*                            fonctionnalite.c                                */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int     affiche_ret_1(Liste *tab, int N, int flag, char *mot)
{
    int         i;
    int         len;
    int         test;
    Liste       tmp;
    Listepos    tmp2;

    if (ft_strchr("ap", flag) != -1)
    {
        if ((i = mot_in_lst(tab[hache(mot) % N], mot)) == -1)
        {
            if (flag == 'a')
                printf("%s n'appartient pas au texte.\n", mot);
            else
                printf("Le mot %s n'a aucune position dans le texte.\n", mot);
        }
        else
        {
            if (flag == 'a')
                printf("%s appartient au texte.\n", mot);
            else
            {
                printf("Voici les positions du mot %s : ", mot);
                for (tmp = tab[hache(mot) % N]; i > 0; tmp = tmp->suivant)
                    i--;
                for (tmp2 = tmp->valeur->positions; tmp2; tmp2 = tmp2->suivant)
                {
                    printf("%d", tmp2->position);
                    if (tmp2->suivant)
                        printf(" ");
                    else
                        printf("\n");
                }
            }
        }
    }
    else
    {
        len = strlen(mot);
        test = 0;
        printf("Voici les mots qui ont pour prefixe %s :\n", mot);
        for (i = 0; i < N; i++)
        {
            for (tmp = tab[i]; tmp; tmp = tmp->suivant)
            {
                if (strncmp(mot, tmp->valeur->mot, len) == 0)
                {
                    printf("%s\n", tmp->valeur->mot);
                    test = 1;
                }
            }
        }
        if (test == 0)
            printf("Aucun résultat.\n");
    }
    return (0);
}

int     affiche_ret_2(Liste lst)
{
    Liste   tmp;
    char    first;
    int     test;

    first = 'a';
    test = 1;
    for (tmp = lst; tmp; tmp = tmp->suivant)
    {
        if (tmp->valeur->mot[0] != first)
        {
            test = 1;
            first = tmp->valeur->mot[0];
        }
        if (test)
        {
            printf("\nLes mots commençants par %c\n", first);
            test = 0;
        }
        printf("%s\n", tmp->valeur->mot);
    }
    return (0);
}

int     affiche_ret_3(Liste *tab, int N, FILE *stream, char *mot)
{
    int         i;
    char        *phrase;
    Liste       tmp;
    Listepos    tmp2;

    tmp = tab[hache(mot) % N];
    if ((i = mot_in_lst(tmp, mot)) == -1)
        printf("Le mot %s n'apparait dans aucune phrase du texte.\n", mot);
    else
    {
        for (; i > 0; tmp = tmp->suivant)
            i--;
        for (tmp2 = tmp->valeur->positions; tmp2; tmp2 = tmp2->suivant)
        {
            fseek(stream, tmp2->position, SEEK_SET);
            if ((phrase = ft_fgets_phrase_2(stream)) == NULL)
                return (1);
            printf("%s\n", phrase);
            free(phrase);
        }
    }
    return (0);
}

int     enregistre_lst(Liste lst, char *name)
{
    FILE        *dico;
    char        *nw_name;
    Liste       tmp;
    Listepos    tmp2;

    if ((nw_name = ft_strjoin(name, ".DICO", 0)) == NULL)
        return (1);
    if ((dico = fopen(nw_name, "w")) == NULL)
        return (1);
    for (tmp = lst; tmp; tmp = tmp->suivant)
    {
        fprintf(dico, "%s : ", tmp->valeur->mot);
        for (tmp2 = tmp->valeur->positions; tmp2; tmp2 = tmp2->suivant)
            fprintf(dico, "%d%c", tmp2->position, (tmp2->suivant) ? ' ' : '\n');
    }
    fclose(dico);
    return (0);
}

int     traite_tab_flag(Liste *tab, int N, Entrer data, Liste lst)
{
    if (ft_strchr("apPld", data.flag) != -1)
    {
        if (ft_strchr("apd", data.flag) != -1)
            return (affiche_ret_1(tab, N, data.flag, data.mot));
        if (ft_strchr("l", data.flag) != -1)
            return (affiche_ret_2(lst));
        else
            return (affiche_ret_3(tab, N, data.content, data.mot));
    }
    return (enregistre_lst(lst, data.name));
}
/* ************************************************************************** */
/*                                                                            */
/*                               menu.c                                       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

char    *saisie_choix(void)
{
    char    *choix;
    char    tmp;

    if (!(choix = (char*)malloc(sizeof(char))) == NULL)
        return (NULL);
    do
    {
        tmp = getchar();
        if (tmp != '\n')
            if (!(choix = ft_stradd(choix, tmp)))
                return (NULL);
    }while (tmp != '\n');
    return (choix);
}

int     select_fichier(Entrer *data)
{
    char    *choix;

    printf("Entrer le nom de votre fichier (.ascii) : ");
    if (!(choix = saisie_choix()))
        return (-1);
    if (strcmp(choix, "quit") == 0)
        return (2);
    if (!ft_strstr(choix, ".ascii"))
        return (0);
    if (!(data->content = fopen(choix, "r")))
        return (0);
    if (!(data->name = ft_strdup(choix)))
        return (-1);
    free(choix);
    return (1);
}

int     select_mode(Entrer *data)
{
    char    *choix;
    int     ret;

    printf("Saisir la fonctionnalité parmis celles-ci dessous :\n\
    - p : affiche la suite des positions de votre mot dans le texte\t\t\t- D \
    : sauve dans un fichier la liste triée des mots du texte et leur position\
     dans\n- P : affiche les phrases du texte contenant votre mot\t\tun \
    fichier. Le fichier aura pour nom le nom du fichier entré suivi du suffixe\n\
    - l : affiche la liste triée des mots du texte\t\t\t\".DICO\". Chaque \
    ligne de ce fichier sera constituée d'un mot suivit de la liste\n\
    - d : affiche l'ensemble des mots du texte ayant votre mot pour préfixe.\
    \t\t\tde ses positions.\n- a : teste l'appartenance de votre mot au texte\n");
    if (!(choix = saisie_choix()))
        return (-1);
    if (strcmp(choix, "quit") == 0)
        return (2);
    ret = option_flag(choix[0], data);
    free(choix);
    return (ret);
}

int     menu(void)
{
    Entrer  data;
    int     controle;
    char    *choix;

    choix = NULL;
    do {
    while ((controle = select_fichier(&data)) != 1)
    {
        if (controle == 2)
            return (0);
        if (controle == -1)
            return (put_error(0));
        printf("Fichier introuvable.\n");
    }
    while ((controle = select_mode(&data)) != 1)
    {
        if (controle == 2)
            return (0);
        if (controle == -1)
            return (put_error(0));
        printf("Option inconnue.\n");
    }
    if (choix != NULL)
        free(choix);
    if (ft_strchr("apPd", data.flag) != -1)
    {
        printf("Entrer un mot : ");
        if (!(choix = saisie_choix()))
            return (put_error(0));
    }
    }while (strcmp(choix, "quit") != 0);
    free(choix);
    return (0);
}
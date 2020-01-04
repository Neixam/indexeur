/* ************************************************************************** */
/*                                                                            */
/*                               menu.c                                       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

char    *saisie_choix(void)
{
    char    *choix;
    char    *line;
    char    buff[BUFF_SIZE];

    if (!(line = (char*)malloc(sizeof(char))))
        return (NULL);
    *line = '\0';
    do
    {
        if (fgets(buff, BUFF_SIZE, stdin) == NULL)
            return (NULL);
        if (!(line = ft_strjoin(line, buff, 1)))
            return (NULL);
    }while  (ft_strchr(buff, '\n') == -1);
    if ((choix = ft_strsupp(line)) == NULL)
        return (NULL);
    return (choix);
}

int     select_fichier(Entrer *data)
{
    char    *choix;

    printf("Entrer le nom de votre fichier (.ascii) :\n");
    if (!(choix = saisie_choix()))
        return (-1);
    if (strcmp(choix, "quit") == 0)
        return (2);
    if (!ft_strstr(choix, ".ascii") || !(data->content = fopen(choix, "r")))
    {
        free(choix);
        return (0);
    }
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
- p : affiche la suite des positions de votre mot dans le texte\n- D \
: sauve dans un fichier la liste triée des mots du texte et leur position\
 dans un fichier. Le fichier aura pour nom le nom du fichier entré suivi \
du suffixe \".DICO\". Chaque ligne de ce fichier sera constituée d'un mot \
suivit de la liste de ses positions\n\
- P : affiche les phrases du texte contenant votre mot\n\
- l : affiche la liste triée des mots du texte\n\
- d : affiche l'ensemble des mots du texte ayant votre mot pour préfixe.\
\n- a : teste l'appartenance de votre mot au texte\n");
    choix = NULL;
    if (!(choix = saisie_choix()))
        return (-1);
    if (strcmp(choix, "quit") == 0)
        return (2);
    ret = option_flag(choix[0], data);
    if (choix != NULL)
        free(choix);
    return (ret);
}

int     restart(Entrer *data)
{
    char    *choix;

    printf("Voulez-vous recommencer ?(y/n)\n");
    choix = NULL;
    if (!(choix = saisie_choix()))
        return (2);
    data->flag = -1;
    ft_convert_case(choix);
    if (strcmp(choix, "y") == 0 || strcmp(choix, "o") == 0 ||
        strcmp(choix, "oui") == 0 || strcmp(choix, "yes") == 0)
        data->flag = 1;
    else if (strcmp(choix, "n") == 0 || strcmp(choix, "no") == 0 ||
        strcmp(choix, "non") == 0)
        data->flag = 0;
    if (data->flag == -1)
        return (1);
    return (0);
}

int     menu(void)
{
    Entrer  data;
    int     controle;

    while ((controle = select_fichier(&data)) != 1)
    {
        if (controle == 2)
            return (0);
        if (controle == -1)
            return (put_error(0));
        printf("Fichier introuvable.\n");
    }
    while ((controle = select_mode(&data)) != 0)
    {
        if (controle == 2)
            return (0);
        if (controle == -1)
            return (put_error(0));
        printf("Option inconnue.\n");
    }
    if (ft_strchr("apPd", data.flag) != -1)
    {
        printf("Entrer un mot : ");
        if (!(data.mot = saisie_choix()))
            return (put_error(0));
    }
    if (start_index(data))
        return (put_error(0));
    while ((controle = restart(&data)) != 0)
        if (controle == 2)
            return (put_error(0));
    if (data.flag == 1)
        return (menu());
    return (0);
}
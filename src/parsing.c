/* ************************************************************************** */
/*                                                                            */
/*                              parsing.c                                     */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int     option_flag(char argument, Entrer *data)
{
    if (argument != 'a' && argument != 'p' && argument != 'P' &&
        argument != 'd' && argument != 'D' && argument != 'l')
        return (1);
    data->flag = argument;
    return (0);
}

int     traite_argument(int ac, char **av, Entrer *data)
{
    if (ac > 4 || ft_strchr(av[1], '-') != 0 || strlen(av[1]) != 2)
        return (1);
    if (option_flag(av[1][1], data) || !(ft_strstr(av[ac - 1], ".ascii")))
        return (1);
    if ((data->name = ft_strdup(av[ac - 1])) == NULL)
        return (1);
    if (ac == 3)
    {
        if (ft_strchr("lD", data->flag) == -1)
            return (1);
    }
    else if (ac == 4)
    {
        if (ft_strchr("apPd", data->flag) == -1)
            return (1);
    }
    else
        return (1);
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                               main.c                                       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

void    initialise(Entrer *data)
{
    data->flag = 0;
    data->content = NULL;
    data->octet = 0;
    data->name = NULL;
    data->mot = NULL;
}

int     main(int ac, char **av)
{
    Entrer  data;

    errno = 0;
    initialise(&data);
    if (ac == 1)
        return (menu());
    else
    {
        if (traite_argument(ac, av, &data))
            return (put_error(1));
        if (!(data.content = fopen(data.name, "r")))
            return (put_error(0));
        if (start_index(data))
            return (put_error(0));
    }
    return (0);
}
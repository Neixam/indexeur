/* ************************************************************************** */
/*                                                                            */
/*                              error.c                                       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int     put_error(int type_error)
{
    if (type_error)
        fprintf(stderr, "Bad enter option :\n./Index [-question [mot] Fichier]\nquestion: -apPldD\n");
    if (errno != 0)
        fprintf(stderr, "%s\n", strerror(errno));
    return (errno);
}
/* ************************************************************************** */
/*                                                                            */
/*                                 hachage.c                                  */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

unsigned int    hache(char *p)
{
    unsigned int    h;
    unsigned int    g;

    for (h = 0; *p; p++)
    {
        h = (h<<4)+*p;
        if ((g = h & 0xf0000000)) 
        /*il y a des valeurs dans les 4 bits de poids fort*/
        {
            h = h ^ (g>>24); /*elles vont influencer l'octet de poids faible*/
            h = h ^ g;       /*on les supprime du haut de h*/
        }
    }
    return (h);
}
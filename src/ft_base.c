/* ************************************************************************** */
/*                                                                            */
/*                              ft_base.c                                     */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int		ft_strchr(char *s, int c)
{
	int		i;

	for (i = 0; i >= 0; i++)
		if (s[i] == c)
			return (i);
	return (-1);
}

char	*ft_strstr(char *s1, char *s2)
/* BUT    : Cherche la première occurence de la chaine s2 dans la chaine s1   */
/* PARAM  : s1 => chaine de charactère botte de foin                          */
/*          s2 => chaine de charactère aiguille                               */
/* RETOUR : Renvoie l'adresse du premier charactère de l'occurence de s2 dans */
/*          s1 si il y a un occurence sinon renvoie NULL                      */
{
	int		i;
	int		j;

	for (i = 0; s1[i] != '\0'; i++)
	{
		for (j = 0; s1[i + j] == s2[j] && s2[j] != '\0' && s1[i + j] != '\0'; j++);
		if (s2[j] == '\0')
			return (&s1[i + 1]);
	}
	return (NULL);
}


char	*ft_strdup(char *s)
/* BUT    : Alloue une nouvelle chaîne de charactère dont le contenue est s   */
/* PARAM  : s => chaîne de charactère dont on veut copier le contenue         */
/* RETOUR : retourne la nouvelle chaîne de charactère créée                   */
{
	int		len;
	int		i;
	char	*ret;

	len = strlen(s);
	if ((ret = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	for (i = 0; i < len; i++)
		ret[i] = s[i];
	ret[i] = '\0';
	return (ret);
}

char	*ft_stradd(char *s, int c)
/* BUT    : Ajoute le charactère c à la fin de la chaine de charactère s      */
/* PARAM  : s => chaine de charactère à changer                               */
/*          c => charactère à ajouter                                         */
/* RETOUR : Renvoie la nouvelle chaine de charactère s avec le charactère c   */
{
	int		len;
	int		i;
	char	*ret;

	len = ft_strlen(s) + 1;
	if ((ret = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	for (i = 0; i < len - 1; i++)
		ret[i] = s[i];
	ret[i] = c;
	ret[i + 1] = '\0';
	free(s);
	return (ret);
}
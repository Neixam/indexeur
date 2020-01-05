/* ************************************************************************** */
/*                                                                            */
/*                              ft_base.c                                     */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int		ft_strchr(char *s, int c)
{
	int		i;

	for (i = 0; s[i] != '\0'; i++)
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

	len = strlen(s) + 1;
	if ((ret = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	for (i = 0; i < len - 1; i++)
		ret[i] = s[i];
	ret[i] = c;
	ret[i + 1] = '\0';
	free(s);
	return (ret);
}

char	*ft_strjoin(char *s1, char *s2, int boo)
/* BUT    : Crée une nouvelle chaine contenant la concaténation de s1 et s2 et*/
/*          peut libèrer l'espace mémoire de s1 et s2 si possible             */
/* PARAM  : s1  => première chaine de charactère                              */
/*          s2  => seconde chaine de charactère                               */
/*          boo => 0 libère aucune chaine, 1 libère s1, 2 libère s2 et libère */
/*                 toute les chaines avec 3                                   */
/* RETOUR : Renvoie la nouvelle chaine de charactère ou NULL si il y a un     */
/*          problème d'allocation mémoire                                     */
{
	int		i;
	int		j;
	int		len;
	char	*ret;

	len = strlen(s1) + strlen(s2);
	if (!(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	for (i = 0; s1[i] != '\0'; i++)
		ret[i] = s1[i];
	j = i;
	for (i = 0; s2[i] != '\0'; i++)
	{
		ret[j] = s2[i];
		j++;
	}
	ret[j] = '\0';
	if (boo == 1 || boo == 3)
		free(s1);
	if (boo == 2 || boo == 3)
		free(s2);
	return (ret);
}

char	*ft_strsupp(char *s)
/* BUT    : Retire le dernier charactère de la chaine s                       */
/* PARAM  : Chaine de charactère que l'on veut modifier                       */
/* RETOUR : La nouvelle chaine de charactère s sans le dernier charactère     */
{
	int		i;
	int		len;
	char	*ret;

	len = strlen(s) - 1;
	if ((ret = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	for (i = 0; i < len; i++)
		ret[i] = s[i];
	ret[i] = '\0';
	free(s);
	return (ret);
}

void	ft_convert_case(char *s)
{
	int		i;

	for (i = 0; s[i] != '\0' ; i++)
		if (s[i] <= 'Z' && s[i] >= 'A')
			s[i] += 32;
}

int		ft_fgets_phrase(char *buff, int size, FILE *stream)
{
	char	tmp;
	int		i;

	for (i = 0; (tmp = fgetc(stream)) != EOF && i < size - 1; i++)
	{
		buff[i] = tmp;
		if (ft_strchr(".?!", tmp) != -1)
		{
			i++;
			break;
		}
	}
	buff[i] = '\0';
	if (tmp == EOF && i == 0)
		return (0);
	return (1);
}

char	*ft_strndup(char *s, int n)
{
	int		len;
	int		i;
	char	*ret;

	len = n;
	if ((ret = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	for (i = 0; i < len; i++)
		ret[i] = s[i];
	ret[i] = '\0';
	return (ret);
}
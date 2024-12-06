/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:12:43 by amezioun          #+#    #+#             */
/*   Updated: 2024/07/14 00:07:16 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s)
{
	int		i;
	char	*cpy;

	i = 0;
	if (!s)
		return (NULL);
	cpy = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!cpy)
		return (NULL);
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	while (s1[i] && s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j] && s2[j] != '\0')
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (free(s1), s1 = NULL, result);
}

int	contains_nl(char *sbuff)
{
	int	i;

	i = 0;
	if (!sbuff)
		return (-1);
	while (sbuff[i] && sbuff[i] != '\0')
	{
		if (sbuff[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*copy_until_nl(char *sbuff)
{
	char	*cunl;
	int		i;

	i = 0;
	if (!sbuff[0])
		return (NULL);
	while (sbuff[i] && sbuff[i] != '\n')
		i++;
	cunl = malloc(i + 1);
	if (!cunl)
		return (NULL);
	i = 0;
	while (sbuff[i] && sbuff[i] != '\n')
	{
		cunl[i] = sbuff[i];
		i++;
	}
	cunl[i] = '\0';
	i++;
	return (cunl);
}

char	*copy_after_nl(char *in)
{
	char	*anl;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!in)
		return (NULL);
	while (in[i] && in[i] != '\n')
		i++;
	if (!in[i])
	{
		free(in);
		return (NULL);
	}
	anl = malloc((ft_strlen(in) - i) + 1);
	i++;
	if (!anl)
		return (NULL);
	while (in[i] != '\0')
		anl[j++] = in[i++];
	anl[j] = '\0';
	return (free(in), anl);
}

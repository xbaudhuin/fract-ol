/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:50:25 by xabaudhu          #+#    #+#             */
/*   Updated: 2023/12/13 16:22:52 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_line(char const *s, char c)
{
	size_t	line;
	size_t	i;
	int		flag;

	flag = 1;
	i = 0;
	line = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 1)
		{
			line++;
			flag = 0;
		}
		if (s[i] == c && flag == 0)
			flag = 1;
		i++;
	}
	return (line);
}

void	free_split(char **split, size_t k)
{
	while (k != 0)
	{
		free(split[k]);
		k--;
	}
	free(split[0]);
	free(split);
}

static char	**fill_split(char const *s, char c, char **split, size_t line)
{
	size_t	i;
	size_t	j;
	size_t	k;

	k = 0;
	i = 0;
	while (k < line)
	{
		while (s[i] && s[i] == c)
			i++;
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		split[k] = ft_substr(s, i, j);
		if (!split[k])
			return (free_split(split, k), NULL);
		i += j;
		k++;
	}
	split[k] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	size_t	line;
	char	**split;

	if (!s)
		return (NULL);
	line = count_line(s, c);
	split = malloc(sizeof(*split) * (line + 1));
	if (!split)
		return (NULL);
	split = fill_split(s, c, split, line);
	return (split);
}

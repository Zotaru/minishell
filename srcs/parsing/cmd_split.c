/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:03:59 by jehubert          #+#    #+#             */
/*   Updated: 2023/07/26 21:12:16 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count(const char *str, char *c, int i[2])
{
	int		cond[2];

	cond[0] = 0;
	cond[1] = 0;
	while (str[i[0]])
	{
		if (!ft_strchr(c, str[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(c, str[i[0]]) || cond[0]) && str[i[0]])
			{
				if (!cond[1] && (str[i[0]] == '\"' || str[i[0]] == '\''))
					cond[1] = str[i[0]];
				cond[0] = (cond[0] + (str[i[0]] == cond[1])) % 2;
				cond[1] *= cond[0] != 0;
				i[0]++;
			}
			if (cond[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static char	**ft_fill(char **res, char const *str, char *sep, int i[3])
{
	int		s_len;
	int		cond[2];

	cond[0] = 0;
	cond[1] = 0;
	s_len = ft_strlen(str);
	while (str[i[0]])
	{
		while (ft_strchr(sep, str[i[0]]) && str[i[0]])
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(sep, str[i[0]]) || cond[0] || cond[1]) && str[i[0]])
		{
			cond[0] = (cond[0] + (!cond[1] && str[i[0]] == '\'')) % 2;
			cond[1] = (cond[1] + (!cond[0] && str[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= s_len)
			res[i[2]++] = "\0";
		else
			res[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
	}
	return (res);
}

char	**ft_cmd_split(char const *str, char *sep)
{
	char	**res;
	int		nbw;
	int		i[3];
	int		j[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	j[0] = 0;
	j[1] = 0;
	if (!str)
		return (NULL);
	nbw = ft_count(str, sep, j);
	if (nbw < 1)
		return (NULL);
	res = malloc((nbw + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res = ft_fill(res, str, sep, i);
	res[nbw] = NULL;
	return (res);
}

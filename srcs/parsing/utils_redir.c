/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:39:46 by jehubert          #+#    #+#             */
/*   Updated: 2023/06/29 18:47:36 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pass_space(char *str, int *i, int *n)
{
	while (str[*i] != ' ' && str[*i] != '\t' && !ft_isalnum(str[*i])
		&& str[*i] != '/' && str[*i] != ';' && str[*i] != ':'
		&& str[*i] != '$' && str[*i])
		(*i)++;
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (str[*i] == '\'' || str[*i] == '\"')
		(*n)++;
}

int	ft_next_redir(char *str, int i)
{
	if (i >= (int)ft_strlen(str))
		return (i);
	while (str[i])
	{
		if ((str[i] == '>' || str[i] == '<')
			&& ft_get_state(str, i) == base)
			return (i);
		i++;
	}
	return (i);
}

int	ft_check_parse_redir(char *str, int i)
{
	return ((!ft_strncmp(&str[i], REDIR_RIGHT, 1)
			|| !ft_strncmp(&str[i], REDIR_DOUBLE_RIGHT, 2)
			|| !ft_strncmp(&str[i], REDIR_LEFT, 1))
		&& ft_get_state(str, i) == base);
}

char	*ft_tjoin(char *s1, char *s2)
{
	char	*res;
	size_t	totlen;

	if (!s2)
		return (NULL);
	totlen = ft_strlen(s1) + ft_strlen(s2);
	res = ft_calloc(sizeof(char), (totlen + 1));
	if (!res)
		return (NULL);
	ft_strlcat(res, (char *)s1, ft_strlen(s1) + 1);
	ft_strlcat(&res[ft_strlen(s1)], (char *)s2, ft_strlen(s2) + 1);
	return (free(s1), res);
}

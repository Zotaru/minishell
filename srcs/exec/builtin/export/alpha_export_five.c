/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_export_five.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:14:30 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/16 22:27:09 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp_new(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	sort_envp(char **envp)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = size_double_tab(envp);
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp_new(envp[j], envp[j + 1]) > 0)
				swap(&(envp[j]), &(envp[j + 1]));
			j++;
		}
		i++;
	}
	return ;
}

char	*allocate_new_string(char *str, int len)
{
	char	*new;

	new = malloc(sizeof(char) * (len + 3));
	if (new == NULL)
		return (NULL);
	(void)str;
	return (new);
}

void	fill_new_string(char *new, char *str, int equ, int len)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i <= equ)
	{
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '"';
	j++;
	while (i < len)
	{
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = '"';
	j++;
	new[j] = '\0';
}

char	*put_quotes_in_string(char *str, int equ)
{
	char	*new;
	int		len;

	len = ft_strlen(str);
	new = allocate_new_string(str, len);
	if (new == NULL)
		return (NULL);
	fill_new_string(new, str, equ, len);
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonier <amonier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:55:44 by alex              #+#    #+#             */
/*   Updated: 2023/09/06 19:25:07 by amonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_equal_to_null(char **envp)
{
	int	i;
	int	value;

	i = 0;
	while (envp[i])
	{
		value = find_char(envp[i], '=');
		if (value != -1)
			envp[i][value] = '\0';
		i++;
	}
	return ;
}

void	change_null_to_equal(char **envp)
{
	int	i;
	int	value;

	i = 0;
	while (envp[i])
	{
		value = ft_strlen(envp[i]);
		envp[i][value] = '=';
		i++;
	}
	return ;
}

int	find_to_del(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "_", 2) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**del_one(char **envp, int position)
{
	int		i;
	int		j;
	char	**new_envp;
	int		size;

	size = size_double_tab(envp);
	new_envp = malloc(sizeof(char *) * (size - 1 + 1));
	if (new_envp == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (i != position)
		{
			new_envp[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	free_double_tab_char(envp);
	return (new_envp);
}

void	swap(char **first, char **second)
{
	char	*temp;

	temp = *first;
	*first = *second;
	*second = temp;
}

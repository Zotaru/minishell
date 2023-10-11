/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_export_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:19:34 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/16 22:19:41 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_with_two_null(char *src)
{
	char	*str;
	int		l;
	int		i;

	l = ft_strlen(src);
	str = malloc((l + 1 + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	i++;
	str[i] = '\0';
	return (str);
}

char	**dup_env_for_all(t_mini *minsh, char **envp)
{
	char	**final;
	int		size;
	int		i;

	i = 0;
	size = ft_env_size(envp);
	final = malloc(sizeof(char *) * (size + 1));
	if (final == NULL)
	{
		free_t_mini(minsh);
		exit(1);
	}
	while (envp[i])
	{
		if (find_char(envp[i], '=') >= 0)
			final[i] = ft_strdup(envp[i]);
		else
			final[i] = ft_strdup_with_two_null(envp[i]);
		if (final[i] == NULL)
			security_malloc_for_new_env(minsh, final, i);
		i++;
	}
	final[i] = NULL;
	return (final);
}

void	change_equ_to_null_for_exp(char **temp_envp)
{
	int	pos;
	int	i;

	i = 0;
	if (temp_envp == NULL || *temp_envp == NULL)
		return ;
	while (temp_envp[i])
	{
		pos = find_char(temp_envp[i], '=');
		if (pos != -1)
		{
			if (temp_envp[i][pos + 1] == '\0')
			{
				temp_envp[i][pos] = '\0';
			}
		}
		i++;
	}
}

void	print_alpha_env(t_mini *minsh, int position, char **envp)
{
	char	**temp_envp;
	int		value;

	if (envp == NULL || *envp == NULL)
		return ;
	temp_envp = dup_env_for_all(minsh, envp);
	change_equal_to_null(temp_envp);
	value = find_to_del(temp_envp);
	if (value == -1)
	{
		sort_envp(temp_envp);
		change_null_to_equal(temp_envp);
	}
	else
	{
		change_null_to_equal(temp_envp);
		temp_envp = del_one(temp_envp, value);
		change_equal_to_null(temp_envp);
		sort_envp(temp_envp);
		change_null_to_equal(temp_envp);
	}
	change_equ_to_null_for_exp(temp_envp);
	print_and_free(minsh, position, temp_envp);
}

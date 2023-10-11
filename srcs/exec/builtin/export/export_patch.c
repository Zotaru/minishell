/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_patch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 04:18:56 by alex              #+#    #+#             */
/*   Updated: 2023/09/16 22:11:00 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_existence(t_mini *minsh, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while ((minsh->envp)[i])
	{
		if (ft_strncmp((minsh->envp)[i], str, len) == 0
			&& ((minsh->envp)[i][len] == '=' || (minsh->envp)[i][len] == '\0'))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	export_no_equal(t_mini *minsh, int position, int i)
{
	char	**new_env;
	int		s_env;

	s_env = size_double_tab(minsh->envp);
	if (is_valid_variable((minsh->cmds)[position].cmd[i], \
	ft_strlen((minsh->cmds)[position].cmd[i])) == -1)
		return (print_not_valid_identifier(minsh, position, i));
	if (check_existence(minsh, (minsh->cmds)[position].cmd[i]) == 1)
		return (0);
	new_env = create_new_env_no_plus(minsh, s_env, position, i);
	free_double_tab_char(minsh->envp);
	minsh->envp = new_env;
	return (0);
}

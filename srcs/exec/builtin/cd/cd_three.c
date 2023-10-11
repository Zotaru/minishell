/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_three.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:11:43 by jehubert          #+#    #+#             */
/*   Updated: 2023/08/09 18:12:11 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	after_dir_change(t_mini *minsh, int position, char *s_old)
{
	char	*s_new;
	int		checker;

	checker = check_for_create_env(minsh);
	(void)position;
	s_new = malloc((PATH_MAX + 1) * sizeof(char));
	if (s_new == NULL)
	{
		free(s_old);
		free_t_mini(minsh);
		exit(1);
	}
	getcwd(s_new, PATH_MAX);
	s_new[PATH_MAX] = '\0';
	if (checker == 2)
		update_pwd_both(minsh, s_new, s_old);
	else
		update_or_create_env(minsh, s_new, s_old);
	free(s_old);
	free(s_new);
	return (0);
}

int	b_cd(t_mini *minsh, int position)
{
	char	*s_old;
	int		size;
	int		err;

	size = size_double_tab((minsh->cmds)[position].cmd);
	if (size > 2)
	{
		ft_putstr_fd("cd : too many argument\n", 2);
		return (1);
	}
	s_old = malloc((PATH_MAX + 1) * sizeof(char));
	if (s_old == NULL)
	{
		free_t_mini(minsh);
		exit(1);
	}
	getcwd(s_old, PATH_MAX);
	s_old[PATH_MAX] = '\0';
	err = change_dir(minsh, position, size);
	if (err == 0)
		err = after_dir_change(minsh, position, s_old);
	else
		free(s_old);
	return (err);
}

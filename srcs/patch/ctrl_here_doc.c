/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:42:35 by amonier           #+#    #+#             */
/*   Updated: 2023/09/16 21:26:10 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*stat_pointer(t_mini *minsh)
{
	static t_mini	*mini = NULL;

	if (minsh != NULL)
		mini = minsh;
	return (mini);
}

char	*stat_pointer_char(char *str)
{
	static char	*act;

	act = NULL;
	if (str != NULL)
		act = str;
	return (act);
}

void	ctrl_c_here_doc(int signal)
{
	extern int	g_status;
	t_mini		*minsh;
	char		*str;

	(void)signal;
	minsh = stat_pointer(NULL);
	close(minsh->act_fd);
	minsh->act_fd = -1;
	free_t_mini(minsh);
	str = stat_pointer_char(NULL);
	free(str);
	g_status = 130;
	exit(130);
}

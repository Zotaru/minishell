/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:22:40 by jehubert          #+#    #+#             */
/*   Updated: 2023/09/04 16:44:21 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_change_status(int status)
{
	extern int	g_status;

	g_status = status;
}

int	ft_check_prompt(char *line)
{
	char		tmp;

	tmp = ft_check_dt(line);
	if (tmp)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(tmp, 2);
		ft_putstr_fd("'\n", 2);
		return (ft_change_status(1), 0);
	}
	if (!ft_check_pipes(line))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (ft_change_status(1), 0);
	}
	if (!ft_check_quote_syntax(line))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `\"'\n", 2);
		return (ft_change_status(1), 0);
	}
	return (1);
}

int	ft_triple(char *line)
{
	char	tmp;

	tmp = ft_check_triple_redir(line);
	if (tmp)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(tmp, 2);
		ft_putchar_fd(tmp, 2);
		ft_putstr_fd("'\n", 2);
		return (ft_change_status(1), 0);
	}
	return (1);
}

int	ft_redir_error(t_mini *mini, char *tkn, int j)
{
	ft_putstr_fd("minishell: syntax error ", 2);
	ft_putstr_fd("near unexpected token `", 2);
	ft_putstr_fd(tkn, 2);
	ft_putstr_fd("'\n", 2);
	ft_free_cmds(j, mini);
	return (ft_change_status(1), 0);
}

int	ft_check_redir(t_mini *mini, int j)
{
	int	i;
	int	res;

	i = -1;
	while (++i < j)
	{
		res = ft_wf(mini->cmds[i].input_file, \
		mini->cmds[i].output_file, mini->cmds[i].redir_type);
		if (res == 1)
			return (ft_redir_error(mini, "<", j));
		else if (res == 2)
			return (ft_redir_error(mini, "<<", j));
		else if (res == 3)
			return (ft_redir_error(mini, ">", j));
		else if (res == 4)
			return (ft_redir_error(mini, ">>", j));
	}
	return (1);
}

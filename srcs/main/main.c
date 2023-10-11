/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 04:52:33 by alex              #+#    #+#             */
/*   Updated: 2023/09/16 22:32:20 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	ft_end_loop(t_mini *mini, char *line)
{
	int			pid;
	extern int	g_status;

	free(line);
	line = NULL;
	pid = fork();
	signal(SIGINT, ctrlc);
	if (pid == 0)
	{
		signal(SIGINT, ctrl_c_here_doc);
		create_temp_files(mini);
		free_t_mini(mini);
		exit(0);
	}
	else
		wait(&pid);
	if (g_status != 130)
		create_file_for_dad(mini);
	if (fork_or_not(mini) == 1 && g_status != 130)
		no_fork(mini);
	else if (g_status != 130)
		exec(mini);
	send_act_cmd_for_unlink(mini);
	ft_free_cmds(mini->nb_cmd, mini);
}

void	set_signals(void)
{
	signal(SIGINT, handle_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

void	process_line(t_mini *mini, char *line)
{
	if (line != NULL)
	{
		if (ft_line_empty(line, 0))
			return ;
		add_history(line);
		mini->nb_cmd = ft_line(line, mini);
		if (mini->nb_cmd == -1)
		{
			free(line);
			return ;
		}
		g_status = 0;
		ft_end_loop(mini, line);
	}
}

void	clean_up(t_mini *mini)
{
	ft_clean_split(mini->envp);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_mini		mini;
	char		*line;
	extern int	g_status;

	ft_start_main(argc, argv, envp, &mini);
	while (1)
	{
		set_signals();
		line = readline("minishell$> ");
		if (ft_line_empty(line, 1))
			break ;
		process_line(&mini, line);
	}
	clean_up(&mini);
	return (0);
}

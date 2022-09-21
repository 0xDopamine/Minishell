/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 05:36:51 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"
#include <readline/readline.h>

t_global	g = {0};

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g.exit_status = 130;
		return ;
	}
	if (sig == SIGQUIT)
		exit(255);
	return ;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_cmd	*simple_command;
	t_env	*env_list;
	char	*temp;

	(void)argc;
	(void)argv;
	line = NULL;
	g.here_sig = 0;
	simple_command = malloc(sizeof(t_cmd));
	ft_get_env(env, &env_list);
	printf("Two brothers minishell\n");
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (true)
	{
		line = readline(CYAN"TwoBrosShell➤ "RESET);
		temp = line;
		if (!temp)
		{
			free(temp);
			ft_putstr_fd("\nexit\n", NULL, STDOUT_FILENO);
			exit(255);
		}
		add_history(temp);
		temp = spaces(temp);
		simple_command = parsepipe(&temp, env_list);
		ft_check_cmd(simple_command, &env_list);
		free(simple_command);
		// system("leaks minishell");
	}
	free(temp);
	freethis(&line);
	free(simple_command);
	return (0);
}

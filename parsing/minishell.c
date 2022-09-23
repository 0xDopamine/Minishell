/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:15:40 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"
#include <readline/readline.h>
#include <readline/history.h>

t_global	g_var = {0};

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_cmd	*simple_command;
	t_env	*env_list;
	char	*temp;

	(void)argc;
	(void)argv;
	line = NULL;
	g_var.here_sig = 0;
	env_list = NULL;
	// simple_command = malloc(sizeof(t_cmd));
	ft_get_env(env, &env_list);
	printf("Two brothers minishell\n");
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (TRUE)
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
		for (int i = 0; i < 3; i++)
			system("leaks minishell");
	}
	free(temp);
	freethis(&line);
	free(simple_command);
	return (0);
}

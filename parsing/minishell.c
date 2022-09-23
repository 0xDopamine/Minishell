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
	ft_get_env(env, &env_list);
	printf("Two brothers minishell\n");
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (TRUE)
	{
		line = readline(CYAN"TwoBrosShell➤ "RESET);
		if (!line)
		{
			free(line);
			ft_putstr_fd("\nexit\n", NULL, STDOUT_FILENO);
			exit(255);
		}
		temp = ft_strdup(line);
		add_history(temp);
		free(line);
		line = spaces(temp);
		simple_command = parsepipe(&line, env_list);
		ft_check_cmd(simple_command, &env_list);
		free(simple_command);
		free(temp);
		system("leaks minishell");
	}
	free(simple_command);
	return (0);
}

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

void free_cmd(t_cmd *cmd) ;

void	ft_wait_pids(t_cmd *cmd)
{
	if (cmd->type == PIPE)
	{
		ft_wait_pids(((t_pipe *)cmd)->left);
		ft_wait_pids(((t_pipe *)cmd)->right);
	}
	else if (cmd->type == EXEC)
	{
		waitpid(((t_exec *)cmd)->pid, &g_var.exit_status, 0);
		g_var.exit_status = WEXITSTATUS(g_var.exit_status); // TODO CHECK IF THE MACRO IS CORRECT
	}
	else if (cmd->type == REDIR)
		ft_wait_pids(((t_redir *)cmd)->cmd);
}


int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_cmd	*simple_command;
	t_env	*env_list;
	char	*temp;
	t_parse	*parse;

	(void)argc;
	(void)argv;
	line = NULL;
	parse = malloc(sizeof(t_parse));
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
		add_history(line);
		temp = ft_strdup(line);
		free(line);
		line = spaces(temp);
		simple_command = parsepipe(&line, parse, env_list);
		ft_check_cmd(simple_command, &env_list);
		ft_wait_pids(simple_command);
		freethis(parse->split);
		free(parse->state);
		free(parse);
		free_cmd(simple_command);
		free(temp);
	}
	free(simple_command);
	return (0);
}

void	free_red(t_redir *red)
{
	while (red)
	{
		free(red->file);
		red = red->next;
	}
}

void free_cmd(t_cmd *cmd) {
	t_redir *const	_red = (t_redir *)cmd;
	t_exec *const	_exec = (t_exec *)cmd;
	t_pipe *const	_pipe = (t_pipe *)cmd;

	if (cmd == NULL)
		return ;
	if (cmd->type == EXEC)
		freethis(_exec->argv);
	else if (cmd->type == REDIR)
	{
		free_cmd(_red->cmd);
		free_red(_red);
	}
	else if (cmd->type == PIPE)
	{
		free_cmd(_pipe->left);
		free_cmd(_pipe->right);
	}
	free(cmd);
}
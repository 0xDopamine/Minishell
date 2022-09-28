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

void	free_red(t_redir *red)
{
	void	*tmp;

	free(red->file);
	red = red->next;
	while (red)
	{
		free(red->file);
		tmp = red;
		red = red->next;
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
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

void	ft_wait_pids(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == PIPE)
	{
		ft_wait_pids(((t_pipe *)cmd)->left);
		ft_wait_pids(((t_pipe *)cmd)->right);
	}
	else if (cmd->type == EXEC)
	{
		waitpid(((t_exec *)cmd)->pid, &g_var.exit_status, 0);
		g_var.exit_status = WEXITSTATUS(g_var.exit_status);
	}
	else if (cmd->type == REDIR)
		ft_wait_pids(((t_redir *)cmd)->cmd);
}

void	minishell(char *line, char *temp, t_env *env_list)
{
	t_cmd	*simple_command;

	line = readline(CYAN"TwoBrosShell➤ "RESET);
	ft_line_protection(line);
	temp = line;
	add_history(temp);
	line = spaces(temp);
	char *tttmp = line;
	if (line)
	{
		simple_command = parsepipe(&line, env_list);
		ft_check_cmd(simple_command, &env_list);
		ft_wait_pids(simple_command);
		free_cmd(simple_command);
		system("leaks minishell");
		free(tttmp);
		free(temp);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_env	*env_list;
	char	*temp;

	(void)argc;
	(void)argv;
	line = NULL;
	temp = NULL;
	g_var.here_sig = 0;
	env_list = NULL;
	ft_get_env(env, &env_list);
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (TRUE)
		minishell(line, temp, env_list);
	return (0);
}

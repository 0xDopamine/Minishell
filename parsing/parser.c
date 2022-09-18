/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:51:27 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/18 01:39:40 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <unistd.h>

t_cmd	*parseexec(char **ps, t_env *env_list)
{
	t_exec	*cmd;
	t_cmd	*ret;
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (ft_strchr(**ps, "\'\""))
		parse->words = num_words(*ps, 0);
	else
		parse->words = num_words(*ps, 1);
	ret = execcmd(parse->words);
	cmd = (t_exec *)ret;
	parse->argc = 0;
	ret = parseredir_test(ret, ps, env_list);
	while (!next(ps, "|"))
	{
		parse->tok = get_token(ps, &parse->q);
		if (parse->tok == 0)
			break ;
		parse->state = check_var(parse->q);
		if (ft_strchr(*parse->q, "\'\"") || check_state(parse->state))
			parse->split = ft_split_q(parse->q, ' ');
		else
			parse->split = ft_split(parse->q, ' ');
		if (parse->tok != 'c')
			printf("syntax error %c\n", parse->tok); 
		cmd->argv[parse->argc] = ft_ultimate_string_handler(&parse->split[0], env_list, parse->state);
		printf("cmd: %s\n", cmd->argv[parse->argc]);
		parse->argc++;
		if (parse->argc >= parse->words || parse->split[1] == NULL)
			break ;
		ret = parseredir_test(ret, ps, env_list);
		if (ret == NULL)
			return (NULL);
	}
	cmd->argv[parse->argc] = NULL;
	return (ret);
}

t_cmd	*parseredir_test(t_cmd *cmd, char **ps, t_env *env_list)
{
	t_parse	*parse;
	t_env	**list;
	t_redir	*head;

	parse = malloc(sizeof(t_parse));
	list = malloc(sizeof(t_env **));
	*list = env_list;
	parse->split = NULL;
	if (cmd->type == EXEC)
		head = NULL;
	if (cmd->type == REDIR)
		head = (t_redir *)cmd;
	while (next(ps, "<>"))
	{
		parse->tok = get_token(ps, 0);
		if (get_token(ps, &parse->q) != 'c')
		{
			ft_putstr_fd("syntax error\n", NULL, STDERR_FILENO);
			cmd = NULL;
			return (cmd);
		}
		if (*parse->q)
			parse->split = ft_split(parse->q, ' ');
		if (parse->tok == '<')
			ft_lstadd_redir(&head, redircmd_test(cmd, parse->split[0], O_RDONLY, STDIN_FILENO));
		else if (parse->tok == '>')
			ft_lstadd_redir(&head, redircmd_test(cmd, parse->split[0], O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO));
		else if (parse->tok == 'A')
			ft_lstadd_redir(&head, redircmd_test(cmd, parse->split[0], O_WRONLY | O_CREAT | O_APPEND, 1));
		else if (parse->tok == 'H')
			ft_lstadd_redir(&head, redircmd_test(cmd, parse->split[0], HEREDOC, 0));
		cmd = (t_cmd *)head;
	}
	return (cmd);
}

int		ft_is_heredoc(char **ps)
{
	char	*q;
	int		i;

	i = -1;
	q = *ps;
	while (q[++i])
		if (q[i] == '<' && q[i + 1] == '<')
			return (1);
	return (0);
}

t_cmd	*parsepipe(char **ps, t_env *env_list)
{
	t_cmd	*cmd;
	
	cmd = parseexec(ps, env_list);
	if (cmd == NULL)
		return (NULL);
	if (next(ps, "|"))
	{
		get_token(ps, 0);
		cmd = pipecmd(cmd, parsepipe(ps, env_list));
	}
	return (cmd);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:51:27 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/23 19:13:52 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <unistd.h>

t_cmd	*parseexec(char **ps, t_env *env_list, t_parse *parse)
{
	t_exec	*cmd;
	t_cmd	*ret; 

	parse->words = ft_init_words(ps);
	ret = execcmd(parse->words);
	cmd = (t_exec *)ret;
	parse->argc = 0;
	ret = parseredir(ret, ps, parse);
	while (!next(ps, "|"))
	{
		parse->tok = get_token(ps, &parse->q);
		if (parse->tok == 0)
			break ;
		ft_append_command(cmd, parse, env_list);
		parse->argc++;
		if (parse->argc >= parse->words || parse->split[1] == NULL)
			break ;
		freethis(parse->split);
		ret = parseredir(ret, ps, parse);
		if (ret == NULL)
			return (NULL);
	}
	cmd->argv[parse->argc] = NULL;
	// free(parse->split);
	// freethis(parse->split);
	// free(parse->state);
	return (ret);
}

t_cmd	*parseredir(t_cmd *cmd, char **ps, t_parse *parse)
{
	t_redir	*head;

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
		ft_append_redir_list(&head, parse, cmd);
		cmd = (t_cmd *)head;
	}
	return (cmd);
}

t_cmd	*parsepipe(char **ps, t_env *env_list)
{
	t_cmd	*cmd;
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	cmd = parseexec(ps, env_list, parse);
	if (cmd == NULL)
	{
		freethis(parse->split);
		free(parse->state);
		free(parse);
		return (NULL);
	}
	if (next(ps, "|"))
	{
		get_token(ps, 0);
		cmd = pipecmd(cmd, parsepipe(ps, env_list));
	}
	freethis(parse->split);
	free(parse->state);
	free(parse);
	return (cmd);
}

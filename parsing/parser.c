/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:51:27 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/25 17:52:38 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <unistd.h>

static	t_cmd	*parse_norme(t_cmd *cmd)
{
	ft_putstr_fd("syntax error\n", NULL, STDERR_FILENO);
	g_var.exit_status = 2;
	cmd->status = ERROR;
	return (cmd);
}

void	ft_init_parse(char	**ps, t_parse *parse, t_env *env_list)
{
	parse->words = ft_init_words(ps, env_list);
	parse->state = NULL;
	parse->split = NULL;
	parse->argc = 0;
}

t_cmd	*parseexec(char **ps, t_env *env_list, t_parse *parse)
{
	t_exec	*cmd;
	t_cmd	*ret;

	ft_init_parse(ps, parse, env_list);
	if (parse->words == 0)
		return (NULL);
	ret = execcmd(parse->words);
	cmd = (t_exec *)ret;
	ret = parseredir(ret, ps, parse, env_list);
	ft_free_and_null(parse, 1);
	while (*ps && !next(ps, "|") && ret->status != ERROR)
	{
		parse->tok = get_token(ps, &parse->q);
		if (parse->tok == 0)
			break ;
		ft_append_command(cmd, parse, env_list, ret);
		if (ret->status != ERROR)
			if (++parse->argc >= parse->words || parse->split[1] == NULL)
				break ;
		ret = parseredir(ret, ps, parse, env_list);
		ft_free_and_null(parse, 0);
	}
	if (cmd->argv[parse->argc])
		cmd->argv[parse->argc] = NULL;
	return (ret);
}

t_cmd	*parseredir(t_cmd *cmd, char **ps, t_parse *parse, t_env *env_list)
{
	t_redir	*head;

	if (parse->split)
		freethis(parse->split);
	parse->split = NULL;
	if (cmd->type == EXEC)
		head = NULL;
	if (cmd->type == REDIR)
		head = (t_redir *)cmd;
	while (*ps && next(ps, "<>"))
	{
		parse->tok = get_token(ps, 0);
		if (!*ps)
			break ;
		if (*ps && get_token(ps, &parse->q) != 'c')
			return (parse_norme(cmd));
		if (*parse->q)
			ft_filename(parse, env_list);
		ft_append_redir_list(&head, parse, cmd);
		freethis(parse->split);
		parse->split = NULL;
		cmd = (t_cmd *)head;
	}
	return (cmd);
}

t_cmd	*parsepipe(char **ps, t_env *env_list)
{
	t_cmd	*cmd;
	t_parse	*parse;

	parse = ft_calloc(sizeof(t_parse), 1);
	cmd = parseexec(ps, env_list, parse);
	if (cmd == NULL)
	{
		freethis(parse->split);
		free(parse->state);
		free(parse);
		return (NULL);
	}
	if (*ps && next(ps, "|"))
	{
		get_token(ps, 0);
		cmd = pipecmd(cmd, parsepipe(ps, env_list));
	}
	freethis(parse->split);
	free(parse->state);
	free(parse);
	return (cmd);
}

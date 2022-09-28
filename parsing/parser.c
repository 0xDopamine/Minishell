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

t_cmd	*parseexec(char **ps, t_env *env_list, t_parse *parse)
{
	t_exec	*cmd;
	t_cmd	*ret;

	parse->words = ft_init_words(ps);
	if (parse->words == 0)
	{
		ft_putstr_fd("Quotes error\n", NULL, STDERR_FILENO);
		return (NULL);
	}
	parse->state = NULL;
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
		free(parse->state);
		parse->state = NULL;
	}
	cmd->argv[parse->argc] = NULL;
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
		{
			freethis(parse->split);
			parse->split = ft_split(parse->q, ' ');
		}
		ft_append_redir_list(&head, parse, cmd);
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
// void	parseexec_loop(char	**ps, t_parse *parse, t_env *env_list, t_exec *cmd)
// {
// 	parse->tok = get_token(ps, &parse->q);
// 	if (parse->tok == 0)
// 		return ;
// 	ft_append_command(cmd, parse, env_list);
// }

// t_cmd	*parseexec(char **ps, t_env *env_list, t_parse *parse)
// {
// 	t_exec	*cmd;
// 	t_cmd	*ret;

// 	parse->words = ft_init_words(ps);
// 	parse->state = NULL;
// 	ret = execcmd(parse->words);
// 	cmd = (t_exec *)ret;
// 	parse->argc = 0;
// 	ret = parseredir(ret, ps, parse);
// 	if (!ret)
// 		return (NULL);
// 	while (!next(ps, "|"))
// 	{
// 		parseexec_loop(ps, parse, env_list, cmd);
// 		parse->argc++;
// 		if (parse->argc >= parse->words || parse->split[1] == NULL)
// 			break ;
// 		freethis(parse->split);
// 		ret = parseredir(ret, ps, parse);
// 		if (ret == NULL)
// 			return (NULL);
// 		free(parse->state);
// 		parse->state = NULL;
// 	}
// 	cmd->argv[parse->argc] = NULL;
// 	return (ret);
// }

// t_cmd	*parseredir(t_cmd *cmd, char **ps, t_parse *parse)
// {
// 	t_redir	*head;

// 	parse->split = NULL;
// 	if (cmd->type == EXEC)
// 		head = NULL;
// 	if (cmd->type == REDIR)
// 		head = (t_redir *)cmd;
// 	while (next(ps, "<>"))
// 	{
// 		parse->tok = get_token(ps, 0);
// 		if (get_token(ps, &parse->q) != 'c')
// 		{
// 			ft_putstr_fd("syntax error\n", NULL, STDERR_FILENO);
// 			return (cmd);
// 		}
// 		if (*parse->q)
// 		{
// 			freethis(parse->split);
// 			parse->split = ft_split(parse->q, ' ');
// 		}
// 		ft_append_redir_list(&head, parse, cmd);
// 		cmd = (t_cmd *)head;
// 	}
// 	return (cmd);
// }

// t_cmd	*parsepipe(char **ps, t_env *env_list)
// {
// 	t_cmd	*cmd;
// 	t_parse	*parse;

// 	parse = ft_calloc(sizeof(t_parse), 1);
// 	cmd = parseexec(ps, env_list, parse);
// 	if (cmd == NULL)
// 	{
// 		freethis(parse->split);
// 		free(parse->state);
// 		free(parse);
// 		return (NULL);
// 	}
// 	if (next(ps, "|"))
// 	{
// 		get_token(ps, 0);
// 		cmd = pipecmd(cmd, parsepipe(ps, env_list));
// 	}
// 	freethis(parse->split);
// 	free(parse->state);
// 	free(parse);
// 	return (cmd);
// }

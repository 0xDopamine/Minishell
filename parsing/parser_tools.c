/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 23:59:08 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/25 20:30:38 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

int	ft_init_words(char	**ps)
{
	if (ft_strchr(**ps, "\'\""))
		return (num_words(*ps, 0));
	else
		return (num_words(*ps, 1));
}

char	**ft_split_argv(t_parse *parse)
{
	if (ft_strchr(*parse->q, "\'\"") || check_state(parse->state))
		return (ft_split_q(parse->q, ' '));
	else
		return (ft_split(parse->q, ' '));
}

void	fetch_delimiter(char **q, char **eq)
{
	char	*s;

	s = *q;
	*q = s;
	while (!ft_strchr(*s, "\'\"") && *s)
		s++;
	*eq = s--;
}

char	*ft_delimiter_handler(char **del)
{
	char	*s;
	char	*es;
	char	*res;

	s = *del;
	es = NULL;
	if (ft_strchr(*s, "\'\""))
	{
		fetch_quoted(&s, &es);
		res = ft_join_string(s, es);
	}
	else
	{
		fetch_delimiter(&s, &es);
		res = ft_join_string(s, es);
	}
	return (res);
}

void	ft_filename(t_parse *parse, t_env *env_list)
{
	char	*tmp;

	freethis(parse->split);
	parse->split = ft_split(parse->q, ' ');
	tmp = parse->split[0];
	if (parse->tok != 'H')
		parse->split[0] = ft_ultimate_string_handler(&tmp, env_list);
	else
		parse->split[0] = ft_delimiter_handler(&tmp);
	free(tmp);
}

void	ft_append_command(t_exec *cmd, t_parse *parse, t_env *env_list, t_cmd *ret)
{
	parse->state = check_var(parse->q);
	parse->split = ft_split_argv(parse);
	if (!parse->split)
	{
		ret->status = ERROR;
		cmd->argv[parse->argc] = NULL;
		return ;
	}
	if (parse->tok != 'c')
	{
		ret->status = ERROR;
		printf("syntax error %c\n", parse->tok);
	}
	cmd->argv[parse->argc] = ft_ultimate_string_handler(&parse->split[0],
			env_list);
	if (parse->split[1] && cmd->argv[parse->argc] == NULL)
		cmd->argv[parse->argc] = ft_strdup(" ");
	
}

void	ft_append_redir_list(t_redir **head, t_parse *parse, t_cmd *cmd)
{
	char	*delimiter;

	delimiter = NULL;
	if (parse->tok == '<')
		ft_lstadd_redir(head, redircmd(cmd, parse->split[0],
				O_RDONLY, STDIN_FILENO));
	else if (parse->tok == '>')
		ft_lstadd_redir(head, redircmd(cmd, parse->split[0],
				O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO));
	else if (parse->tok == 'A')
	{
		ft_lstadd_redir(head, redircmd(cmd, parse->split[0],
				O_WRONLY | O_CREAT | O_APPEND, 1));
	}
	else if (parse->tok == 'H')
	{
		if (!parse->split[0])
			delimiter = ft_strdup("\0");
		else
			delimiter = ft_strdup(parse->split[0]);
		ft_lstadd_redir(head,
			redircmd(cmd, delimiter, HEREDOC, 0));
	}
	free(delimiter);
}

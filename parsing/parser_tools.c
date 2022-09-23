/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 23:59:08 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/23 07:29:02 by mbaioumy         ###   ########.fr       */
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

void	ft_append_command(t_exec *cmd, t_parse *parse, t_env *env_list)
{
	parse->state = check_var(parse->q);
	parse->split = ft_split_argv(parse);
	if (parse->tok != 'c')
		printf("syntax error %c\n", parse->tok);
	cmd->argv[parse->argc] = ft_ultimate_string_handler(&parse->split[0],
			env_list);
}

void	ft_append_redir_list(t_redir **head, t_parse *parse, t_cmd *cmd)
{
	if (parse->tok == '<')
		ft_lstadd_redir(head, redircmd(cmd, parse->split[0],
				O_RDONLY, STDIN_FILENO));
	else if (parse->tok == '>')
		ft_lstadd_redir(head, redircmd(cmd, parse->split[0],
				O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO));
	else if (parse->tok == 'A')
		ft_lstadd_redir(head, redircmd(cmd, parse->split[0],
				O_WRONLY | O_CREAT | O_APPEND, 1));
	else if (parse->tok == 'H')
		ft_lstadd_redir(head,
			redircmd(cmd, parse->split[0], HEREDOC, 0));
}

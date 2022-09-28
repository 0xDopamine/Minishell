/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 09:44:17 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/28 04:49:29 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

char	*ft_env_case(char **q, char **eq, char *res, t_env *env_list)
{
	char	*temp;

	ft_check_envs(q);
	if (**q == '$')
	{	
		fetch_env(q, eq);
		temp = *q;
		*q = ft_join_string(*q, *eq);
		if (**q == '$' && **(q + 1) == '\0')
			res = strjoin_and_free1(res, "$");
		else if (**q == '$' && **(q + 1) == '?')
			res = strjoin_and_free(res, ft_assign_env(*q, env_list));
		else
			res = strjoin_and_free(res, ft_assign_env(*q, env_list));
		free(*q);
		*q = *eq;
	}
	return (res);
}

char	*ft_quote_case(char **q, char **eq, char *res, t_env *env_list)
{
	fetch_quoted(q, eq);
	if (**q == '$' && **eq != '\'')
		res = ft_env_case(q, eq, res, env_list);
	else if (*(*q) == '\'' && *(*q + 1) == '$' && **eq == '"')
		res = strjoin_and_free(res, ft_search_for_env(*q, env_list));
	else
		res = strjoin_and_free(res, ft_join_string(*q, *eq));
	if (**eq + 1)
		*q = *eq + 1;
	return (res);
}

char	*ft_normal_case(char **q, char **eq, char *res)
{
	fetch_string(q, eq);
	res = strjoin_and_free(res, ft_join_string(*q, *eq));
	if (**eq == '\0')
	{
		*q = NULL;
		return (res);
	}
	else
		*q = *eq;
	return (res);
}

char	*ft_ultimate_string_handler(char **ps, t_env *env_list)
{
	char	*q;
	char	*eq;
	char	*res;

	eq = NULL;
	res = NULL;
	q = *ps;
	while (q)
	{
		if (ft_strchr(*q, "\'\""))
			res = ft_quote_case(&q, &eq, res, env_list);
		else if (ft_strchr(*q, "$"))
			res = ft_env_case(&q, &eq, res, env_list);
		else
			res = ft_normal_case(&q, &eq, res);
	}
	return (res);
}

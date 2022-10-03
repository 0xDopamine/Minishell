/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 09:44:17 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/28 22:52:38 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

char	*strjoin_and_free2(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (s2)
		free(s2);
	return (res);
}

char	*ft_env_case(char **q, char **eq, char *res, t_env *env_list)
{
	ft_check_envs(q);
	if (**q == '$')
	{	
		fetch_env(q, eq);
		*q = ft_join_string(*q, *eq);
		if (**q == '$' && *(*q + 1) == '\0')
			res = strjoin_and_free1(res, "$");
		else if (**q == '$' && *(*q + 1) == '?')
			res = strjoin_and_free(res, ft_assign_env(*q, env_list));
		else
			res = strjoin_and_free(res, ft_assign_env(*q, env_list));
		free(*q);
		*q = *eq;
	}
	return (res);
}

char	*ft_normal_case(char **q, char **eq, char *res)
{
	fetch_string(q, eq);
	res = strjoin_and_free2(res, ft_join_string(*q, *eq));
	if (**eq == '\0')
	{
		*q = NULL;
		return (res);
	}
	else if (ft_strchr(**eq, "\'\"") && *(*eq + 1) == '\0')
		*q = *eq + 1;
	else
		*q = *eq;
	return (res);
}

// char	*ft_quote_case(char **q, char **eq, char *res, t_env *env_list)
// {
// 	int	quote;

// 	quote = **q;
// 	if (**q)
// 	{
// 		fetch_quoted(q, eq);
// 		if (*q == NULL)
// 		{
// 			free(res);
// 			return (NULL);
// 		}
// 		if (**q == '$' && *(*q + 1) != ' ' && **eq != '\'')
// 			res = ft_env_case(q, eq, res, env_list);
// 		else if (*(*q) == '\'' && *(*q + 1) == '$' && **eq == '"')
// 			res = strjoin_and_free(res, ft_search_for_env(*q, env_list));
// 		else if (**q == '\'' && **eq == '\"')
// 			res = strjoin_and_free(res, ft_join_string(*q, *eq));
// 		else
// 			res = strjoin_and_free(res, ft_normal_case(q, eq, res));
// 		if (**eq == quote)
// 		 	*eq += 1;
// 		*q = *eq;
// 	}
// 	return (res);
// }

char	*ft_quote_case(char **q, char **eq, char *res, t_env *env_list)
{
	const char	quote = **q;
	char		*tmp;

	fetch_quoted(q, eq);
	if (q == NULL)
		return (res);
	while (*q != *eq)
	{
		if (quote == '"' && **q == '$')
			res = ft_env_case(q, &tmp, res, env_list);
		else
		{
			res = strjoin_and_free1(res, (char [2]){**q, '\0'});
			(*q)++;
		}
	}
	(*q)++;
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

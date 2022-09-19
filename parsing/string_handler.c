/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 09:44:17 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/19 10:44:09 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

// char	*ft_quotes_case(char **ps, char **es, char *res, t_env *env_list)
// {
// 	char	*q;
// 	char	*eq;

// 	q = *ps;
// 	eq = *es;
// 	fetch_quoted(&q, &eq);
// 	if (*q == 1)
// 		return (NULL);
// 	if (*q == '$' && *eq != '\'')
// 	{					
// 		fetch_env(&q, &eq);
// 		if (*q == 1)
// 			return (NULL);
// 		q = ft_join_string(q, eq);
// 		res = ft_strjoin(res, ft_assign_env(q, env_list));
// 	}
// 	else if (*q == '\'' && (*(q + 1) == '$') && *eq == '"')
// 		res = ft_strjoin(res, ft_search_for_env(q, env_list));
// 	else
// 		res = ft_strjoin(res, ft_join_string(q, eq));
// 	if (*eq + 1)
// 		*ps = eq + 1;
// 	return (res);
// }

// char	*ft_env_case(char **ps, char **es, char *res, t_env *env_list)
// {
// 	char	*q;
// 	char	*eq;

// 	q = *ps;
// 	eq = *es;
// 	ft_check_envs(&q);
// 	if (*q == '$')
// 	{	
// 		fetch_env(&q, &eq);
// 		q = ft_join_string(q, eq);
// 		if (*q == '$' && *(q + 1) == '\0')
// 			res = ft_strjoin(res, "$");
// 		else
// 			res = ft_strjoin(res, ft_assign_env(q, env_list));
// 		*ps = eq;
// 	}
// 	return (res);
// }

// char	*ft_string_case(char **ps, char **es, char *res)
// {
// 	char	*q;
// 	char	*eq;

// 	q = *ps;
// 	eq = *es;
// 	fetch_string(&q, &eq);
// 	res = ft_strjoin(res, ft_join_string(q, eq));
// 	*ps = eq;
// 	return (res);
// }

// char	*ft_ultimate_string_handler(char **ps, t_env *env_list)
// {
// 	char	*q;
// 	char	*eq;
// 	char	*res;

// 	eq = NULL;
// 	res = NULL;
// 	if (ps)
// 	{
// 		q = *ps;
// 		while (q)
// 		{
// 			if (ft_strchr(*q, "\'\""))
// 				res = ft_quotes_case(&q, &eq, res, env_list);
// 			else if (ft_strchr(*q, "$"))
// 				res = ft_env_case(&q, &eq, res, env_list);
// 			else
// 				res = ft_string_case(&q, &eq, res);
// 			if (*q == '\0')
// 				break ;
// 		}
// 	}
// 	if (res)
// 		*ps = res;
// 	return (*ps);
// }

char	*ft_ultimate_string_handler(char **ps, t_env *env_list)
{
	char	*q;
	char	*eq;
	char	*res;

	eq = NULL;
	res = NULL;
	if (ps)
	{
		q = *ps;
		while (q)
		{
			if (ft_strchr(*q, "\'\""))
			{
				fetch_quoted(&q, &eq);
				if (*q == 1)
					return (NULL);
				if (*q == '$' && *eq != '\'')
				{					
					fetch_env(&q, &eq);
					if (*q == 1)
						return (NULL);
					q = ft_join_string(q, eq);
					res = ft_strjoin(res, ft_assign_env(q, env_list));
				}
				else if (*q == '\'' && (*(q + 1) == '$') && *eq == '"')
					res = ft_strjoin(res, ft_search_for_env(q, env_list));
				else
					res = ft_strjoin(res, ft_join_string(q, eq));
				if (*eq + 1)
					q = eq + 1;
			}
			else if (ft_strchr(*q, "$"))
			{
				ft_check_envs(&q);
				if (*q == '$')
				{	
					fetch_env(&q, &eq);
					q = ft_join_string(q, eq);
					if (*q == '$' && *(q + 1) == '\0')
						res = ft_strjoin(res, "$");
					else
						res = ft_strjoin(res, ft_assign_env(q, env_list));
					q = eq;
				}			
			}
			else
			{
				fetch_string(&q, &eq);
				res = ft_strjoin(res, ft_join_string(q, eq));
				if (*eq == '\0')
					break ;
				else
					q = eq;
			}
		}
	}
	if (res)
		*ps = res;
	return (*ps);
}
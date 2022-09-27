/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 09:44:17 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/27 03:09:46 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

char	*strjoin_and_free1(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (res);
}

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (s2)
		free(s2);
	if (s1)
		free(s1);
	return (res);
}

char	*ft_ultimate_string_handler(char **ps, t_env *env_list)
{
	char	*q;
	char	*eq;
	char	*res;
	// char	*tmp;

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
				if (q == NULL)
					return (NULL);
				if (*q == '$' && *eq != '\'')
				{					
					fetch_env(&q, &eq);
					if (*q == 1)
						return (NULL);
					q = ft_join_string(q, eq);
					res = strjoin_and_free(res, ft_assign_env(q, env_list));
				}
				else if (*q == '\'' && (*(q + 1) == '$') && *eq == '"')
					res = strjoin_and_free(res, ft_search_for_env(q, env_list));
				else
					res = strjoin_and_free(res, ft_join_string(q, eq));
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
						res = strjoin_and_free1(res, "$");
					else if (*q == '$' && *(q + 1) == '?')
						res = strjoin_and_free(res, ft_assign_env(q, env_list));
					else
						res = strjoin_and_free(res, ft_assign_env(q, env_list));
					void	*tmp = q;
					q = eq;
					free(tmp);
				}			
			}
			else
			{
				fetch_string(&q, &eq);
				res = strjoin_and_free(res, ft_join_string(q, eq));
				if (*eq == '\0')
					break ;
				else
				{
					// free(q);
					q = eq;
				}
			}
		}
	}
	return (res);
}

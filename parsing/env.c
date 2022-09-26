/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 01:10:55 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/26 02:15:01 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

char	*ft_search_for_env(char *s, t_env *env_list)
{
	char	*res;
	char	*q;
	char	*eq;
	char	*temp;

	q = s;
	res = ft_strdup("");
	while (q)
	{
		if (*q == '\'')
		{
			fetch_quoted(&q, &eq);
			q = ft_join_string(q, eq);
			res = ft_strjoin(res, "'");
			res = ft_strjoin(res, ft_assign_env(q, env_list));
			res = ft_strjoin(res, "'");
			return (res);
		}
		else
		{
			temp = ft_assign_env(q + 1, env_list);
			res = ft_strjoin(res, temp);
			free(temp);
			return (res);
		}		
		q++;
	}
	free(q);
	free(res);
	return (s);
}

void	ft_check_envs(char **q)
{
	int		count;
	char	*s;

	s = *q;
	count = ft_count_dollars(s);
	if (count % 2 == 0)
		while (*s && *s == '$')
			s++;
	else if (count % 2 != 0)
		while (*s && *(s + 1) == '$')
			s++;
	*q = s;
}

int	ft_env_examiner(char **s)
{
	char	*q;

	q = *s;
	while (*q)
	{
		if (*q == '$' && *q)
			q++;
		while (!ft_strchr(*q, "\'\"") && *q)
			q++;
		if (ft_strchr(*q, "\'\"") && *q)
		{
			q--;
			*q = 1;
			*s = q + 1;
			return (0);
		}
		if (!*q)
			break ;
		q++;
	}
	return (1);
}

char	*ft_append_env(char **split, char *ret, t_env *env_list)
{
	int		i;
	t_env	*temp_list;

	i = -1;
	while (split[++i])
	{
		temp_list = env_list;
		while (temp_list != NULL)
		{
			if (ft_strcmp(split[i], temp_list->name) == 0)
			{
				ret = ft_strjoin(ret, temp_list->path);
				break ;
			}
			temp_list = temp_list->next;
		}
	}
	freethis(split);
	return (ret);
}	

char	*ft_assign_env(char *s, t_env *env_list)
{
	char	**split;
	char	*ret;

	ret = ft_strdup("\0");
	if (*s == '$' && *(s + 1) == '\0')
	{
		free(s);
		free(ret);
		return (NULL);
	}
	split = ft_split(s, '$');
	if (*split == NULL)
	{
		freethis(split);
		return (NULL);
	}
	if (!ft_env_examiner(&s))
		return (s);
	if (**split == '?')
	{
		free(s);
		freethis(split);
		return ("$?");
	}
	ret = ft_append_env(split, ret, env_list);
	if (ret != NULL)
	{
		free(s);
		return (ret);
	}
	free(ret);
	return (NULL);
}

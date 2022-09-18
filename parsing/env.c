/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 01:10:55 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/18 01:18:42 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

char	*ft_search_for_env(char *s, t_env *env_list)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			s = ft_handle_quotes(s, env_list);
			res = ft_strjoin(res, "'");
			res = ft_strjoin(res, ft_assign_env(s + 1, env_list));
			res = ft_strjoin(res, "'");
			return (res);
		}
		else
			return (ft_strjoin(res, ft_assign_env(s + 1, env_list)));
		i++;
	}
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

char	*ft_assign_env(char *s, t_env *env_list)
{
	int		i;
	char	**split;
	char	*ret;
	t_env	*temp_list;
	int		flag;

	i = -1;
	flag = 0;
	if (*s == '$' && *(s + 1) == '\0')
		return (NULL);
	split = ft_split(s, '$');
	if (*split == NULL)
		return (NULL);
	ret = ft_strdup("\0");
	if (!ft_env_examiner(&s))
		return (s);
	if (**split == '?')
		return ("$?");
	while (split[++i])
	{
		temp_list = env_list;
		while (temp_list != NULL)
		{
			if (ft_strcmp(split[i], temp_list->name) == 0)
			{
				ret = ft_strjoin(ret, temp_list->path);
				flag = 1;
				break ;
			}
			temp_list = temp_list->next;
		}
		i++;
	}
	if (ret != NULL)
		return (ret);
	return (NULL);
}

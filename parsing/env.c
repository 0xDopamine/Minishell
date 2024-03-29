/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 01:10:55 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/30 11:42:28 by mbaioumy         ###   ########.fr       */
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
	res = NULL;
	while (q)
	{
		if (*q == '\'')
			return (ft_env_quoted(&q, &eq, env_list));
		else
		{
			temp = ft_assign_env(q + 1, env_list);
			res = strjoin_and_free1(res, temp);
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
	char	*tmp;

	i = -1;
	tmp = ret;
	while (split[++i])
	{
		temp_list = env_list;
		while (temp_list != NULL)
		{
			if (ft_strcmp(split[i], temp_list->name) == 0)
			{
				tmp = ret;
				ret = ft_strjoin(tmp, temp_list->path);
				free(tmp);
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
		return (set_free(s, ret, NULL, NULL));
	split = ft_split(s, '$');
	if (*split == NULL)
		return (set_free(NULL, NULL, split, NULL));
	if (!ft_env_examiner(&s))
		return (s);
	if (**split == '?')
		return (set_free(s, NULL, split, "$?"));
	ret = ft_append_env(split, ret, env_list);
	if (ret != NULL)
		return (ret);
	free(ret);
	return (NULL);
}

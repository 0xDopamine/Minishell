/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:17:08 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/11 17:42:17 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_envcmp(char *s1, char *s2)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = 0;
	while (s1[name_len] != '=')
		name_len++;
	if (ft_strchr('=', s2))
		return (0);
	while (s1[i] != '=' && s2[i] && s1[i] == s2[i])
		i++;
	if (i == name_len)
		return (1);
	else
		return (0);
}

void	ft_copy(char **ret, char *str, int sublen, int len)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (i < sublen)
	{
		ret[0][i] = str[i];
		i++;
	}
	ret[0][i++] = '\0';
	while (i < len)
	{
		ret[1][j] = str[i];
		i++;
		j++;
	}
	ret[1][j] = '\0';
}

char	**ft_split_typecont(char *str)
{
	int	sublen;
	int len;
	char **ret;

	len = 0;
	sublen = 0;
	ret = (char **)malloc(sizeof(char *) * 2);
	while (str[len])
		len++;
	while (str[sublen] != '=')
		sublen++;
	ret[0] = (char *)malloc(sublen + 1);
	ret[1] = (char *)malloc(len - sublen + 1);
	ft_copy(ret, str, sublen, len);
	return (ret);
}

void	ft_get_env(char **env, t_env **env_list)
{
	int i;
	char	**str;

	i = 0;
	while (env[i])
	{
		str = ft_split_typecont(env[i]);
		ft_lstadd_back(env_list, ft_lstnew(str[1], str[0]));
		i++;
	}
	return ;
}

char    **ft_find_path(void)
{
    return (ft_split(getenv("PATH"), ':'));
}
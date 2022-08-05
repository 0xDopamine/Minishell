/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:17:08 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/04 12:27:56 by abaioumy         ###   ########.fr       */
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
	if (strchr(s2, '='))
		return (0);
	while (s1[i] != '=' && s2[i] && s1[i] == s2[i])
		i++;
	if (i == name_len)
		return (1);
	else
		return (0);
}

void	ft_get_env(char **env, t_env **env_list)
{
	int i;
	
	i = 0;
	while (env[i])
	{
		ft_lstadd_back(env_list, ft_lstnew(env[i]));
		i++;
	}
	return ;
}

char    **ft_find_path(void)
{
    return (ft_split(getenv("PATH"), ':'));
}
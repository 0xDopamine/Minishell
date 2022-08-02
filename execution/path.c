/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:17:08 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/02 12:43:48 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
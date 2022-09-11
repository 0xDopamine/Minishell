/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:25:04 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/11 20:26:32 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	unset_loop(t_env *env, t_env *temp, t_env *prev, char *arg)
{
	while (env)
	{
		if (ft_envcmp(env->name, arg))
		{
			temp = env;
			prev->next = temp->next;
			ft_lstdelone(env, del);
			break ;
		}
		prev = env;
		env = env->next;
	}
}

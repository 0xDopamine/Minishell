/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:59:52 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/20 17:48:10 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	cd_ifoldpwd(char *str, t_env **env_list)
{
	if (str)
	{
		if (str[0] == '-')
		{
			cd_oldpwd(env_list);
			g.exit_status = EXIT_SUCCESS;
			return (1);
		}
	}
	return (0);
}

int	cd_home(void)
{
	if (chdir(getenv("HOME")) < 0)
	{
		perror("cd");
		g.exit_status = 2;
		return (1);
	}
	return (1);
}

int	cd_errors(void)
{
	g.exit_status = EXIT_FAILURE;
	return (1);
}
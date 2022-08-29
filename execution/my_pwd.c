/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:44:30 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/29 02:18:49 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_pwd(void)
{
	char	*s;
	char	*ret;

	s = NULL;
	ret = getcwd(s, PATH_MAX);
	if (ret == NULL)
	{
		g.exit_status = EXIT_FAILURE;
		return (1);
	}
	printf("%s\n", ret);
	g.exit_status = EXIT_SUCCESS;
	return (1);
}

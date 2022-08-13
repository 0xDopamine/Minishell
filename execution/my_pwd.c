/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:44:30 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/13 16:23:21 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_pwd(t_exec *line)
{
	char	*s;

	s = NULL;
	if (line->argv[1])
	{
        g.exit_status = EXIT_FAILURE;
		ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (getcwd(s, PATH_MAX) == NULL)
	{
		free(s);
		perror("pwd");
		g.exit_status = EXIT_FAILURE;
		return (1);
	}
	printf("%s\n", getcwd(s, PATH_MAX));
	free(s);
	g.exit_status = EXIT_SUCCESS;
	return (1);
}

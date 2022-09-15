/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:30:38 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/15 12:40:59 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	echo_case1(char *str, int fd)
{
	if (!str)
	{
		g.exit_status = EXIT_SUCCESS;
		ft_putstr_fd("\n", NULL, fd);
		return (1);
	}
	// if (!ft_strncmp(str, "$?", 2))
	// {
	// 	ft_putnbr_fd(g.exit_status, fd);
	// 	ft_putchar_fd('\n', fd);
	// 	g.exit_status = EXIT_SUCCESS;
	// 	return (1);
	// }
	return (0);
}

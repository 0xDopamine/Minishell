/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:01:03 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/18 15:53:52 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static	int	echo_check_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

static void	echo_ifnewline(t_exec *line, int i, int ifnl)
{
	if (ifnl)
		echo_str_nonl(line->argv, i);
	else
		echo_str_nl(line->argv, 1);
}

int	ft_echo(t_exec *line, int fd)
{
	int	i;
	int	ifnl;

	i = 1;
	ifnl = 0;
	if (echo_case1(line->argv[0], fd))
		return (1);
	while (echo_check_nl(line->argv[i]))
	{
		ifnl = 1;
		i++;
	}
	if (!line->argv[i])
	{
		g.exit_status = EXIT_SUCCESS;
		return (1);
	}
	if (ifnl)
		echo_ifnewline(line, i, ifnl);
	else
		echo_ifnewline(line, i, ifnl);
	g.exit_status = EXIT_SUCCESS;
	return (1);
}

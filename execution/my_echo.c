/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:01:03 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/15 14:13:28 by abaioumy         ###   ########.fr       */
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

static void	echo_ifnewline(t_exec *line, int i, int ifnl, int fd)
{
	int ifspace;

	ifspace = 0;
	if (ifnl)
	{
		if (!ft_strncmp(line->argv[i], "$?", 2))
		{
			ft_putnbr_fd(g.exit_status, fd);
			g.exit_status = EXIT_SUCCESS;
		}
		else
			ft_putstr_fd(line->argv[i], NULL, fd);
		i++;
		while (line->argv[i])
		{
			ft_putchar_fd(' ', fd);
			if (!ft_strncmp(line->argv[i], "$?", 2))
			{
				ft_putnbr_fd(g.exit_status, fd);
				g.exit_status = EXIT_SUCCESS;
			}
			else
				ft_putstr_fd(line->argv[i], NULL, fd);
			i++;
		}
	}
	else
	{
		i = 1;
		if (!ft_strncmp(line->argv[i], "$?", 2))
		{
			ft_putnbr_fd(g.exit_status, fd);
			g.exit_status = EXIT_SUCCESS;
		}
		else
			ft_putstr_fd(line->argv[i], NULL, fd);
		i++;
		if (!line->argv[i])
		{
			ft_putchar_fd('\n', fd);
			return ;
		}
		while (line->argv[i])
		{
			ft_putchar_fd(' ', fd);
			if (!ft_strncmp(line->argv[i], "$?", 2))
			{
				ft_putnbr_fd(g.exit_status, fd);
				g.exit_status = EXIT_SUCCESS;
			}
			else
				ft_putstr_fd(line->argv[i], NULL, fd);
			i++;
		}
		ft_putchar_fd('\n', fd);
	}
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
		echo_ifnewline(line, i, ifnl, fd);
	else
		echo_ifnewline(line, i, ifnl, fd);
	g.exit_status = EXIT_SUCCESS;
	return (1);
}

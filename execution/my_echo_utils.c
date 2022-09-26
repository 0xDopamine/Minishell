/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:30:38 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static	void	echo_print_strnl(char *str)
{
	ft_putchar_fd(' ', STDOUT_FILENO);
	if (!ft_strncmp(str, "$?", 2))
	{
		ft_putnbr_fd(g_var.exit_status, STDOUT_FILENO);
		g_var.exit_status = EXIT_SUCCESS;
	}
	else
		ft_putstr_fd(str, NULL, STDOUT_FILENO);
}

void	echo_str_nl(char **av, int i)
{
	if (!ft_strncmp(av[i], "$?", 2))
	{
		ft_putnbr_fd(g_var.exit_status, STDOUT_FILENO);
		g_var.exit_status = EXIT_SUCCESS;
	}
	else
		ft_putstr_fd(av[i], NULL, STDOUT_FILENO);
	i++;
	if (!av[i])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (av[i])
	{
		echo_print_strnl(av[i]);
		i++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	echo_str_nonl(char **av, int i)
{
	if (!ft_strncmp(av[i], "$?", 2))
	{
		ft_putnbr_fd(g_var.exit_status, STDOUT_FILENO);
		g_var.exit_status = EXIT_SUCCESS;
	}
	else
		ft_putstr_fd(av[i], NULL, STDOUT_FILENO);
	i++;
	while (av[i])
	{
		ft_putchar_fd(' ', STDOUT_FILENO);
		if (!ft_strncmp(av[i], "$?", 2))
		{
			ft_putnbr_fd(g_var.exit_status, STDOUT_FILENO);
			g_var.exit_status = EXIT_SUCCESS;
		}
		else
			ft_putstr_fd(av[i], NULL, STDOUT_FILENO);
		i++;
	}
}

int	echo_case1(char *str, int fd)
{
	if (!str)
	{
		g_var.exit_status = EXIT_SUCCESS;
		ft_putstr_fd("\n", NULL, fd);
		return (1);
	}
	return (0);
}

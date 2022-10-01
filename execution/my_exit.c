/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:11:59 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static	int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(char *str)
{
	int					i;
	unsigned long long	result;
	int					sign;

	result = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]) == 1)
	{
		result = (result * 10) + str[i] - 48;
		i++;
	}
	return (result * sign);
}

static	int	exit_ifnumeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' && str[i + 1] == '\0')
	{
		ft_putstr_fd("exit: '", str, STDERR_FILENO);
		ft_putstr_fd("': numeric argument required\n", NULL, STDERR_FILENO);
		return (1);
	}
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57) && str[i] != '-')
		{
			ft_putstr_fd("exit: '", str, STDERR_FILENO);
			ft_putstr_fd("': numeric argument required\n", NULL, STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_exit(char **argv)
{
	int	exit_val;

	if (!argv[1])
	{
		freethis(argv);
		exit(g_var.exit_status);
	}
	if (argv[1] && !argv[2])
		exit_val = ft_atoi(argv[1]);
	printf("exit\n");
	if (exit_ifnumeric(argv[1]))
	{
		freethis(argv);
		exit(255);
	}
	if (argv[1] && !argv[2])
	{
		freethis(argv);
		exit(exit_val);
	}
	g_var.exit_status = EXIT_FAILURE;
	ft_putstr_fd("exit: too many arguments\n", NULL, STDERR_FILENO);
	return (1);
}

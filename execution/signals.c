/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:15:05 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:22:40 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>

void	ft_sig_here(int signal)
{
	(void)signal;
	close(0);
	g_var.exit_status = 1;
	g_var.here_sig = 1;
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_var.exit_status = 130;
		return ;
	}
	return ;
}

int	ft_get_sigint(int infd)
{
	signal(SIGINT, ft_sig_handler);
	g_var.here_sig = 0;
	dup2(infd, 0);
	close(infd);
	return (1);
}

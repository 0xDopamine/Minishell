/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:15:05 by abaioumy         #+#    #+#             */
/*   Updated: 2022/09/21 18:22:40 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>

void	ft_sig_here(int signal)
{
	(void)signal;
	close(0), printf("%s:%d ---> %d\n", __FILE__, __LINE__, 0);
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

int	ft_here_signal(int infd)
{
	signal(SIGINT, ft_sig_handler);
	g_var.here_sig = 0;
	dup2(infd, 0);
	close(infd), printf("%s:%d ---> %d\n", __FILE__, __LINE__, infd);
	return (1);
}

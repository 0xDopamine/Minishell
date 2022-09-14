/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:16:26 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/14 22:11:13 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	del(char *path)
{
	free(path);
}

void	ft_lstdelone(t_env *lst, void (*del)(char*))
{
	if (lst)
	{
		(del)(lst->path);
		(del)(lst->name);
		free(lst);
	}
	return ;
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, char *str2, int fd)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
		ft_putchar_fd(str[i++], fd);
	if (str2 == NULL)
		return ;
	i = 0;
	while (str2[i])
		ft_putchar_fd(str2[i++], fd);
}

void	ft_putnbr_fd(int nb, int fd)
{
	int	nbr;

	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		if (nb == -2147483648)
		{
			write(fd, "2147483648", 10);
			return ;
		}		
		nbr = nb * -1;
	}
	else
		nbr = nb;
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
	}
	ft_putchar_fd(nbr % 10 + '0', fd);
}

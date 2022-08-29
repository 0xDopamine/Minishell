/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:16:26 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/29 02:18:49 by mbaioumy         ###   ########.fr       */
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

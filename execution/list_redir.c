/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:52:00 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/23 19:16:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_redir	*ft_lstlastredir(t_redir *lst)
{
	t_redir	*last;

	last = lst;
	if (last == NULL)
		return (lst);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	ft_lstadd_frontredir(t_redir **lst, t_redir *new)
{
	if (lst == NULL && new == NULL)
		return ;
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_redir(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		ft_lstadd_frontredir(lst, new);
		return ;
	}
	last = ft_lstlastredir(*lst);
	last->next = new;
}

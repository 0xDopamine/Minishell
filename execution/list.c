/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:45:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/17 01:51:10 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec.h"

int	ft_lstsize(t_env *lst)
{
	int		size;
	t_env	*temp;

	size = 0;
	temp = lst;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*last;

	last = lst;
	if (last == NULL)
		return (lst);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	ft_lstadd_front(t_env **lst, t_env *new)
{
	if (lst == NULL && new == NULL)
		return ;
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

t_env	*ft_lstnew(char *path, char *name, int ifnull)
{
	t_env	*head;
	int		i;

	i = 0;
	head = (t_env *)malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	head->path = ft_strdup(path);
	head->name = ft_strdup(name);
	head->ifnull = ifnull;
	head->next = NULL;
	return (head);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

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
	printf("new: %s\n", new->file);
	last = ft_lstlastredir(*lst);
	last->next = new;
}

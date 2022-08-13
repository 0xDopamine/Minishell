/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:45:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/13 16:25:30 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "header.h"

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

t_env	*ft_lstnew(char *content, char *type)
{
	t_env	*head;
	int		i;

	i = 0;
	head = (t_env *)malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	head->content = ft_strdup(content);
	head->type = ft_strdup(type);
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
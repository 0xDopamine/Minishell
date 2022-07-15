/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:29:39 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/07/15 21:39:47 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*ft_lstnew(char  **content)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

// t_list	*copytolist(int *arr, int size)
// {
// 	int		i;
// 	t_list	*stack;

// 	i = 0;
// 	while (i < size)
// 	{
// 		ft_lstadd_back(&stack, ft_lstnew(arr[i]));
// 		i++;
// 	}
// 	return (stack);
// }

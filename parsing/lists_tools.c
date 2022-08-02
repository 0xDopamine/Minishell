/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:26:22 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/07/19 20:41:59 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*tmp;

	size = 0;
	tmp = lst;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

// int	*copytoarray(t_list *stack)
// {
// 	int	size;
// 	int	i;
// 	int	*arr;

// 	i = 0;
// 	size = ft_lstsize(stack);
// 	arr = (int *)malloc(sizeof(int) * size);
// 	while (stack)
// 	{
// 		arr[i] = stack->content;
// 		i++;
// 		stack = stack->next;
// 	}
// 	return (arr);
// }

// void	print_arr(int *arr, int size)
// {
// 	int	i;

// 	i = 0;
// 	while (i < size)
// 	{
// 		printf("%d\n", arr[i]);
// 		i++;
// 	}
// }
void	print_list(t_list *stack)
{
	int	i;

	i = 0;
	while (stack != NULL)
	{
		printf("Token: %s value: %d\n", stack->content, stack->type);
		stack = stack->next;
		i++;
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list	*curr;
	t_list	*next;

	curr = *lst;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	*lst = NULL;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst == NULL && new == NULL)
		return ;
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evar.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 01:26:28 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/23 17:14:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

int	*check_var(char *str)
{
	int	i;
	int	*state;

	i = 0;
	state = malloc(sizeof(int) * 2);
	state[0] = NOT_VAR;
	state[1] = NOT_QUOTED;
	while (str[i])
	{
		if (str[i] == ' ')
			break ;
		if (str[i] == '=')
		{
			state[0] = IS_VAR;
			if (ft_strchr(str[i + 1], "\'\""))
				state[1] = QUOTED;
		}
		i++;
	}
	return (state);
}

int	check_state(int *state)
{
	if (state[0] == IS_VAR && state[1] == QUOTED)
		return (1);
	return (0);
}

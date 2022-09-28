/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:44:30 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**ft_myenv(t_env *env)
{
	char	**str;
	char	*name;
	int		i;

	i = 0;
	name = NULL;
	str = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (!str)
		return (NULL);
	while (env)
	{
		name = ft_strjoin(env->name, "=");
		if (!env->path)
			str[i] = name;
		else
		{
			str[i] = ft_strjoin(name, env->path);
			free(name);
		}
		env = env->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

int	ft_pwd(void)
{
	char	*s;
	char	*ret;

	s = NULL;
	ret = getcwd(s, PATH_MAX);
	if (ret == NULL)
	{
		g_var.exit_status = EXIT_FAILURE;
		return (1);
	}
	printf("retpwd:: %s\n", ret);
	free (ret);
	free (s);
	g_var.exit_status = EXIT_SUCCESS;
	return (1);
}

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

char	*expand_heredoc_nq(char *str, char *eq, t_env *env_list)
{
	char	*tmp;
	char	*res;

	fetch_env(&str, &eq);
	tmp = ft_join_string(str, eq);
	res = ft_assign_env(tmp, env_list);
	free(tmp);
	return (res);
}

char	*expand_heredoc_q(char *str, char *eq, char tok, t_env *env_list)
{
	char	*res;
	char	*tmp;

	fetch_env(&str, &eq);
	res = malloc(2);
	res[0] = tok;
	res[1] = '\0';
	tmp = ft_join_string(str, eq);
	res = strjoin_and_free(res, ft_assign_env(tmp, env_list));
	free(tmp);
	res = ft_copy_char(res, tok);
	return (res);
}

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
	printf("%s\n", ret);
	free (ret);
	free (s);
	g_var.exit_status = EXIT_SUCCESS;
	return (1);
}

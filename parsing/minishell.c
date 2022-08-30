/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/08/29 19:19:07 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"
#include <readline/readline.h>

t_global g = { 0 };


// void	ft_assign_env(char *s, t_env_p *env_list)
// {
// 	int	i;

// 	i = 0;
// 	printf("string %s\n", s);
// 	while (s[i])
// 	{
// 		if (s[i] == '$')
// 		{
// 			printf("here %s\n", s + i + 1);
// 			return (ft_assign_env(s + i + 1, env_list));
// 		}	
// 		i++;
// 	}
// 	while (env_list->next != NULL)
// 	{
// 		if (ft_strncmp(s, env_list->name, ft_strlen(s)) == 0)
// 			return ;
// 		env_list = env_list->next;
// 	}
// }

int	ft_check_quotes(char *s)
{
	int		i;
	int		j;
	char	q;

	i = 0;
	while (s[i])
	{
		if (ft_strchr(s[i], "\"\'") && s[i + 1] != '\0')
		{
			j = i + 1;
			q = s[i];
			while (s[j] != q && s)
				j++;
			if (s[j] == '\0')
			{
				perror("quotes error");
				return (258);
			}	
		}
		i++;
	}
	return (1);
}

char	*ft_handle_quotes(char *q, t_env_p *env_list)
{
	char	*s;
	char	*res;
	char	*temp;
	int		i;

	s = q;
	(void)env_list;
	res = malloc(sizeof(char) * 10000000000);
	res[0] = 0;
	i = 0;
	// if (ft_check_quotes(s))
	// {	
		while (s && ft_strchr(*s, "\"\'"))
		{
			temp = s + 1;
			printf("i : %d\ntemp: %s\ns: %s\n", i, temp, s);
			if (*temp != *s)
			{
				while (*temp != *s && *temp)
				{
					res[i] = *temp;
					i++;
					temp++;
				}
				res[i] = '\0';
				printf("res: %s\n", res);
				if (*temp != 0)
					s = temp;
				else
					break ;
			}
			else
				s++;
		}	
	// }
	// else
	// 	return (res);
	return(res);
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		// rl_on_new_line();
		// write(1, "\n", 1);
		// rl_replace_line("", 0); /* comment all of this cuz we need to install brew and other things in goinfre */
		// rl_redisplay();
		g.exit_status = 130;
		return ;
	}
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
		g.exit_status = 0;
		return ;
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_cmd	*simpleCommand;
	t_env 	*env_list;
	t_env_p	*env_list_p;

	line = NULL;
	(void)argc;
	(void)argv;
	simpleCommand = malloc(sizeof(t_cmd));
	ft_get_env(env, &env_list);
	env_list_p = (t_env_p *)env_list;
	printf("Two brothers minishell\n");
	//don't use CTRL -C signal now
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, ft_sig_handler);
	while (1)
	{
		line = readline("$> ");
		if (!line)
		{
			ft_putstr_fd("\nexit\n", NULL, STDOUT_FILENO);
			exit(255); /* needs to be finished */
		}
		if (*line)
			add_history(line);
		line = ft_strdup(spaces(line));
		simpleCommand = parsepipe(&line, env_list_p);
		ft_check_cmd(simpleCommand, env, &env_list);
		// system("leaks minishell");
		// demo(line);
	} 
	return 0;
}
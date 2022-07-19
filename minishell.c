/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:49:43 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/07/19 21:02:28 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <readline/readline.h>

char	**builtins_init(void)
{
	char	**builts;

	builts = malloc(sizeof(char *) * 8);
	builts[0] = ft_strdup("echo");
	builts[1] = ft_strdup("cd");
	builts[2] = ft_strdup("pwd");
	builts[3] = ft_strdup("export");
	builts[4] = ft_strdup("unset");
	builts[5] = ft_strdup("env");
	builts[6] = ft_strdup("exit");
	builts[7] = NULL;
	return (builts);	
}

int	check_builtins(char *token, char **builts)
{
	int	i;

	i = 0;
	while (builts[i])
	{
		if (builts[i] == token)
			return (1);
		i++;
	}
	return (0);
}

t_token *init_token(char *value, int type)
{
	t_token *token = ft_calloc(1, sizeof(t_token));
	token->value = value;
	token->type = type;
	return (token);
}

t_token	*append_token(char c, int type)
{
	char	*value;
	t_token	*tok;

	value = ft_calloc(2, sizeof(char));
	tok = malloc(sizeof(t_token));
	value[0] = c;
	tok = init_token(value, type);
	return(tok);
}

t_token	*ft_isgreat(char *str)
{
	int		i;
	t_token	*tok;
	char	*value;
	int		type;

	i = 0;
	tok = malloc(sizeof(t_token));
	value = NULL;
	type = 0;
	while (str[i] != ' ' && str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>') && str[i + 1])
		{
			value = ft_calloc(3, sizeof(char));
			value[0] = str[i];
			value[1] = str[i + 1];
			type = 3;
			break ;
		}
		else if ((str[i] == '>' && str[i + 1] != '>') && str[i + 1])
		{
			value = ft_calloc(2, sizeof(char));
			value[0] = str[i];
			type = 2;
			break ;
		}
		i++;
	}
	tok = init_token(value, type);
	return (tok);
}

t_token	*ft_isless(char *str)
{
	int		i;
	t_token	*tok;
	char	*value;
	int		type;

	i = 0;
	tok = malloc(sizeof(t_token));
	type = 0;
	value = NULL;
	while (str[i] != ' ' && str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 1])
		{
			value = ft_calloc(3, sizeof(char));
			value[0] = str[i];
			value[1] = str[i + 1];
			type = 3;
			break ;
		}
		else if (str[i] == '<' && str[i + 1] != '<' && str[i + 1])
		{
			value = ft_calloc(2, sizeof(char));
			value[0] = str[i];
			type = 2;
			break ;
		}
		i++;
	}
	tok = init_token(value, type);
	return (tok);
}

t_list	*lexer(t_token *token, t_list *lst_tokens, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isalpha(line[i]))
			token = append_token(line[i], 6);
		else if (line[i] == '|')
			token = append_token(line[i], 0);
		else if (line[i] == ' ')
			token = append_token(line[i], 1);
		else if (line[i] == '>')
		{	
			token = ft_isgreat(line + i);
			if (ft_strncmp(token->value, ">>", 3))
				i++;
		}
		else if (line[i] == '<')
		{
			token = ft_isless(line + i);
			if (ft_strncmp(token->value, "<<", 3))
				i++;
		}
		else if (line[i] == '\'')
			token = append_token(line[i], 7);
		else if (line[i] == '\"')
			token = append_token(line[i], 8);
		else if (line[i] == '-')
			token = append_token(line[i], 9);
		ft_lstadd_back(&lst_tokens, ft_lstnew(token->value, token->type));
		i++;
	}
	return (lst_tokens);
}

t_list	*process(char *line)
{
	t_token	*token;
	t_list	*lst_tokens;

	token = malloc(sizeof(t_token));
	lst_tokens = NULL;
	lst_tokens = lexer(token, lst_tokens, line);
	return (lst_tokens);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_list	*lst_tokens;

	line = NULL;
	(void)argc;
	(void)argv;
	(void)env;
	lst_tokens = malloc(sizeof(t_list));
	while (1)
	{
		line = readline("$>");
		if (line)
			add_history(line);
		lst_tokens = process(line);
		print_list(lst_tokens);
		printf("%s\n", line);
	} 
	return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:03:11 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/17 01:26:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

void	show_data(t_data *data, int i)
{
	int	j;
	t_list *tmp;

	j = 0;
	ft_printf("\n%d table\n", i);
	tmp = data->input;
	if (tmp != NULL)
	{
		while (tmp != NULL)
		{
			ft_printf("input %d : %s\n", ++j, tmp->content);
			tmp = tmp->next;
		}
	}
	tmp = data->output;
	if (tmp != NULL)
	{
		while (tmp != NULL)
		{
			ft_printf("output %d : %s\n", ++j, tmp->content);
			tmp = tmp->next;
		}
	}
	if (data->command != NULL)
		ft_printf("command : %s\n", data->command);
	tmp = data->arg;
	if (tmp != NULL)
	{
		while (tmp != NULL)
		{
			ft_printf("arg %d : %s\n", ++j, tmp->content);
			tmp = tmp->next;
		}
	}
	if (data->next != NULL)
		show_data(data->next, ++i);
}

static char	*set_prompt()
{
	char	*user;
	char	*pwd;
	char	*prompt;

	user = getenv("USER");
	pwd = getcwd(NULL, 0);
	prompt = ft_strjoin("\e[32m", user);
	prompt = ft_strjoin(prompt, "\e[94m ");
	prompt = ft_strjoin(prompt, pwd);
	prompt = ft_strjoin(prompt, "\e[0m");
	prompt = ft_strjoin(prompt, " $ ");

	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	**lexer;
	t_data	*data;
	char	*prompt;

	g_env = envp;
	(void) argc;
	(void) argv;
	while (1)
	{
		prompt = set_prompt();
		str = readline(prompt);
		if (str == NULL)
			return (1);
		if (ft_strncmp(str, "\0", 2))
			add_history(str);
		lexer = pre_parser(str);
		if (lexer == NULL)
			return (1);
		data = parser(lexer);
		freetab(lexer);
		if (data == NULL)
			return (1);
		if (data->command != NULL)
			exec(data);
		clear_data(data);
		free(prompt);
	}
}
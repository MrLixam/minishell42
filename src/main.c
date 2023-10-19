/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:03:11 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/18 16:14:41 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include <fcntl.h>

int	g_exit;

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

int	main(int argc, char **argv, char **envp)
{
	char	*str;
//	char	**lexer;
	t_local	local;

	create_env(local.env, envp);
	g_exit = 0;
	(void) argc;
	(void) argv;
	while (1)
	{
		str = readline("\e[94mminishell\e[0m$ ");
		if (str == NULL)
			return (1);
		if (ft_strncmp(str, "\0", 2))
			add_history(str);
		//
		parser(local, str);
		/*
		lexer = pre_parser(str);
		if (lexer == NULL)
			return (1);
		local.data = parser(lexer);
		freetab(lexer);
		*/
		if (local.data == NULL)
			return (1);
	//	if (local->data->command != NULL)
	//		exec(data);
		show_data(local.data, 0);
		clear_data(local.data);
	}
	//clear_local(local);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:03:11 by gpouzet           #+#    #+#             */
/*   Updated: 2023/09/11 16:27:51 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
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
	if (data->option != NULL)
		ft_printf("option : %s\n", data->option);
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

int	main(void)
{
	char	*str;
	char	**lexer;
	t_data	*data;

	while (1)
	{
		str = readline(NULL);
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
		ft_printf("[	data table	]\n");
		show_data(data, 1);
		ft_printf("[	end		]\n");
//		clear_data(data);
	}
}

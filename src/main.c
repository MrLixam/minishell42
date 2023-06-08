/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:03:11 by gpouzet           #+#    #+#             */
/*   Updated: 2023/06/08 16:49:49 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

void	show_data(t_data *data, int i)
{
	ft_printf("\n%d table\n", i);
	if (data->input != NULL)
		ft_printf("input : %s\n", data->input);
	if (data->output != NULL)
		ft_printf("output : %s\n", data->output);
	if (data->command != NULL)
		ft_printf("command : %s\n", data->command);
	if (data->option != NULL)
		ft_printf("option : %s\n", data->option);
	if (data->arg != NULL)
		ft_printf("arg : %s\n", data->input);
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
		lexer = ft_split(str, ' ');
		free(str);
		if (lexer == NULL)
			return (1);
		data = parser(lexer);
		freetab(lexer);
		ft_printf("[	data table	]\n");
		show_data(data, 1);
		ft_printf("[	end		]\n");
		clear_data(data);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:03:23 by gpouzet           #+#    #+#             */
/*   Updated: 2023/06/08 16:36:01 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_data	*new_data(void)
{
	t_data	*create;

	create = ft_calloc(1, sizeof(t_data));
	create->input = NULL;
	create->output = NULL;
	create->command = NULL;
	create->option = NULL;
	create->arg = NULL;
	create->next = NULL;
	return(create);
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	clear_data(t_data *data)
{
	if (data->input != NULL)
		free(data->input);
	if (data->output != NULL)
		free(data->output);
	if (data->command != NULL)
		free(data->command);
	if (data->option != NULL)
		free(data->option);
	if (data->arg != NULL)
		freetab(data->arg);
	if (data->next != NULL)
		clear_data(data->next);
	free(data);
}

t_data	*parser(char **lexer)
{
	t_data	*first;
	t_data	*curent;
	int	i;

	i = 0;
	first = new_data();
	curent = first;
	while (lexer[i])
	{
		if (!ft_strncmp(lexer[i], "<", ft_strlen(lexer[i])))
			curent->input = ft_strdup(lexer[++i]);
		else if (!ft_strncmp(lexer[i], ">", ft_strlen(lexer[i])))
			curent->output = ft_strdup(lexer[++i]);
		else if (curent->command == NULL)
			curent->command = ft_strdup(lexer[i]);
		else if (lexer[i][0] == '-')
			curent->option = ft_strdup(lexer[i]);
		else if (!ft_strncmp(lexer[i], "|", ft_strlen(lexer[i])))
		{
			curent->next = new_data();
			curent = curent->next;
		}
	//	else
	//		append (lexer[i], curent.arg);
		i++;
	}
	return (first);
}

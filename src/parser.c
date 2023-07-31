/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:03:23 by gpouzet           #+#    #+#             */
/*   Updated: 2023/07/31 11:49:56 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_data	*new_data(void)
{
	t_data	*create;

	create = ft_calloc(1, sizeof(t_data));
	if (create == NULL)
		return (NULL);
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

int	new_arg(t_list **lst, char *arg)
{
	t_list	*new;
	char	*tmp;

	tmp = ft_strdup(arg);
	if (tmp == NULL)
		return (1);
	new = ft_lstnew(tmp);
	ft_lstadd_back(lst, new);
	return (0);
}

/*
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
*/
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
/*		if (!ft_strncmp(lexer[i], "<", ft_strlen(lexer[i])))
		{
			curent->input = ft_strdup(lexer[++i]);
			if (curent->input == NULL)
				return (NULL);
		}
		else if (!ft_strncmp(lexer[i], ">", ft_strlen(lexer[i])))
		{
			curent->output = ft_strdup(lexer[++i]);
			if (curent->output == NULL)
				return (NULL);
		}
		else */if (curent->command == NULL)
		{
			curent->command = ft_strdup(lexer[i]);
			if (curent->command == NULL)
				return (NULL);
		}/*
		else if (lexer[i][0] == '-')
		{
			curent->option = ft_strdup(lexer[i]);
			if (curent->option == NULL)
				return (NULL);
		}*/
		else if (!ft_strncmp(lexer[i], "|", ft_strlen(lexer[i])))
		{
			curent->next = new_data();
			if (curent->next == NULL)
				return (NULL);
			curent = curent->next;
		}
		else
			if (new_arg(&curent->arg, lexer[i]))
				return (NULL);
		i++;
	}
	return (first);
}

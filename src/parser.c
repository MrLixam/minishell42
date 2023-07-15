/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:03:23 by gpouzet           #+#    #+#             */
/*   Updated: 2023/07/14 19:18:34 by gpouzet          ###   ########.fr       */
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
/*
char	**arg(char **arg, char *lexer)
{
	char	**newarg;
	int		i;

	i = -1;
	newarg = ft_calloc(sizeof(char *), ft_tabstrlen(arg) + 1);
	while (arg[++i] != NULL)
		newarg[i] = ft_strdup(arg[i]);
	 gerer lexer
	if (lexer[0] == "'")
	 fin 
	if (arg != NULL)
		freetab(arg);
	return (newarg);
}
*/
char	**append(char *lexer, char **src)
{
	char	**dest;
	int		i;

	i = 0;
	if (lexer == NULL)
	{
		freetab(src);
		return (NULL);
	}
	dest = ft_calloc(sizeof(char **), ft_tabstrlen(src) + 1 + (src == NULL));
	if (dest == NULL)
	{
		freetab(src);
		return (NULL);
	}
	while (src != NULL && i < (int)ft_tabstrlen(src))
	{
		dest[i] = ft_strdup(src[i]);
		if (dest[i] == NULL)
		{
			freetab(src);
			freetab(dest);
			return (NULL);
		}
		i++;
	}
//	if (src != NULL)
//		freetab(src);
	dest[i] = ft_strdup(lexer);
	if (dest[i] == NULL)
	{
		freetab(src);
		return (NULL);
	}
	return (dest);
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
		else if (curent->command == NULL)
		{
			curent->command = ft_strdup(lexer[i]);
			if (curent->command == NULL)
				return (NULL);
		}
		else if (lexer[i][0] == '-')
		{
			curent->option = ft_strdup(lexer[i]);
			if (curent->option == NULL)
				return (NULL);
		}
		else if (!ft_strncmp(lexer[i], "|", ft_strlen(lexer[i])))
		{
			curent->next = new_data();
			if (curent->next == NULL)
				return (NULL);
			curent = curent->next;
		}
		else
		{
			curent->arg = append(lexer[i], curent->arg);
			if (curent->arg == NULL)
				return (NULL);
		}
		i++;
	}
	return (first);
}

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

static int	new_arg(t_list **lst, char *arg)
{
	t_list	*new;
	char	*tmp;

	tmp = ft_strdup(arg);
	if (tmp == NULL)
		return (write(1, "malloc failed \n", 15));
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

int	redirection(char *lexer, t_data *data)
{
	int		i;
	int		j;
	t_list	*tmp;

	i = 0;
	while (lexer[i])
	{
		j = i;
		while (lexer[i] == '<' || lexer[i] == '>')
			i++;
		if (i - j > 2 && ft_strncmp(lexer + j, "<<<", i - j))
			return (1);
		ft_lstadd_back(&data->redirection, ft_lstnew(ft_substr(lexer, j, i - j)));
		tmp = ft_lstlast(data->redirection);
		if (tmp == NULL)
			return (1);
		j = i;
		while (lexer[i] && lexer[i] != '<' && lexer[i] != '>')
			i++;
		if (i - j > 0)
		{
			ft_lstadd_back(&data->redirection, ft_lstnew(ft_substr(lexer, j, i - j)));
			tmp = ft_lstlast(data->redirection);
			if (tmp == NULL)
				return (1);
		}
	}
	return (0);
}

int	switcher(t_data *data)
{
	t_list	*src;

	src = data->redirection;
	while (src != NULL)
	{
		if (!ft_strncmp(src->content, ">", 1))
		{
			if (new_arg(&data->output, src->content))
				return (1);
			src = src->next;
			if (!src)
				return (write(1, "invalide syntax\n", 16));
			if (new_arg(&data->output, src->content))
				return (1);
		}
		if (!ft_strncmp(src->content, "<", 1))
		{
			if (new_arg(&data->input, src->content))
				return (1);
			src = src->next;
			if (!src)
				return (write(1, "invalide syntax\n", 16));
			if (new_arg(&data->input, src->content))
				return (1);
		}
			src = src->next;
	}
	return (0);
}

t_data	*parser(char **lexer)
{
	t_data	*first;
	t_data	*curent;
	t_list	*tmp;
	int	i;

	i = 0;
	first = new_data();
	curent = first;
	while (lexer[i])
	{
		tmp = ft_lstlast(curent->redirection);
		if (tmp && (!ft_strncmp(tmp->content, ">", 1) || !ft_strncmp(tmp->content, "<", 1)))
		{
			if (new_arg(&curent->redirection, lexer[i]))
				return (NULL);
		}
		else if (lexer[i][0] == '<' || lexer[i][0] == '>')
		{
			if (redirection(lexer[i], curent))
				return (NULL);
		}
		else if (curent->command == NULL)
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
			switcher(curent);
			curent->next = new_data();
			if (curent->next == NULL)
				return (NULL);
			curent = curent->next;
		}
		else
		{
			if (new_arg(&curent->arg, lexer[i]))
				return (NULL);
		}
		i++;
	}
	switcher(curent);
	return (first);
}

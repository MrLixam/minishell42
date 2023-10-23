/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:03:23 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/23 15:57:10 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir(t_list **redir, char *lexer, int i, int j)
{
	t_list	*tmp;

	ft_lstadd_back(redir, ft_lstnew(ft_substr(lexer, j, i - j)));
	tmp = ft_lstlast(*redir);
	if (tmp == NULL)
		return (1);
	return (0);
}

int	redirection(char *lexer, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (lexer[i])
	{
		j = i;
		while (lexer[i] == '<' || lexer[i] == '>')
			i++;
		if (i - j > 2 && ft_strncmp(lexer + j, "<<<", i - j))
			return (1);
		if (redir(&data->redir, lexer, i, j))
			return (1);
		j = i;
		while (lexer[i] && lexer[i] != '<' && lexer[i] != '>')
			i++;
		if (i - j > 0)
			if (redir(&data->redir, lexer, i, j))
				return (1);
	}
	return (0);
}

int	switcher(t_data *data, t_list *src)
{
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

t_data	*switch_elem(char **lexer)
{
	t_data	*first;
	t_data	*curent;
	t_list	*tmp;
	int		i;

	i = -1;
	first = new_data();
	curent = first;
	while (lexer[++i])
	{
		tmp = ft_lstlast(curent->redir);
		if (tmp && (!ft_strncmp(tmp->content, ">", 1) || !ft_strncmp(tmp->content, "<", 1)))
		{
			if (lexer[i][0] == '<' || lexer[i][0] == '>' || new_arg(&curent->redir, lexer[i]))
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
		}
		else if (!ft_strncmp(lexer[i], "|", ft_strlen(lexer[i])))
		{
			switcher(curent, curent->redir);
			curent->next = new_data();
			if (curent->next == NULL)
				return (NULL);
			curent = curent->next;
		}
		else
			if (new_arg(&curent->arg, lexer[i]))
				return (NULL);
	}
	switcher(curent, curent->redir);
	return (first);
}

int	parser(t_local *local, char *lexer)
{
	char	**tmp;

	if (check_quote(lexer))
	{
		write(1, "error\n", 6);
		return (1);
	}
	tmp = arg_sep(lexer);
	free(lexer);
	if (tmp == NULL)
		return (1);
	if (swap_env_var(local, tmp))
		return (1);
	if (tmp == NULL)
		return (1);
	local->data = switch_elem(tmp);
	freetab(tmp);
	return (0);
}

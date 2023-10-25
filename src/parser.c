/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:03:23 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/25 20:15:50 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	switcher(t_data *data, t_list *src)
{
	while (src != NULL)
	{
		if (!ft_strncmp(src->content, ">", 1))
		{
			if (new_arg(&data->output, src->content))
				return (1);
			src = src->next;
			if (!src)
				return (write(1, "invalid syntax\n", 16));
			if (new_arg(&data->output, src->content))
				return (1);
		}
		if (!ft_strncmp(src->content, "<", 1))
		{
			if (new_arg(&data->input, src->content))
				return (1);
			src = src->next;
			if (!src)
				return (write(1, "invalid syntax\n", 16));
			if (new_arg(&data->input, src->content))
				return (1);
		}
		src = src->next;
	}
	return (0);
}

static int	elem_dispatch(t_data *curent, char *lex, int ret)
{
	t_list	*tmp;

	tmp = ft_lstlast(curent->redir);
	if (tmp && (!ft_strncmp(tmp->content, ">", 1)
			|| !ft_strncmp(tmp->content, "<", 1)))
	{
		ret = 2;
		if (lex[0] == '<' || lex[0] == '>' || new_arg(&curent->redir, lex))
			return (1);
	}
	else if (lex[0] == '<' || lex[0] == '>')
	{
		ret = 2;
		if (redirection(lex, curent))
			return (1);
	}
	else if (curent->command == NULL)
	{
		ret = 2;
		curent->command = ft_strdup(lex);
		if (curent->command == NULL)
			return (1);
	}
	return (ret);
}

static int	next_data(t_data **curent)
{
	if (switcher(*curent, (*curent)->redir))
		return (1);
	if (format_quote(*curent))
		return (1);
	(*curent)->next = new_data();
	if ((*curent)->next == NULL)
		return (1);
	*curent = (*curent)->next;
	return (0);
}

t_data	*switch_elem(char **lexer, t_data *first)
{
	t_data	*curent;
	int		i;
	int		cmp;

	i = -1;
	curent = first;
	while (lexer[++i])
	{
		cmp = elem_dispatch(curent, lexer[i], 0);
		if (cmp == 1)
			return (NULL);
		if (!cmp && !ft_strncmp(lexer[i], "|", ft_strlen(lexer[i])))
			if (next_data(&curent))
				return (NULL);
		if (!cmp && ft_strncmp(lexer[i], "|", ft_strlen(lexer[i])))
			if (new_arg(&curent->arg, lexer[i]))
				return (NULL);
	}
	if (switcher(curent, curent->redir))
		return (NULL);
	if (format_quote(curent))
		return (NULL);
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
	local->data = new_data();
	if (!local->data)
		return (1);
	if (!switch_elem(tmp, local->data))
		return (1);
	freetab(tmp);
	return (0);
}

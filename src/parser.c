/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:03:23 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/31 03:45:44 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	elem_dispatch(t_data *curent, char *lex, int ret)
{
	t_list	*tmp;

	tmp = ft_lstlast(curent->redir);
	if (tmp && (!ft_strncmp(tmp->content, ">", 1)
			|| !ft_strncmp(tmp->content, "<", 1)))
	{
		ret = err_dispatch(lex);
		if (ret)
			return (ret);
		if (new_arg(&curent->redir, lex))
			return (1);
	}
	else if (lex[0] == '<' || lex[0] == '>')
		ret = redirection(lex, curent);
	return (ret);
}

static int	next_data(t_data **curent)
{
	if (!empty_data(*curent))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (2);
	}
	if (format_quote(*curent))
		return (1);
	(*curent)->next = new_data();
	if ((*curent)->next == NULL)
		return (1);
	*curent = (*curent)->next;
	return (0);
}

static int	error_redir(t_data *current)
{
	t_list	*tmp;
	char	*tmp2;

	if (!empty_data(current))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (2);
	}
	if (format_quote(current))
		return (1);
	if (current->redir == NULL)
		return (0);
	tmp = ft_lstlast(current->redir);
	if (!tmp)
		return (1);
	tmp2 = (char *)tmp->content;
	if (tmp2[0] == '<' || tmp2[0] == '>')
	{
		ft_putstr_fd("minishell:", 2);
		ft_putendl_fd(" syntax error near unexpected token `newline'", 2);
		return (2);
	}
	return (0);
}

static int	switch_elem(char **lexer, t_data *first, int i, int cmp)
{
	t_data	*curent;

	curent = first;
	while (lexer[++i])
	{
		cmp = -1;
		if (ft_strlen(lexer[i]))
			cmp = elem_dispatch(curent, lexer[i], -1);
		if (cmp > 0)
			return (cmp);
		if (cmp && !ft_strncmp(lexer[i], "|", 2))
			cmp = next_data(&curent);
		if (cmp > 0)
			return (cmp);
		if (cmp && curent->command == NULL && ft_strncmp(lexer[i], "\"\"", 2))
		{
			curent->command = ft_strdup(lexer[i]);
			if (curent->command == NULL)
				return (1);
		}
		else if (cmp && ft_strncmp(lexer[i], "|", 2))
			if (new_arg(&curent->arg, lexer[i]))
				return (1);
	}
	return (error_redir(curent));
}

int	parser(t_local *local, char *lexer)
{
	char	**tmp;
	int		err;

	err = 0;
	if (check_quote(lexer))
		ft_putendl_fd("minishell : syntax error unresolved quote", 2);
	if (check_quote(lexer))
		return (1);
	lexer = swap_env_var(local, lexer);
	if (!lexer)
		return (1);
	tmp = arg_sep(lexer);
	free(lexer);
	if (tmp == NULL)
		return (1);
	local->data = new_data();
	if (!local->data)
		return (1);
	err = switch_elem(tmp, local->data, -1, -1);
	freetab(tmp);
	if (err)
		clear_data(local->data);
	if (err)
		return (err);
	return (0);
}

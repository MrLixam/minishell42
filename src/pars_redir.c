/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:39:40 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/28 17:10:46 by lvincent         ###   ########.fr       */
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

static int	redir_size(char *lexer)
{
	int	i;

	i = 0;
	if (lexer[i] == '<')
	{
		while (lexer[i] == '<')
			i++;
		if (i > 2)
			ft_putendl_fd("minishell: syntax error near unexpected token `<'",
				2);
	}
	else if (lexer[i] == '>')
	{
		while (lexer[i] == '>')
			i++;
		if (i > 2)
			ft_putendl_fd("minishell: syntax error near unexpected token `>'",
				2);
	}
	if (i > 2)
		return (-1);
	return (i);
}

int	redirection(char *lexer, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (lexer[i])
	{
		j = i;
		if (!ft_strncmp(lexer, "<>", 2) || !ft_strncmp(lexer, "><", 2))
			return (1);
		i += redir_size(lexer);
		if (i < 0)
			return (2);
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

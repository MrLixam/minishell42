/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:39:40 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/24 13:40:51 by gpouzet          ###   ########.fr       */
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

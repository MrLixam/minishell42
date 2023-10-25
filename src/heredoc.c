/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:11:43 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/25 10:42:38 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list *new_here(char *word)
{
	int		i;
	char	*str;
	t_list	*new;

	i = 1;
	new = NULL;
	while (i)
	{
		str = readline("> ");
		if (!str)
		{
			ft_printf("error msg");
			break;
		}
		if (!ft_strncmp(word, str, ft_strlen(word) + 1))
			i = 0;
		if (i)
			if (new_arg(&new, str))
				return (NULL);
	}
	return (new);
}

static void	showdoc(t_list	*doc)
{
	t_list	*tmp;
	t_list	*bigtmp;

	bigtmp = doc;
	while (bigtmp)
	{
		tmp = bigtmp->content;
		while (tmp)
		{
			ft_printf("%s\n", tmp->content);
			tmp = tmp->next;
		}
		bigtmp = bigtmp->next;
	}
}

int	heredoc(t_data *curent)
{
	t_list	*tmp;
	char	*move;

	tmp = curent->input ;
	while (tmp)
	{
		if (!ft_strncmp("<<", tmp->content, 3))
		{
			tmp = tmp->next;
			move = ft_strdup(tmp->content);
			if (!move)
				return (1);
			if (tmp)
				ft_lstadd_back(&curent->doc, ft_lstnew(new_here((move))));
			free(move);
		}
		tmp = tmp->next;
		showdoc(curent->doc);
	}
	return (0);
}

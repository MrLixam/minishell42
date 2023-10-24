/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:11:43 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/24 17:26:54 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_doc	*new_doc(t_list *start)
{
	t_doc	*new;

	new = (t_doc *)ft_calloc(1, sizeof(t_doc));
	if (!new)
		return (0);
	new->here = start;
	new->next = NULL;
	return (new);
}

static t_doc	*last_doc(t_doc *doc)
{
	if (doc == NULL)
		return (0);
	while (doc->next != NULL)
		doc = doc->next;
	return (doc);
}

static void	add_doc(t_doc **doc, t_doc *new)
{
	t_doc	*tmp;

	if (*doc == NULL)
		*doc = new;
	else
	{
		tmp = last_doc(*doc);
		tmp->next = new;
	}
}

static t_list *new_here(char *word)
{
	int		i;
	char	*str;
	t_list	*new;

	i = 1;
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
		if (new_arg(&new, str))
			return (NULL);
	}
	return (new);
}

int	heredoc(t_data *curent)
{
	t_list	*tmp;

	tmp = curent->input ;
	while (tmp)
	{
		if (!ft_strncmp("<<", tmp->content, 3))
		{
			tmp = tmp->next;
			if (tmp)
				add_doc(&curent->doc, new_doc(new_here(tmp->content)));
		}
		tmp = tmp->next;
	}
	return (0);
}

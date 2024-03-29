/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:26:14 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/28 15:43:01 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *readline)
{
	int	one;
	int	two;
	int	i;

	i = -1;
	one = 1;
	two = 1;
	while (readline[++i])
	{
		if (readline[i] == 39 && two > 0)
			one *= -1;
		else if (readline[i] == 34 && one > 0)
			two *= -1;
	}
	if (one < 0 || two < 0)
		return (1);
	return (0);
}

int	ft_strmcmp(char *s1, char *s2)
{
	int	len[2];

	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	if (len[0] > len[1])
		return (ft_strncmp(s1, s2, len[0]));
	return (ft_strncmp(s1, s2, len[1]));
}

void	fix_fd(int save[2])
{
	dup2(save[0], 0);
	dup2(save[1], 1);
	close(save[0]);
	close(save[1]);
}

int	is_last(t_list *redir, int mode)
{
	t_list	*tmp;

	tmp = redir;
	if (mode)
	{
		while (tmp)
		{
			if (!ft_strmcmp(tmp->content, ">")
				|| !ft_strmcmp(tmp->content, ">>"))
				return (0);
			tmp = tmp->next;
		}
		return (1);
	}
	else
	{
		while (tmp)
		{
			if (!ft_strmcmp(tmp->content, "<")
				|| !ft_strmcmp(tmp->content, "<<"))
				return (0);
			tmp = tmp->next;
		}
		return (1);
	}
}

void	clear_heredoc(t_local *local)
{
	t_list	*tmp;
	t_data	*curr;

	curr = local->data;
	if (!curr)
		return ;
	while (curr)
	{
		tmp = curr->redir;
		if (tmp != NULL)
		{
			while (tmp)
			{
				if (!ft_strmcmp(tmp->content, "<<"))
				{
					tmp = tmp->next;
					unlink(tmp->content);
				}
				tmp = tmp->next;
			}
		}
		curr = curr->next;
	}
}

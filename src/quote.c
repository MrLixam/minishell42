/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r <marvin@42.fr>                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:48:12 by r                 #+#    #+#             */
/*   Updated: 2023/10/30 18:11:30 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	nb_of_quote(char *src)
{
	int	s_quote;
	int	d_quote;
	int	ret;
	int	i;

	i = -1;
	ret = 0;
	s_quote = 1;
	d_quote = 1;
	while (src[++i])
	{
		if (src[i] == 39 && d_quote > 0)
		{
			ret++;
			s_quote *= -1;
		}
		else if (src[i] == 34 && s_quote > 0)
		{
			ret++;
			d_quote *= -1;
		}
	}
	return (ret);
}

char	*add_quote(char *src, int s_quote, int d_quote, int j)
{
	char	*dest;
	int		i;

	i = -1;
	dest = ft_calloc(ft_strlen(src) + 1 + nb_of_quote(src), 1);
	if (!dest)
		return (NULL);
	while (src[++i])
	{
		if (src[i] == 39 && d_quote > 0 && s_quote > 0)
			dest[j++] = 34;
		else if (src[i] == 34 && s_quote > 0 && d_quote > 0)
			dest[j++] = 39;
		dest[j++] = src[i];
		if (src[i] == 39 && d_quote > 0 && s_quote < 0)
			dest[j++] = 34;
		else if (src[i] == 34 && s_quote > 0 && d_quote < 0)
			dest[j++] = 39;
		if (src[i] == 39 && d_quote > 0)
			s_quote *= -1;
		else if (src[i] == 34 && s_quote > 0)
			d_quote *= -1;
	}
	free(src);
	return (dest);
}

static int	remove_quote(t_list	*src, int s_quote, int d_quote)
{
	char	*tmp;
	char	*dest;
	int		i;
	int		j;

	i = -1;
	j = 0;
	tmp = (char *)src->content;
	dest = ft_calloc(ft_strlen(tmp) + 1 - nb_of_quote(tmp), 1);
	if (!dest)
		return (1);
	while (tmp[++i])
	{
		if (tmp[i] == 39 && d_quote > 0)
			s_quote *= -1;
		else if (tmp[i] == 34 && s_quote > 0)
			d_quote *= -1;
		else
			dest[j++] = tmp[i];
	}
	free(src->content);
	src->content = dest;
	return (0);
}

static char	*remove_quote_arg(char *src, int s_quote, int d_quote)
{
	char	*dest;
	int		i;
	int		j;

	i = -1;
	j = 0;
	dest = ft_calloc(ft_strlen(src) + 1 - nb_of_quote(src), 1);
	if (!dest)
		return (NULL);
	while (src[++i])
	{
		if (src[i] == 39 && d_quote > 0)
			s_quote *= -1;
		else if (src[i] == 34 && s_quote > 0)
			d_quote *= -1;
		else
			dest[j++] = src[i];
	}
	free(src);
	return (dest);
}

int	format_quote(t_data *current)
{
	t_list	*tmp;

	tmp = current->arg;
	while (tmp)
	{
		if (ft_strrchr(tmp->content, 39) || ft_strrchr(tmp->content, 34))
			if (remove_quote(tmp, 1, 1))
				return (1);
		tmp = tmp->next;
	}
	tmp = current->redir;
	while (tmp)
	{
		if (ft_strrchr(tmp->content, 39) || ft_strrchr(tmp->content, 34))
			if (remove_quote(tmp, 1, 1))
				return (1);
		tmp = tmp->next;
	}
	if (current->command)
	{
		current->command = remove_quote_arg(current->command, 1, 1);
		if (!current->command)
			return (1);
	}
	return (0);
}

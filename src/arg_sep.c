/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_sep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:12:58 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/26 16:47:56 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/libft.h"

static int	wspac(char c)
{
	if ((c >= '\t' && c <= '\r') || c == 32)
		return (1);
	return (0);
}

static int	cut(char const *s)
{
	int	i;
	int	nb_arg;
	int	s_quote;
	int	d_quote;

	i = -1;
	nb_arg = 1;
	s_quote = 1;
	d_quote = 1;
	if (!*s)
		return (0);
	while (s[++i])
	{
		if (s[i] == 39 && d_quote > 0)
			s_quote *= -1;
		else if (s[i] == 34 && s_quote > 0)
			d_quote *= -1;
		if (i > 0 && wspac(s[i]) && !wspac(s[i - 1]) && (s_quote + d_quote) > 0)
			nb_arg++;
		if (s[i] == '|' && (s_quote + d_quote) > 0)
			nb_arg += 2;
	}
	if (wspac(s[ft_strlen(s) - 1]))
		nb_arg--;
	return (nb_arg);
}

static int	next_arg(char const *s)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = -1;
	s_quote = 1;
	d_quote = 1;
	if (s[i + 1] == '|')
		return (1);
	while (s[++i])
	{
		if (s[i] == 39 && d_quote > 0)
			s_quote *= -1;
		else if (s[i] == 34 && s_quote > 0)
			d_quote *= -1;
		if ((wspac(s[i]) || s[i] == '|') && s_quote > 0 && d_quote > 0)
			return (i);
	}
	return (i);
}

char	**arg_sep(char const *s)
{
	char	**args;
	int		next;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	args = ft_calloc(cut(s) + 1, sizeof(char *));
	if (!args)
		return (args);
	while (s[i] && s)
	{
		while (s[i] && wspac(s[i]))
			i++;
		next = next_arg(s + i);
		if (s[i] || wspac(s[i - 1]))
			args[j++] = ft_substr(s + i, 0, next);
		i += next + (wspac(s[i + next]));
	}
	args[j] = 0;
	return (args);
}

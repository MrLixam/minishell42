/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:52:19 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/25 22:12:38 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cut(char const *s, int s_quote, int d_quote)
{
	int	i;
	int	nb_arg;

	i = -1;
	nb_arg = 1;
	if (!*s)
		return (0);
	while (s[++i])
	{
		if (s[i] == 39 && d_quote > 0)
			s_quote *= -1;
		else if (s[i] == 34 && s_quote > 0)
			d_quote *= -1;
		if (s[i] == '$' && s_quote > 0)
		{
			nb_arg++;
			if (s[i + 1] != '?')
			{
				while (s[i + 1] && (!ft_isalnum(s[i + 1]) || s[i + 1] == '_'))
					i++;
				nb_arg++;
			}
		}
	}
	nb_arg++;
	return (nb_arg);
}

static int	next_arg(char const *s)
{
	static int	s_quote = 1;
	static int	d_quote = 1;
	int			i;

	i = 0;
	if (s[i] == '$')
	{
		i++;
		if (s[i] == '?')
			return (++i);
		while (ft_isalnum(s[i]) || s[i] == '_')
			i++;
	}
	else
	{
		while (s[i] && (s[i] != '$' || s_quote < 0))
		{
			if (s[i] == 39 && d_quote > 0)
				s_quote *= -1;
			else if (s[i] == 34 && s_quote > 0)
				d_quote *= -1;
			i++;
		}
	}
	return (i);
}

char	**env_sep(char const *s)
{
	char	**args;
	int		next;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	args = ft_calloc(cut(s, 1, 1) + 1, sizeof(char *));
	if (!args)
		return (args);
	while (s[i] && s)
	{
		next = next_arg(s + i);
		args[j++] = ft_substr(s + i, 0, next);
		i += next;
	}
	args[j] = 0;
	return (args);
}

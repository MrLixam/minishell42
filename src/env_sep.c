/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <gpouzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:52:19 by gpouzet           #+#    #+#             */
/*   Updated: 2023/09/14 20:51:50 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/libft.h"

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
		if (i > 0 && s[i] == '$' && s_quote > 0)
		{
			nb_arg++;
			if (s[i + 1] && s[i + 1] == '$')
				i++;
			while (s[++i])
		}
	}
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
	while (s[++i])
	{
		if (s[i] == 39 && d_quote > 0)
			s_quote *= -1;
		else if (s[i] == 34 && s_quote > 0)
			d_quote *= -1;
		if (s[i] == 32 && s_quote > 0 && d_quote > 0)
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
		while (s[i] == 32 && s[i])
			i++;
		next = next_arg(s + i);
		if (s[i] || s[i - 1] == 32)
			args[j++] = ft_substr(s + i, 0, next);
		i += next + (s[i + next] == 32);
	}
	args[j] = 0;
	return (args);
}

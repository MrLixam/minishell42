/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:53:34 by gpouzet           #+#    #+#             */
/*   Updated: 2023/04/14 12:59:25 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

static int	cut(char const *s, char c)
{
	int	ct;
	int	i;

	i = 0;
	ct = 1;
	if (!*s)
		return (0);
	while (s[++i])
		if (s[i] == c && s[i - 1] != c)
			ct++;
	if (s[ft_strlen(s) - 1] == c)
		ct--;
	return (ct);
}

static char	*wordcutter(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (ft_substr(s, 0, i));
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		cuts;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	cuts = cut(s, c);
	split = ft_calloc(cuts + 1, sizeof(char *));
	if (!split)
		return (split);
	while (cuts-- && s[i] && s)
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] || s[i - 1] == c)
			split[j++] = wordcutter(s + i, c);
		while (s[i] != c && s[i])
			i++;
	}
	split[j] = 0;
	return (split);
}

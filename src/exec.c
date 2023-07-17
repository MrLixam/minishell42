/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:55 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/17 20:29:50 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t			size;
	unsigned int	i;
	char			*new;

	if (ft_strlen(s) > n)
		size = n + 1;
	else
		size = ft_strlen(s) + 1;
	i = 0;
	new = malloc(size);
	if (!new)
		return (new);
	while (s[i] && i < n)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_strli(char *s, char c)
{
	int i;

	i = ft_strlen(s);
	while (--i)
		if (s[i] == c)
			return (i);
	return (-1);
}

int	exec(char *arg, char **envp)
{
	int fd;
	fd = open(arg[0]);
	if (fd == -1)
		return (-1);
	close(fd);
	return (1);
}

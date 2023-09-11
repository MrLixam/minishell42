/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:55 by lvincent          #+#    #+#             */
/*   Updated: 2023/09/09 14:50:22 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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
}*/

int	exec_bin(char *bin, char **args, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(bin, args, envp);
		exit(0);
	}
	else if (pid < 0)
		return (1);
	else
		waitpid(pid, NULL, 0);
	return (0);
}

int	file_access(char *path)
{
	int i;

	i = access(path, F_OK & R_OK & W_OK & X_OK);
	if (i == 0)
		return (0);
	else
		return (1);
}


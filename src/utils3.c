/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:26:14 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/25 08:23:00 by marvin           ###   ########.fr       */
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

char	*ft_strmerge(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
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

void	path_error(char *filename)
{
	char	*err;

	err = ft_strjoin(filename, ": command not found\n");
	write(2, err, ft_strlen(err));
	free(err);
}

void	fix_fd(int save[2])
{
	dup2(save[0], STDIN_FILENO);
	dup2(save[1], STDOUT_FILENO);
	close(save[0]);
	close(save[1]);
}

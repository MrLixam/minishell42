/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:11:43 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/25 13:01:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_input(int fd, char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			free(line);
			continue ;
		}
		if (!ft_strmcmp(line, delim))
		{
			free(line);
			break ;
		}
		line = ft_strmerge(line, ft_strdup("\n"));
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

static int	create_heredoc_file(char *delim, t_list *curr)
{
	int		fd;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin("/tmp/.heredoc", ft_itoa(i));
	while (!access(tmp, F_OK))
	{
		free(tmp);
		tmp = ft_strjoin("/tmp/.heredoc", ft_itoa(++i));
	}
	fd = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(curr->content);
	curr->content = tmp;
	if (fd == -1)
	{
		perror("minishell : error while parsing heredoc");
		return (1);
	}
	get_input(fd, delim);
	close(fd);
	return (0);
}

int	parse_heredoc(t_data **line)
{
	t_list	*curr;
	t_data	*local;
	char	*delim;
	int		i;

	local = *line;
	while (local)
	{
		curr = local->input;
		while (curr)
		{
			if (ft_strncmp(curr->content, "<<", 2) == 0)
			{
				curr = curr->next;
				delim = ft_strdup(curr->content);
				i = create_heredoc_file(delim, curr);
				free(delim);
				if (i)
					return (1);
			}
			curr = curr->next;
		}
		local = local->next;
	}
	return (0);
}

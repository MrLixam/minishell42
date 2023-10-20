/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:05:22 by marvin            #+#    #+#             */
/*   Updated: 2023/10/17 12:05:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	redir_in(t_data *command, int in)
{
	t_list	*input;
	int		i;

	input = command->input;
	if (!input)
		return (in);
	i = 0;
	while (input->next)
	{
		if (i % 2 != 0 && file_access(input->content))
			return (perror_filename("minishell : ", input->content));
		input = input->next;
		i++;
	}
	if (!file_access(input->content))
		return (open(input->content, O_RDONLY));
	return (perror_filename("minishell : ", input->content));
}

static int	outfile_logic(int *fd, int *i, t_list **output, char **tmp)
{
	if (*i % 2 != 0)
	{
		if (ft_strlen(*tmp) == 1)
			*fd = open((*output)->content, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else
			*fd = open((*output)->content, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (*fd == -1)
			return (1);
		if ((*output)->next)
			close(*fd);
	}
	else
	{
		free(*tmp);
		*tmp = ft_strdup((*output)->content);
	}
	*output = (*output)->next;
	(*i)++;
	return (0);
}

static int	redir_out(t_data *command, int out)
{
	t_list	*output;
	int		i;
	int		fd;
	char	*tmp;

	output = command->output;
	if (!output)
		return (out);
	i = 1;
	tmp = ft_strdup(output->content);
	output = output->next;
	while (output)
	{
		if (outfile_logic(&fd, &i, &output, &tmp))
			return (perror_filename("minishell : ", output->content));
	}
	free(tmp);
	return (fd);
}

void	redirect(int in, int out, t_data *curr, int redir[2])
{
	redir[0] = redir_in(curr, in);
	redir[1] = redir_out(curr, out);
}

void	link_redir(int pipes[2], int fd, t_data *curr, t_local *local)
{
	int	redir[2];

	redirect(fd, pipes[1], curr, redir);
	if (redir[0] == -1 || redir[1] == -1)
		clean_child(local, curr, pipes, fd);
	if (curr != local->data && curr->next != NULL)
	{
		dup2(redir[0], STDIN_FILENO);
		dup2(redir[1], STDOUT_FILENO);
		close(redir[0]);
		close_pipe(pipes);
	}
	else if (curr == local->data)
	{
		dup2(redir[1], STDOUT_FILENO);
		close(redir[1]);
		close(pipes[0]);
	}
	else if (curr->next == NULL)
	{
		dup2(redir[0], STDIN_FILENO);
		close(redir[0]);
	}
}

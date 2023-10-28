/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:56:48 by marvin            #+#    #+#             */
/*   Updated: 2023/10/24 18:56:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_parent(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = sig;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_child(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit\n");
	}
}

void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		if (*getfd() != -1)
			close(*getfd());
		exit(130);
	}
}

void	check_sig(t_local *local)
{
	if (g_sig == SIGINT)
	{
		g_sig = 0;
		if (!WIFSIGNALED(local->exit_code))
			local->exit_code = 130;
	}
	if (g_sig == SIGQUIT)
	{
		g_sig = 0;
		if (!WIFSIGNALED(local->exit_code))
			local->exit_code = 131;
	}
}

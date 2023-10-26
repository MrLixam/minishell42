/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:03:11 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/26 12:07:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>

static void	init_local(t_local *local, char **envp)
{
	local->child_pid = NULL;
	local->env = NULL;
	local->exit_code = 0;
	create_env(local, envp);
}

int	clear_local(t_local	*local, int exit_code)
{
	if (local->env)
		freetab(local->env);
	clear_data(local->data);
	if (local->child_pid)
		free(local->child_pid);
	free(local);
	return (exit_code);
}

void	minishell_loop(t_local *local)
{
	char	*str;

	while (1)
	{
		signal(SIGINT, sig_parent);
		signal(SIGQUIT, SIG_IGN);
		str = readline("minishell$ ");
		if (str == NULL)
			exit(clear_local(local, 1));
		if (ft_strncmp(str, "\0", 2))
			add_history(str);
		if (parser(local, str))
			exit(clear_local(local, 1));
		if (local->data == NULL)
			exit(clear_local(local, 1));
		if ( local->data->command != NULL && *local->data->command != '\0')
			exec(local);
		clear_data(local->data);
		local->child_pid = NULL;
		str = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_local	*local;

	local = ft_calloc(1, sizeof(t_local));
	if (!local)
		return (1);
	init_local(local, envp);
	(void) argc;
	(void) argv;
	minishell_loop(local);
	return (0);
}

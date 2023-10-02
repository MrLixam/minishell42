/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:59:09 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/02 17:09:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "../libft/printf.h"
# include "../libft/list.h"
# include "../libft/get_next_line.h"

/*			global			*/
char	**g_env;
t_list	*g_env2;

/*			struct			*/

typedef struct s_data
{
	char	*command;
	t_list	*redirection;
	t_list	*input;
	t_list	*output;
	t_list	*arg;
	struct	s_data	*next;
}	t_data;

typedef struct s_group
{
	int	*child_pid;
	t_data **line;
}	t_group;

/*			prototype		*/
void	freetab(char **tab);
int		ft_strmcmp(char *s1, char *s2);
char	*ft_getenv(char *name);

/*			data			*/
t_data	*new_data(void);
int		data_len(t_data *line);
void	freetab(char **tab);
void	clear_data(t_data *data);

/*			parser			*/
int		swap_env_var(char **lex);
int		check_quote(char *readline);
char	**pre_parser(char *lexer);
char	**arg_sep(char const *s);
char	**env_sep(char const *s);
t_data	*parser(char **lexer);

/*			exec			*/
void	pipeline(t_group *group);

/*			builtins		*/
int		ft_pwd(void);
int		ft_cd(char *arg, char **envp);
int		ft_echo(char **arg);

#endif

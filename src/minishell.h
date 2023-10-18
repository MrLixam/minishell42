/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:59:09 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/18 16:17:34 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "../libft/printf.h"
# include "../libft/list.h"
# include "../libft/get_next_line.h"

/*			global			*/
extern char		**g_env;
extern int		g_exit;
/*			struct			*/

typedef struct s_local
{
	char			**env;
	struct s_data	*data;
}	t_local;

typedef struct s_data
{
	char			*command;
	t_list			*redirection;
	t_list			*input;
	t_list			*output;
	t_list			*arg;
	struct s_data	*next;
}	t_data;

typedef struct s_group
{
	int		*child_pid;
	t_data	**line;
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
int		new_arg(t_list **lst, char *arg);

/*			parser			*/
int		swap_env_var(char **lex);
int		check_quote(char *readline);
char	**pre_parser(char *lexer);
char	**arg_sep(char const *s);
char	**env_sep(char const *s);
t_data	*switch_elem(char **lexer);
char	*ft_strmerge(char *s1, char *s2);

/*			exec			*/
void	exec(t_data *line);

/*			builtins		*/
int		ft_pwd(void);
int		ft_cd(char **arg);
int		ft_echo(t_list *arg);
int		ft_export(char **arg);
int		ft_unset(char **arg);
void	ft_exit(t_data *line);

/*			env_modif		*/
char	*ft_getenv(char *name);
int		create_env(char **env, char **envp);
int		unset_env(char *unset);
int		export_env(char *env);
int		print_env(char **arg);

/*			error			*/
int		perror_filename(char *command, char *filename);
int		ft_error(char *message, t_group *group);

/*			execution		*/
void	link_redir(int pipes[2], int fd, t_data *curr, t_group *group);
int		is_builtin(char *command);
int		file_access(char *path);
char	**lst_to_str(t_list *lst, char *command);
int		redir_present(t_data *command);
int		exec_builtin(char **str, t_data *line);
int		fix_path(t_data **line);
void	clean_child(t_group *group, t_data *curr, int pipes[2], int fd);
void	close_pipe(int pipes[2]);
void	redirect(int in, int out, t_data *curr, int redir[2]);
int		pipeline(t_group *group);

#endif

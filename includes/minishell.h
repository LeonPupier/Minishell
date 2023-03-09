/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:31:00 by lpupier           #+#    #+#             */
/*   Updated: 2023/03/09 14:24:20 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Define
#ifndef MINISHELL_H
# define MINISHELL_H

// Librairies
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

// Headers
# include "../libft/libft.h"

// Env structure
typedef struct s_env
{
	char	**envp;
	t_list	*new_envp;
}	t_env;

// Parsing structure
typedef struct s_parsing
{
	char	**envp;
	int		idx;
	int		idx_init;
	char	c;
}	t_parsing;

// main.c

int		main(int argc, char **argv, char **envp);
char	*init_minishell(int argc, char **argv, char **envp);
int		loop_main(char *prompt, t_env *env);

// commands.c

int		check_functions(char **cmd, t_env *envi, int status);
int		check_builtins(char **cmd, t_env *envi);

// utils.c

pid_t	binary(const char *program, char **args, char **envp);
int		is_in_envp(char **envp, char *request);
char	*get_env(char **envp, char *request);
char	*get_binary_path(char *cmd, char **envp);

// ft_tab.c

void	free_tab(char **tab);
void	free_2tab(char ***tab);
int		get_array_size(char **envp);
char	*get_binary_path(char *cmd, char **envp);
char	**add_to_tab(char **tab, char *elt);

// get_variable.c

char	*get_var(char *str, char **envp);
int		replace_var(char **envp, char **cmd, int idx, int new_idx);

// parsing.c

char	**cmd_parsing(char **cmd, char *prompt, char **envp);

// quotes.c

int		parse_quotes(char ***cmd, char *str, t_parsing *parsing);
char	*removing_quotes(char *str);
char	*str_without_quote(char *str, char *new_str);

// signals.c

void	signal_ctrl_c(int id);
void	signal_ctrl_backslash(int id);

// ft_echo.c

void	echo(char **cmd);

// ft_pwd.c

void	pwd(char **cmd, char **envp);

// ft_env.c

void	env(char **cmd, char **envp);
void	sort_envp(t_list *start);
t_list	*envp_to_list(char **envp);

// ft_export.c

void	ft_export(char **cmd, t_list *new_envp);
char	*remove_plus(char *str);

// list_utils.c

t_list	*ft_create_elem(void *data);
int		ft_list_contains(t_list *begin_list, void *data_ref, int search);
void	ft_list_push_back(t_list **begin_list, void *data);
t_list	*ft_list_find(t_list *begin_list, void *data_ref, int search);
void	swap_nodes(t_list *a, t_list *b);
char	**list_to_envp(t_list *list);

// ft_unset.c

void	ft_lstdelone(t_list **head_lst, char *data_ref);
void	ft_unset(char **cmd, t_list *new_envp);

// ft_check_export.c

int		check_export_error(char **cmd, int argc);
void	print_export(t_list *new_envp);
void	treat_export(char **cmd, t_list *new_envp, int argc);

// ft_cd.c

void	cd(char **cmd, t_list *new_envp, char **envp);

// pipe_utils.c

int		count_pipe(char ***cmd_tab);
int		check_redirections(char **cmd);
int		get_index_redirection(char **cmd);
void	make_redirections(char **cmd);

// ft_pipe.c

int		ft_pipe(char ***cmd_tab, t_env *env);
int		exec_cmd(int *prev_fd, int *next_fd, char **cmd, t_env *env);

// decoration.c

void	minishell_header(void);

// redirections_utils.c

int		get_infiles_index(char **cmd);
int		check_infiles(char **cmd);
void	handle_infiles(char **cmd, t_env *env, int status);
void	handle_heredoc(char **cmd, int status);

#endif
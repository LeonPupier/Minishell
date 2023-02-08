/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:31:00 by lpupier           #+#    #+#             */
/*   Updated: 2023/02/08 20:27:40 by vcart            ###   ########.fr       */
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
# include <readline/history.h>
# include <readline/readline.h>


// Headers
# include "../libft/libft.h"
# include "../pipex/includes/pipex.h"

// main.c

pid_t	binary(const char *program, char **args, char **envp);
int		main(int argc, char **argv, char **envp);

// utils.c

char	*get_env(char **envp, char *request);
char	*get_binary_path(char *cmd, char **envp);

// ft_tab.c

void	free_tab(char **tab);
int		get_array_size(char **envp);
char	*get_binary_path(char *cmd, char **envp);
char	**add_to_tab(char **tab, char *elt);

// verify_args.c

char	**find_occurrence(char **cmd, char *prompt, char c);
void	retrieve_environment_variables(char **new_cmd, char **envp);

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

void	ft_unset(char **cmd, t_list *new_envp);

// ft_check_export.c

int		check_export_error(char **cmd, int argc);
void	print_export(t_list *new_envp);
void	treat_export(char **cmd, t_list *new_envp, int argc);

// ft_cd.c

void	cd(char **cmd, t_list *new_envp, char **envp);

#endif
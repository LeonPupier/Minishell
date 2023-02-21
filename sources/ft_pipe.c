/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart < vcart@student.42lyon.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:16:45 by vcart             #+#    #+#             */
/*   Updated: 2023/02/21 15:28:20 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Ferme les deux extrémités du pipe
void close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

// Modifie les deux valeurs d'un tableau de deux entiers
void change_fd(int *fd, int value1, int value2)
{
	fd[0] = value1;
	fd[1] = value2;
}

// Exécute une commande en redirigeant l'entrée et/ou la sortie
int exec_cmd(int *prev_fd, int *next_fd, char **cmd, char **envp, t_list *new_envp)
{
	if (prev_fd != NULL)
	{
		dup2(prev_fd[0], STDIN_FILENO);
		close(prev_fd[0]);
		close(prev_fd[1]);
	}
	if (next_fd != NULL)
	{
		close(next_fd[0]);
		dup2(next_fd[1], STDOUT_FILENO);
		close(next_fd[1]);
	}
	check_functions(cmd, envp, new_envp); // Exécute la commande
	return (0);
}

// Gère l'exécution de toutes les commandes avec les pipes
int handle_pipe(int num_pipes, int *prev_fd, int *curr_fd, char ***cmd_tab, char **envp, t_list *new_envp)
{
	int i;
	int pid;
	
	i = 0;
	while (i < num_pipes)
	{
		if (i < num_pipes - 1)
		{
			if (pipe(curr_fd) == -1)
				return (-1);
		}
		else
			change_fd(curr_fd, -1, -1);
		pid = fork(); // Crée un nouveau processus pour exécuter la commande
		if (pid < 0)
			return (-2);
		if (pid == 0) // Si on est dans le processus fils
		{
			exec_cmd(prev_fd, curr_fd, cmd_tab[i], envp, new_envp); // Exécute la commande
			exit(0); // Termine le processus fils
		}
		if (prev_fd[0] != STDIN_FILENO) // Ferme les extrémités du pipe du processus précédent s'il y en a un
			close_pipe(prev_fd);
		change_fd(prev_fd, curr_fd[0], curr_fd[1]);
		i++;
	}
	return (0);
}

// Fonction principale pour l'exécution des commandes avec des pipes
int ft_pipe(char ***cmd_tab, char **envp, t_list *new_envp)
{
	int num_pipes;
	int i;
	int prev_fd[2];
	int curr_fd[2];
	
	num_pipes = 0;
	prev_fd[0] = STDIN_FILENO;
	prev_fd[1] = STDOUT_FILENO;
	while (cmd_tab[num_pipes] != NULL)
		num_pipes++;
	handle_pipe(num_pipes, prev_fd, curr_fd, cmd_tab, envp, new_envp); 
	close_pipe(prev_fd);
	i = 0;
	while (i < num_pipes)
	{
		wait(NULL);
		i++;
	}
	return (0);
}

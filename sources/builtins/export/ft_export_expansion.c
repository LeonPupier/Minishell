/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:59:55 by vcart             #+#    #+#             */
/*   Updated: 2023/03/20 15:17:59 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_export_equals(t_list *new_envp)
{
	int		i;
	char	*elt;

	i = 0;
	elt = (char *)new_envp->content;
	printf("declare -x ");
	while (elt[i] != '=')
	{
		printf("%c", elt[i]);
		i++;
	}
	printf("=\"%s\"\n", elt + i + 1);
}

int	check_prompt_error(char **cmd, char **cmd_split, int i)
{
	if (count_plus(cmd_split[0]) > 1)
	{
		printf("%s \e[31m: not a valid identifier\e[0m\n", cmd[i]);
		return (-1);
	}
	else if (check_forbidden_char(cmd_split[0]))
	{
		printf("%s \e[31m: not a valid identifier\e[0m\n", cmd[i]);
		return (-1);
	}
	else if (contains("0123456789", cmd_split[0][0]) || \
			contains(cmd_split[0], '-'))
	{
		printf("%s \e[31m: not a valid identifier\e[0m\n", cmd[i]);
		return (-1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:51 by lpupier           #+#    #+#             */
/*   Updated: 2023/03/26 15:32:32 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	idx;
	char	*new_s1;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	idx = 0;
	new_s1 = malloc(sizeof(char) * (len + 1));
	if (!new_s1)
		return (NULL);
	while (idx < len)
	{
		new_s1[idx] = s1[idx];
		idx++;
	}
	new_s1[idx] = '\0';
	return (new_s1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:50:00 by bboulmie          #+#    #+#             */
/*   Updated: 2025/03/02 16:05:02 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		diff;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
	{
		i = i + 1;
	}
	diff = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (diff);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:06:53 by bboulmie          #+#    #+#             */
/*   Updated: 2025/03/03 14:20:30 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getline(void)
{
	char	*buffer;
	char	c;
	int		i;
	int		ret;

	i = 0;
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	while (i < BUFFER_SIZE - 1)
	{
		ret = read(STDIN_FILENO, &c, 1);
		if (ret <= 0)
			break ;
		buffer[i++] = c;
		if (c == '\n')
			break ;
	}
	buffer[i] = '\0';
	if (i == 0 && ret <= 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

void	create_pipe(int *pipe_fd, t_pipex *p)
{
	wrapped(pipe(pipe_fd), STERROR, p);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	handle_intermediate(t_pipex *p, int i, int *prev_fd, int *pipe_fd)
{
	create_pipe(pipe_fd, p);
	create_process(p, i, prev_fd, pipe_fd);
	if (*prev_fd != p->fd_in && *prev_fd >= 0)
		wrapped(close(*prev_fd), STERROR, p);
	*prev_fd = pipe_fd[0];
}

void	handle_last_cmd(t_pipex *p, int i, int *prev_fd)
{
	create_process(p, i, prev_fd, NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:54:11 by bboulmie          #+#    #+#             */
/*   Updated: 2025/03/03 19:40:36 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	read_here_doc(int fd, char *limiter, t_pipex *p)
{
	char	*line;

	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		line = ft_getline();
		if (!line)
		{
			unlink(".here_doc_tmp");
			wrapped(close(fd), STERROR, NULL);
			cleanup(p);
			exit(0);
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

static int	open_here_doc_tmp(int flags, t_pipex *p)
{
	int	fd;

	fd = open(".here_doc_tmp", flags, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			print_error_msg(3, ".here_doc_tmp");
			cleanup(p);
			exit(1);
		}
		wrapped(fd, NO_FILE, p);
	}
	return (fd);
}

static int	here_doc(char *limiter, t_pipex	*p)
{
	int	fd;

	fd = open_here_doc_tmp(O_WRONLY | O_CREAT | O_TRUNC, p);
	read_here_doc(fd, limiter, p);
	wrapped(close(fd), STERROR, NULL);
	fd = open_here_doc_tmp(O_RDONLY, p);
	return (fd);
}

void	init_here_doc(t_pipex *p)
{
	p->fd_in = here_doc(p->argv[2], p);
	p->fd_out = open(p->argv[p->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (p->fd_out == -1)
	{
		if (errno == EACCES)
		{
			print_error_msg(3, p->argv[p->argc - 1]);
			close(p->fd_in);
			unlink(".here_doc_tmp");
			cleanup(p);
			exit(1);
		}
		else
			wrapped(p->fd_out, NO_PERM, p);
	}
	p->cmd_start = 3;
	p->hd_mode = 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:24:37 by bboulmie          #+#    #+#             */
/*   Updated: 2025/03/03 18:36:37 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_iteration(t_pipex *p, int i, int *prev_fd)
{
	int	pipe_fd[2];

	if (i < p->argc - 2)
		handle_intermediate(p, i, prev_fd, pipe_fd);
	else
		handle_last_cmd(p, i, prev_fd);
}

static void	process_commands(t_pipex *p)
{
	int	i;
	int	prev_fd;

	i = p->cmd_start;
	prev_fd = p->fd_in;
	while (i < p->argc - 1)
	{
		execute_iteration(p, i, &prev_fd);
		i++;
	}
	if (prev_fd != p->fd_in && prev_fd >= 0)
		wrapped(close(prev_fd), STERROR, p);
}

void	init_fds(t_pipex *p)
{
	p->in = malloc(sizeof(t_cmd));
	p->out = malloc(sizeof(t_cmd));
	if (!p->in || !p->out)
		error_exit(MALLOC, p);
	p->in->fd = -1;
	p->out->fd = -1;
	if (ft_strcmp(p->argv[1], "here_doc") == 0)
		init_here_doc(p);
	else
		init_normal(p);
}

int	pipex(t_pipex *p)
{
	int		last_exit_status;
	pid_t	pid;
	int		status;

	last_exit_status = 0;
	init_fds(p);
	process_commands(p);
	if (p->fd_in >= 0)
		wrapped(close(p->fd_in), STERROR, p);
	if (p->fd_out >= 0)
		wrapped(close(p->fd_out), STERROR, p);
	pid = wait(&status);
	while (pid != -1)
	{
		if (pid == p->out->pid && WIFEXITED(status))
			last_exit_status = WEXITSTATUS(status);
		pid = wait(&status);
	}
	if (p->hd_mode == 1)
		unlink(".here_doc_tmp");
	cleanup(p);
	if (p->fd_out == -1)
		return (1);
	return (last_exit_status);
}

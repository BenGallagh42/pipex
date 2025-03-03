/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:41:46 by bboulmie          #+#    #+#             */
/*   Updated: 2025/03/03 18:15:41 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_input_file(t_pipex *p)
{
	p->fd_in = open(p->argv[1], O_RDONLY);
	if (p->fd_in == -1)
	{
		if (errno == ENOENT)
		{
			print_error_msg(2, p->argv[1]);
			p->fd_in = open("/dev/null", O_RDONLY);
			if (p->fd_in == -1)
				error_exit(NO_FILE, p);
		}
		else if (errno == EACCES)
		{
			print_error_msg(3, p->argv[1]);
			p->fd_in = -1;
		}
	}
}

static void	handle_output_file(t_pipex *p)
{
	p->fd_out = open(p->argv[p->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->fd_out == -1)
	{
		if (errno == EACCES)
			print_error_msg(3, p->argv[p->argc - 1]);
		else if (errno == ENOENT)
			print_error_msg(2, p->argv[p->argc - 1]);
		else if (errno == EISDIR)
		{
			print_error_msg(4, p->argv[p->argc - 1]);
			if (p->in)
				free(p->in);
			if (p->out)
				free(p->out);
			exit (1);
		}
		p->fd_out = -1;
	}
}

void	init_normal(t_pipex *p)
{
	handle_output_file(p);
	handle_input_file(p);
	p->cmd_start = 2;
	p->hd_mode = 0;
}

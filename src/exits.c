/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:53:18 by bboulmie          #+#    #+#             */
/*   Updated: 2025/03/03 18:24:27 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error_msg(int err_type, char *arg)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	if (err_type <= 4)
		print_err_detail(err_type, arg);
	else
	{
		ft_putstr_fd("pipex: execution failed: ", STDERR_FILENO);
		print_err_detail(err_type, arg);
	}
}

void	handle_cmd_error(char **args, char *cmd_path, int err_type)
{
	print_error_msg(err_type, args[0]);
	free_tab(args);
	if (cmd_path)
		free(cmd_path);
	if (err_type == 3)
		exit(126);
	exit(127);
}

void	wrapped(int result, int code, t_pipex *p)
{
	if (result == -1)
		error_exit(code, p);
}

int	wait_processes(t_pipex *p)
{
	pid_t	pid;
	int		status;
	int		exitcode;

	exitcode = 0;
	pid = wait(&status);
	while (pid != -1)
	{
		if (WIFEXITED(status) && pid == p->out->pid)
			exitcode = WEXITSTATUS(status);
		pid = wait(&status);
	}
	return (exitcode);
}

void	error_exit(int err, t_pipex *p)
{
	if (p)
		cleanup(p);
	exit(err);
}

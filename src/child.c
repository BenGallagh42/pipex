/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:59:34 by bboulmie          #+#    #+#             */
/*   Updated: 2025/03/03 18:27:44 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_directory(char **args, char *cmd_path)
{
	int	fd;

	fd = open(cmd_path, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		free_tab(args);
		free(cmd_path);
		exit(126);
	}
}

static void	execute_command(char *cmd, char **envp, t_pipex *p)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args)
		error_exit(MALLOC, p);
	if (!args[0] || args[0][0] == '\0')
		handle_cmd_error(args, NULL, 1);
	cmd_path = get_command_path(args[0], envp);
	if (!cmd_path)
		check_pathless_cmd(args);
	if (access(cmd_path, X_OK) != 0)
		handle_cmd_error(args, cmd_path, 3);
	check_directory(args, cmd_path);
	execve(cmd_path, args, envp);
	handle_cmd_error(args, cmd_path, 0);
}

static void	child_process(int i_fd, int out_fd, char *cmd, t_pipex *p)
{
	if (dup2(i_fd, STDIN_FILENO) == -1 || dup2(out_fd, STDOUT_FILENO) == -1)
	{
		if (i_fd >= 0)
			close(i_fd);
		if (out_fd >= 0)
			close(out_fd);
		if (p->fd_in >= 0)
			close(p->fd_in);
		if (p->fd_out >= 0)
			close(p->fd_out);
		cleanup(p);
		exit(1);
	}
	if (i_fd != p->fd_in && i_fd >= 0)
		close(i_fd);
	if (out_fd != p->fd_out && out_fd >= 0)
		close(out_fd);
	if (p->fd_in >= 0)
		close(p->fd_in);
	if (p->fd_out >= 0)
		close(p->fd_out);
	cleanup(p);
	execute_command(cmd, p->envp, p);
	exit(1);
}

static void	manage_child(t_pipex *p, int i, int *prev_fd, int *pipe_fd)
{
	int	out_fd;

	if (i < p->argc - 2 && pipe_fd != NULL)
		out_fd = pipe_fd[1];
	else
		out_fd = p->fd_out;
	if (i < p->argc - 2 && pipe_fd != NULL && pipe_fd[0] >= 0)
		close(pipe_fd[0]);
	child_process(*prev_fd, out_fd, p->argv[i], p);
}

void	create_process(t_pipex *p, int i, int *prev_fd, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		cleanup(p);
		exit(1);
	}
	if (pid == 0)
		manage_child(p, i, prev_fd, pipe_fd);
	else
	{
		if (i == p->cmd_start)
			p->in->pid = pid;
		if (i == p->argc - 2)
			p->out->pid = pid;
		if (i < p->argc - 2 && pipe_fd != NULL)
			wrapped(close(pipe_fd[1]), STERROR, p);
	}
}

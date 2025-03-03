/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:29:39 by bboulmie          #+#    #+#             */
/*   Updated: 2025/03/03 19:46:56 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cleanup(t_pipex *p)
{
	if (p->in)
		free(p->in);
	if (p->out)
		free(p->out);
	p->in = NULL;
	p->out = NULL;
}

void	print_err_detail(int err_type, char *arg)
{
	if (err_type == 1)
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	else if (err_type == 2)
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else if (err_type == 3)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	else if (err_type == 4)
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	else
		ft_putendl_fd(arg, STDERR_FILENO);
}

static void	validate_args(int argc, char **argv)
{
	if (argc < 5 || (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6))
	{
		ft_putendl_fd("pipex: syntax error", STDERR_FILENO);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	validate_args(argc, argv);
	p.argc = argc;
	p.argv = argv;
	p.envp = envp;
	return (pipex(&p));
}

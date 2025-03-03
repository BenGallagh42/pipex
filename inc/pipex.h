/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:50:49 by bboulmie          #+#    #+#             */
/*   Updated: 2025/03/03 18:27:23 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

# define STERROR 1
# define MALLOC 2
# define NO_FILE 3
# define NO_PERM 4

# define BUFFER_SIZE 1024

# ifndef O_DIRECTORY
#  define O_DIRECTORY 0200000
# endif

typedef struct s_cmd
{
	pid_t	pid;
	int		fd;
}	t_cmd;

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	int		fd_in;
	int		fd_out;
	int		hd_mode;
	int		cmd_start;
	t_cmd	*in;
	t_cmd	*out;
}	t_pipex;

// Core Functions
int		pipex(t_pipex *p);
void	create_process(t_pipex *p, int i, int *prev_fd, int *pipe_fd);
void	init_here_doc(t_pipex *p);
void	init_normal(t_pipex *p);

// Error Handling
void	error_exit(int err, t_pipex *p);
void	wrapped(int result, int code, t_pipex *p);
int		wait_processes(t_pipex *p);
void	handle_cmd_error(char **args, char *cmd_path, int err_type);
void	print_error_msg(int err_type, char *arg);
void	print_err_detail(int err_type, char *arg);

// Utils
char	*get_command_path(char *cmd, char **envp);
void	check_pathless_cmd(char **args);
void	create_pipe(int *pipe_fd, t_pipex *p);
char	*ft_getline(void);
void	handle_intermediate(t_pipex *p, int i, int *prev_fd, int *pipe_fd);
void	handle_last_cmd(t_pipex *p, int i, int *prev_fd);

// Memory Management
void	free_tab(char **tab);
void	cleanup(t_pipex *p);

// Libft
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strchr(const char *s, int c);

#endif
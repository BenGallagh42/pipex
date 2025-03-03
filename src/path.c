/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:19:33 by bboulmie          #+#    #+#             */
/*   Updated: 2025/03/03 18:27:08 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_pathless_cmd(char **args)
{
	if (args[0][0] == '/' || ft_strchr(args[0], '/'))
	{
		if (access(args[0], F_OK) == 0 && access(args[0], X_OK) != 0)
			handle_cmd_error(args, NULL, 3);
		else
			handle_cmd_error(args, NULL, 2);
	}
	else
		handle_cmd_error(args, NULL, 1);
}

static char	*create_path(char *path, char *cmd)
{
	char	*tmp;

	tmp = malloc(ft_strlen(path) + ft_strlen(cmd) + 2);
	if (!tmp)
		return (NULL);
	ft_strcpy(tmp, path);
	ft_strcat(tmp, "/");
	ft_strcat(tmp, cmd);
	return (tmp);
}

static char	*search_cmd_in_paths(char *cmd, char **paths)
{
	char	*tmp;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		tmp = create_path(paths[i], cmd);
		if (!tmp)
			return (NULL);
		if (access(tmp, X_OK) == 0)
		{
			free_tab(paths);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

static char	*find_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = find_path_env(envp);
	if (!path_env)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = ft_split(path_env, ':');
	return (search_cmd_in_paths(cmd, paths));
}

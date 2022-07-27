/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoel <tgoel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 22:35:58 by tgoel             #+#    #+#             */
/*   Updated: 2022/06/18 10:38:02 by tgoel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	ft_real_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (!s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	execve_cmd(int *fdin, int *fdout, char *argv, t_ptrs *ptrs)
{
	char	*full_path;

	ptrs->command = ft_split(argv, ' ');
	if (!ptrs->command)
		handle_error(EXIT_FAILURE, ptrs);
	if (!ft_strchr(ptrs->command[0], '/'))
		ptrs->path = split_path(get_path(ptrs->envp) + 5, *(ptrs->command));
	else
		ptrs->path = ptrs->command;
	if (!ptrs->path)
		handle_error(EXIT_FAILURE, ptrs);
	close(fdin[1]);
	close(fdout[0]);
	if (dup2(fdin[0], STDIN_FILENO) == -1)
		handle_error(errno, ptrs);
	if (dup2(fdout[1], STDOUT_FILENO) == -1)
		handle_error(errno, ptrs);
	close(fdin[0]);
	close(fdout[1]);
	full_path = good_path(ptrs->path, ptrs);
	if (ft_real_strcmp(full_path, ACCESS_WRONG_PATH) == 0)
		handle_error(EXIT_FAILURE, ptrs);
	if (execve(full_path, ptrs->command, ptrs->envp) == -1)
		handle_error(errno, ptrs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoel <tgoel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 22:36:02 by tgoel             #+#    #+#             */
/*   Updated: 2022/06/18 10:55:12 by tgoel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	handle_error(int err, t_ptrs *ptrs)
{
	if (ptrs->command)
		ptrs->command = (char **)free_tab_v2((void **)ptrs->command);
	if (ptrs->path)
		ptrs->path = (char **)free_tab_v2((void **)ptrs->path);
	if (ptrs->fd)
	{
		close_all_fd(ptrs);
		ptrs->fd = (int **)free_tab_v2((void **)ptrs->fd);
	}
	if (ptrs->on_exit == 1)
		write(STDERR_FILENO, "pipex; another process exited\n",
			ft_strlen("pipex; another process exited") + 1);
	else
	{
		write(STDERR_FILENO, "\033[31;4;1mERROR\033[0m : [Pipex : ", 31);
		write(STDERR_FILENO, strerror(err), ft_strlen(strerror(err)));
		write(STDERR_FILENO, "]\n", 2);
	}
	exit(err);
}

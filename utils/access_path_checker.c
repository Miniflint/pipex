/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_path_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoel <tgoel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 22:43:03 by tgoel             #+#    #+#             */
/*   Updated: 2022/06/19 09:07:55 by tgoel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*good_path(char	**all_paths, t_ptrs *ptrs)
{
	int	i;

	i = 0;
	while (all_paths[i] && access(all_paths[i], X_OK) == -1)
		i++;
	if (!all_paths[i])
		handle_error(errno, ptrs);
	return (all_paths[i]);
}

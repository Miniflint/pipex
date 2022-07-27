/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoel <tgoel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 22:33:01 by tgoel             #+#    #+#             */
/*   Updated: 2022/06/18 08:08:09 by tgoel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	compt_path(char *s)
{
	int	j;

	j = 0;
	while (*s)
	{
		if (*s != ':' && (!*(s + 1) || *(s + 1) == ':'))
			j++;
		s++;
	}
	return (j);
}

char	*path_and_cmd(char *path, char *cmd)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc((ft_strlen_c(path, ':')
				+ ft_strlen_c(cmd, ':') + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	while (*path && *path != ':')
		ret[i++] = *(path++);
	ret[i++] = '/';
	while (*cmd && *cmd != ':')
		ret[i++] = *(cmd++);
	ret[i] = 0;
	return (ret);
}

char	**split_path(char *str, char *cmd)
{
	int		i;
	char	**strs;
	int		cmd_len;

	i = 0;
	cmd_len = ft_strlen(cmd);
	strs = malloc((compt_path(str) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (*str)
	{
		strs[i] = path_and_cmd(str, cmd);
		if (!strs[i])
			return ((char **)free_tab_v2((void **)strs));
		str += ft_strlen_c(str, ':');
		if (*str == ':')
			str++;
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

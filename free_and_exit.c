/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 23:27:22 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/06/21 14:49:37 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_arr_col(t_info_map **map)
{
	int	x;

	x = -1;
	if ((*map)->points)
		free((*map)->points);
	if ((*map)->title)
		free((*map)->title);
	if ((*map)->b_go)
		free((*map)->b_go);
	if ((*map)->arr)
	{
		while (++x < (*map)->height)
			free((*map)->arr[x]);
		free((*map)->arr);
	}
	x = -1;
	if ((*map)->col)
	{
		while (++x < (*map)->height)
			free((*map)->col[x]);
		free((*map)->col);
	}
}

void	free_and_exit(char **str, char *s, t_info_map *map, int nb)
{
	int		i;

	i = 0;
	while (str != NULL && str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
	if (s != NULL)
		free(s);
	if (map)
		free_arr_col(&map);
	if (nb > 0)
		exit(EXIT_FAILURE);
	if (nb == -1)
	{
		write(2, "failed memory allocation\n", 26);
		exit(EXIT_FAILURE);
	}
}

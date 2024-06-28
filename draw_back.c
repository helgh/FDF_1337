/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 23:24:25 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/06/28 03:57:02 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	maximum(int dx, int dy)
{
	if (dx > dy)
		return (dx);
	else
		return (dy);
}

void	draw_background(t_info_map *map)
{
	char	*pixels;
	int		y;
	int		x;

	y = -1;
	while (++y < HEIGHT_WIN)
	{
		x = -1;
		while (++x < WIDTH_WIN)
		{
			pixels = (map->addr) + (y * map->s + x * (map->bpp / 8));
			*(int *) pixels = BACK_COLOR;
		}
	}
}

void	points_colors(t_info_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->arr[y][x] != 0)
			{
				if (map->col[y][x] == 0)
					map->col[y][x] = 0xff0000;
			}
			else
			{
				if (map->col[y][x] == 0)
					map->col[y][x] = 0xffffff;
			}
		}
	}
}

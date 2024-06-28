/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:13:23 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/06/20 16:41:01 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_zoom_value(t_info_map *map, int x, int y, int x_y)
{
	if (x_y == 120)
	{
		map->b_go->x = x;
		map->b_go->x1 = x + 1;
		map->b_go->y = y;
		map->b_go->y1 = y;
		map->b_go->value_1 = map->arr[y][x + 1];
		map->b_go->color = map->col[y][x];
		if (map->col[y][x + 1] != 0xFFFFFF)
			map->b_go->color = map->col[y][x + 1];
	}
	else
	{
		map->b_go->x = x;
		map->b_go->x1 = x;
		map->b_go->y = y;
		map->b_go->y1 = y + 1;
		map->b_go->value_1 = map->arr[y + 1][x];
		map->b_go->color = map->col[y][x];
		if (map->col[y + 1][x] != 0xFFFFFF)
			map->b_go->color = map->col[y + 1][x];
	}
}

void	arr_to_struct(t_info_map *map)
{
	int		s;
	int		i;

	i = -1;
	while (++i < map->height)
	{
		s = -1;
		while (++s < map->width)
		{
			map->points->y += i;
			map->points->x += s;
		}
	}
	map->points->x /= (map->height * map->width);
	map->points->y /= (map->height * map->width);
	if (map->height > map->width && ((HEIGHT_WIN / 2) > map->height))
		map->zoom = ((HEIGHT_WIN / 2) / map->height);
	else if (map->width >= map->height && (WIDTH_WIN / 2) > map->width)
		map->zoom = ((WIDTH_WIN / 2) / map->width);
	if (map->zoom == 1)
		map->zoom = 1.3;
}

void	ver_hor_line(t_info_map *map, int x, int y, int x_y)
{
	char	*pixels;
	int		max;
	float	dx;
	float	dy;

	get_zoom_value(map, x, y, x_y);
	iso_zoom_offset(map, &dx, &dy);
	max = maximum(fabsf(dx), fabsf(dy));
	dx /= max;
	dy /= max;
	while (max)
	{
		x = (int) map->b_go->x;
		y = (int) map->b_go->y;
		if (y < HEIGHT_WIN && y > 0 && x < WIDTH_WIN && x > 0)
		{
			pixels = map->addr + (int)(y * map->s + x * (map->bpp / 8));
			*(int *) pixels = map->b_go->color;
		}
		map->b_go->x += dx;
		map->b_go->y += dy;
		max -= 1;
	}
}

void	drawing(t_info_map *map)
{
	int	x;
	int	y;

	y = -1;
	draw_background(map);
	points_colors(map);
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			map->b_go->value = map->arr[y][x];
			if (x < map->width - 1)
				ver_hor_line(map, x, y, 120);
			if (y < map->height - 1)
				ver_hor_line(map, x, y, 121);
		}
	}
}

int	main(int ac, char **av)
{
	int			fd;
	int			i;
	t_info_map	*map;

	i = 0;
	map = NULL;
	if (ac != 2)
	{
		write(2, "invalid arguments number\n", 26);
		exit(EXIT_FAILURE);
	}
	fd = open(av[1], O_RDWR);
	if (fd == -1)
	{
		write(2, "failed to open file\n", 21);
		exit(EXIT_FAILURE);
	}
	init_struct(&map, av[1], fd);
	pars_map(av[1], fd, map);
	arr_to_struct(map);
	drawing(map);
	mlx_put_image_to_window(map->mlx, map->mlx_w, map->mlx_i, 0, 0);
	mlx_key_hook(map->mlx_w, &handle_event, map);
	mlx_hook(map->mlx_w, 17, 0, &close_window, map);
	mlx_loop(map->mlx);
}

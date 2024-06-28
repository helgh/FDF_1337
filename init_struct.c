/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:47:15 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/06/20 16:19:41 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_mlx_function(t_info_map *map, char *argv, int fd)
{
	map->points = (t_point *) malloc (sizeof(t_point));
	if (!map->points)
		return (close(fd), free_and_exit(NULL, NULL, map, -1));
	map->bpp = 0;
	map->s = 0;
	map->end = 0;
	map->points->x = 0;
	map->points->y = 0;
	map->mlx = mlx_init();
	if (!map->mlx)
		return (close(fd), free_and_exit(NULL, NULL, map, -1));
	map->title = ft_strjoin("FDF - ", argv, map, fd);
	map->mlx_w = mlx_new_window(map->mlx, WIDTH_WIN, HEIGHT_WIN, map->title);
	if (!map->mlx_w)
		return (close(fd), free_and_exit(NULL, NULL, map, -1));
	map->mlx_i = mlx_new_image(map->mlx, WIDTH_WIN, HEIGHT_WIN);
	if (!map->mlx_i)
		return (close(fd), free_and_exit(NULL, NULL, map, -1));
	map->addr = mlx_get_data_addr(map->mlx_i, &map->bpp, &map->s, &map->end);
}

void	init_struct(t_info_map **map, char *argv, int fd)
{
	t_info_map	*tmp;

	tmp = (t_info_map *) malloc (sizeof(t_info_map));
	if (!tmp)
		return (close(fd), free_and_exit(NULL, NULL, *map, -1));
	tmp->height = 0;
	tmp->width = 0;
	tmp->zoom = 1.3;
	tmp->arr = NULL;
	tmp->col = NULL;
	init_mlx_function(tmp, argv, fd);
	tmp->b_go = (t_bres_algo *) malloc (sizeof(t_bres_algo));
	if (!tmp->b_go)
		return (close(fd), free_and_exit(NULL, NULL, *map, -1));
	tmp->b_go->x = 0;
	tmp->b_go->y = 0;
	tmp->b_go->x1 = 0;
	tmp->b_go->y1 = 0;
	tmp->b_go->value = 0;
	tmp->b_go->value_1 = 0;
	tmp->b_go->color = 0;
	tmp->b_go->offset_x = WIDTH_WIN / 2;
	tmp->b_go->offset_y = HEIGHT_WIN / 2;
	*map = tmp;
}

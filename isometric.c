/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 23:21:55 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/06/28 03:52:15 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	isometric(t_info_map *map)
{
	int	val_x;
	int	val_y;
	int	val_x1;
	int	val_y1;

	val_x = map->b_go->x;
	val_x1 = map->b_go->x1;
	val_y = map->b_go->y;
	val_y1 = map->b_go->y1;
	map->b_go->x = (val_x - val_y) * cos(0.523599);
	map->b_go->y = (val_x + val_y) * sin(0.523599) - map->b_go->value;
	map->b_go->x1 = (val_x1 - val_y1) * cos(0.523599);
	map->b_go->y1 = (val_x1 + val_y1) * sin(0.523599) - map->b_go->value_1;
}

void	iso_zoom_offset(t_info_map *map, float *dx, float *dy)
{
	map->b_go->x -= map->points->x;
	map->b_go->x1 -= map->points->x;
	map->b_go->y -= map->points->y;
	map->b_go->y1 -= map->points->y;
	map->b_go->x *= map->zoom;
	map->b_go->x1 *= map->zoom;
	map->b_go->y *= map->zoom;
	map->b_go->y1 *= map->zoom;
	isometric(map);
	*dx = map->b_go->x1 - map->b_go->x;
	*dy = map->b_go->y1 - map->b_go->y;
	map->b_go->x += map->b_go->offset_x;
	map->b_go->y += map->b_go->offset_y;
}

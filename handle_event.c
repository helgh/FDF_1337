/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 23:29:18 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/06/18 16:15:38 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_event(int keycode, t_info_map *map)
{
	(void) map;
	if (keycode == 53)
	{
		free_and_exit(NULL, NULL, map, 0);
		exit(0);
	}
	return (0);
}

int	close_window(int mouse)
{
	(void) mouse;
	exit(0);
}

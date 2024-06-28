/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:31:59 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/06/28 04:06:37 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_name_file(char *argv)
{
	int		i;
	char	*str;

	str = ".fdf";
	i = 0;
	while (argv[i])
		i++;
	while (argv[i] != 46 && i >= 0)
		i--;
	while (argv[i] && i >= 0)
	{
		if (argv[i] != *str)
		{
			write(2, "bad file format\n", 17);
			return (-1);
		}
		i++;
		str++;
		if (argv[i] == 0 && *str == 0)
			return (0);
	}
	write(2, "bad file format\n", 17);
	return (-1);
}

static int	count_colone(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == 32)
			i++;
		if (str[i] != 32 && str[i] != 0 && str[i] != 10)
			count++;
		while (str[i] != 32 && str[i] != 0)
			i++;
	}
	return (count);
}

static void	stock_value(char *argv, t_info_map *map)
{
	int		fd;
	int		y;
	int		x;
	char	*str;
	char	**spl;

	fd = open(argv, O_RDWR);
	str = get_next_line(fd);
	if (!str)
		return (close(fd), free_and_exit(NULL, str, map, -1));
	y = -1;
	while (str)
	{
		x = -1;
		map->arr[++y] = malloc(sizeof(int) * map->width);
		map->col[y] = malloc(sizeof(int) * map->width);
		if (!map->arr[y] || !map->col[y])
			return (close(fd), free_and_exit(NULL, str, map, -1));
		spl = ft_split(str, 32);
		while (*(spl + (++x)))
		{
			map->arr[y][x] = ft_atoi(*(spl + x), map, x, y);
			if (map->arr[y][x] > 1 || map->arr[y][x] < -1)
				map->arr[y][x] = 1;
		}
		free_and_exit(spl, str, NULL, 0);
		str = get_next_line(fd);
	}
	close(fd);
}

void	pars_map(char *argv, int fd, t_info_map *map)
{
	char	*str;

	if (check_name_file(argv) == -1)
		return (close(fd), free_and_exit(NULL, NULL, map, 1));
	str = get_next_line(fd);
	if (str == NULL)
		return (close(fd), free_and_exit(NULL, NULL, map, -1));
	map->width = count_colone(str);
	map->height += 1;
	while (str)
	{
		if (map->width != count_colone(str))
			return (close(fd), free_and_exit(NULL, str, map, -1));
		free(str);
		str = get_next_line(fd);
		if (str)
			map->height += 1;
	}
	free(str);
	close(fd);
	map->arr = (int **) malloc (sizeof(int *) * (map->height));
	map->col = (int **) malloc (sizeof(int *) * (map->height));
	if (!map->arr || !map->col)
		free_and_exit(NULL, NULL, map, -1);
	stock_value(argv, map);
}

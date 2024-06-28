/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:13:59 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/06/20 17:00:27 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <mlx.h>
# include <time.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# define ESC 53
# define WIDTH_WIN 1200
# define HEIGHT_WIN 800
# define BACK_COLOR 0x404040

typedef struct s_point
{
	float	x;
	float	y;
}			t_point;

typedef struct s_bres_algo
{
	float	x;
	float	y;
	float	x1;
	float	y1;
	int		value;
	int		value_1;
	int		color;
	int		offset_x;
	int		offset_y;
}			t_bres_algo;

typedef struct s_info_map
{
	t_point		*points;
	char		*title;
	int			height;
	int			width;
	float		zoom;
	int			**arr;
	int			**col;
	void		*mlx;
	void		*mlx_w;
	void		*mlx_i;
	char		*addr;
	int			bpp;
	int			s;
	int			end;
	t_bres_algo	*b_go;
}		t_info_map;

void	init_struct(t_info_map **map, char *argv, int fd);
void	pars_map(char *argv, int fd, t_info_map *map);
int		maximum(int dx, int dy);
void	draw_background(t_info_map *map);
void	points_colors(t_info_map *map);
void	iso_zoom_offset(t_info_map *map, float *dx, float *dy);
int		handle_event(int keycode, t_info_map *map);
int		close_window(int mouse);
char	*get_next_line(int fd);
char	*mul_str(char *all, char *str);
char	*copy_line(char *str);
char	*save_free(char *str, char *p);
int		leng(char *str);
char	*find_leak(char *all);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2, t_info_map *map, int fd);
void	free_and_exit(char **str, char *s, t_info_map *map, int nb);
int		ft_atoi(const char *str, t_info_map *map, int x, int y);
void	arr_to_struct(t_info_map *map);
void	drawing(t_info_map *map);

#endif
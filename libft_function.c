/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 23:13:36 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/06/17 23:18:29 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

static void	coppy(char *all, char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		all[i] = s[i];
		i++;
	}
	all[i] = 0;
}

char	*ft_strjoin(char *s1, char *s2, t_info_map *map, int fd)
{
	int		i;
	int		s;
	char	*all;

	i = 0;
	s = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 != NULL)
		i = ft_strlen(s1);
	if (s2 != NULL)
		s = ft_strlen(s2);
	all = malloc(sizeof(char) * (i + s + 1));
	if (all == NULL)
		return (close(fd), free_and_exit(NULL, NULL, map, -1), NULL);
	if (s1 != NULL)
		coppy(all, s1);
	if (s2 != NULL)
		coppy((all + i), s2);
	return (all);
}

static int	set_color(const char *str)
{
	int	i;
	int	s;
	int	count;

	i = 0;
	s = 0;
	count = 0;
	while (str[s] != 0 && str[s] != 10 && str[s] != 32)
		s++;
	while (str[i] != 0 && str[i] != 10)
	{
		if (str[i] >= 65 && str[i] <= 70)
			count += (str[i] - 55) * pow(16, s - 1);
		else if (str[i] >= 97 && str[i] <= 102)
			count += (str[i] - 87) * pow(16, s - 1);
		else
			count += (str[i] - 48) * pow(16, s - 1);
		i++;
		s--;
	}
	return (count);
}

int	ft_atoi(const char *str, t_info_map *map, int x, int y)
{
	int					i;
	int					sign;
	unsigned long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	if (str[i] == 44)
		map->col[y][x] = set_color(&str[i + 3]);
	else
		map->col[y][x] = 0;
	return (result * sign);
}

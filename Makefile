# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/02 16:34:58 by hael-ghd          #+#    #+#              #
#    Updated: 2024/06/17 23:41:54 by hael-ghd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc

FLAGS = -Wall -Wextra -Werror

MLX = -framework OpenGL -framework AppKit libmlx.a

SOURCE = fdf.c get_next_line.c get_next_line_utils.c ft_split.c init_struct.c pars_map.c free_and_exit.c isometric.c libft_function.c draw_back.c handle_event.c \

OBJ_SRC = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_SRC)
	$(CC) $(FLAGS) $(OBJ_SRC) $(MLX) -o $(NAME)

%.o: %.c fdf.h
	$(CC) $(FLAGS) -c $<

clean:
	rm -f $(OBJ_SRC)

fclean: clean
	rm -f $(NAME)

re: fclean all

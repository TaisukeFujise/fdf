# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/30 12:42:52 by tafujise          #+#    #+#              #
#    Updated: 2025/11/20 10:39:26 by tafujise         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:=fdf

SRCDIR:=srcs
SRCS:=main.c\
	free.c\
	hooks.c\
	render.c\
	set_hooks.c\
	init.c\
	utils.c\
	parse.c\
	matrix.c\
	transform.c\
	test.c\

HEADDIR:=includes
HEADERS:=$(HEADDIR)/fdf.h

LIBFT_DIR:=libft
LIBFT:=$(LIBFT_DIR)/libft.a

MLX_DIR:=minilibx-linux
MLX:=$(MLX_DIR)/libmlx_Linux.a

OBJDIR:=objects
OBJS:=$(addprefix $(OBJDIR)/,$(SRCS:%.c=%.o))

CC:=cc

CCFLAGS:=-Wall -Wextra -Werror -I$(HEADDIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

DEBUG_FLAGS:=-g -O0

all:$(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) -lXext -lX11 -lm -lz

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

debug: CCFLAGS += $(DEBUG_FLAGS)
debug:
	$(MAKE) fclean
	$(MAKE) -C $(LIBFT_DIR) CCFLAGS="$(CCFLAGS)" all
	$(MAKE) CCFLAGS="$(CCFLAGS)" all

.PHONY: all clean fclean re debug

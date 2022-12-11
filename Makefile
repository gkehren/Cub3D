# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: genouf <genouf@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 14:36:42 by gkehren           #+#    #+#              #
#    Updated: 2022/12/12 00:02:05 by genouf           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES:= cub3d utils/free \
		parsing/parse parsing/get_next_line parsing/get_next_line_utils parsing/check_map parsing/get_map parsing/get_texture \
		utils/window utils/image move render player print_forms utils/intersections utils/intersections_utils utils/utils \
		init_render utils/minimap utils/is_something parsing/copy

NAME:= cub3D

# ------------------
CC:=cc
SRCPATH:=sources/
HDRPATH:=include/
CCHPATH:=obj/
IFLAGS:=-I ${HDRPATH}
CFLAGS:=-Wall -Wextra -Werror -g3 ${IFLAGS} -I minilibx/
# ==================

# ----- Colors -----
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
CYAN:="\033[1;35m"
PURPLE:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"
# ==================

# ------ Auto ------
SRC:=$(addprefix $(SRCPATH),$(addsuffix .c,$(FILES)))
OBJ:=$(addprefix $(CCHPATH),$(addsuffix .o,$(FILES)))
# ==================

all: ${NAME}

${NAME}: ${OBJ}
	@echo ${CYAN} " - Compiling $@" $(RED)
	make -C minilibx
	@${CC} ${CFLAGS} ${SRC} -Lmlx_linux -lmlx_Linux -L minilibx/ -Imlx_linux -lXext -lX11 -lm -lz -o ${NAME}
	@echo $(GREEN) " - OK" $(EOC)

${CCHPATH}%.o: ${SRCPATH}%.c
	@mkdir -p $(@D)
	@echo ${PURPLE} " - Compiling $< into $@" ${EOC}
	@${CC} ${CFLAGS} -Imlx_linux -O3 -c $< -o $@

%.c:
	@echo ${RED}"Missing file : $@" ${EOC}

clean:
	@make -C minilibx clean
	@rm -rf ${CCHPATH}

fclean:	clean
	@make -C minilibx clean
	@rm -f ${NAME}
	@rm -rf ${NAME}.dSYM/

re:	fclean
	@${MAKE} all

.PHONY:	all clean fclean re

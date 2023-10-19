# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 08:48:00 by wmillett          #+#    #+#              #
#    Updated: 2023/10/19 14:20:56 by wmillett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program Name ----------------------------
NAME = philo
#Dependencies -----------------------------
LIBFT = libft
#Command variables ------------------------
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address #-fsanitize=thread #-O3
MK = mkdir -p
RM = rm -rf
#Sources directories ----------------------
INCDIR = inc
SRCDIR = src
LIBFT_A = libft.a
LIBFTDIR = libft
LIBFT = $(addprefix $(LIBFTDIR)/, $(LIBFT_A))
SRC = main.c\
	error.c\
	parse.c\
	print.c\
	time.c\
	utils_parse.c\
	utils_mem.c\
	routine.c\
	one_philo.c\
	init_data.c\
	mutex.c\
	death.c\
	
VPATH = ${SRCDIR}
#Colours -----------------------------------
B_BLUE='\033[1;34m'
RED=\033[0;31m
YELLOW=\033[33m
MAGENTA=\033[35m
B_GREEN=\033[1;32m
PURPLE=\033[1;35m
COLOUR_END=\033[0m
#Object directories ------------------------
OBJDIR = obj
OBJS = $(addprefix ${OBJDIR}/, ${SRC:%.c=%.o})
#Rules -------------------------------------
${OBJDIR}/%.o : %.c
	@${CC} ${CFLAGS} -I${INCDIR} -Ilibft/inc -c $< -o $@
all: $(NAME)
$(NAME): $(OBJDIR) $(OBJS)
	@$(CC) ${CFLAGS} $(OBJS) -o $(NAME)
	@echo "$(YELLOW)😴<$(NAME)>🤔$(B_GREEN)has been created $(COLOUR_END)!"
$(OBJDIR):
	@$(MK) $(OBJDIR)
clean:
	@$(RM) $(OBJDIR)
fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) has been deleted 🗑️$(COLOUR_END)"
re: fclean all
.PHONY: all clean fclean re
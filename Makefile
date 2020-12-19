NAME		=	minishell

LIBFT_DIR	=	./libs/libftprintf
LIBFT		=	$(LIBFT_DIR)/libftprintf.a
LIBS		=	$(LIBFT)

SRCS		=	srcs/main.c \
				srcs/new_gnl/get_next_line.c \
				srcs/parsing/parse.c \
				srcs/exec/exec.c \
				srcs/utils/prints/prints.c \
				srcs/built_ins/cd.c \
				srcs/built_ins/echo.c \
				srcs/built_ins/env.c \
				srcs/built_ins/exit.c \
				srcs/built_ins/export.c \
				srcs/built_ins/pwd.c \
				srcs/built_ins/split_mod.c \
				srcs/built_ins/unset.c \
				#srcs/built_ins/env_manag.c 

SRCS_PG		=	playground/main.c

OBJS		=	$(SRCS:.c=.o)
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
INC_PATH	=	-I./incs
COMPILE		=	$(CC) $(FLAGS) $(INC_PATH) -L$(LIBFT_DIR) -lftprintf

%.o : %.c	
			$(CC) $(FLAGS) $(INC_PATH) -c $<  -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(LIBS) ${OBJS}
			$(COMPILE) $(OBJS) -o $(NAME)
$(LIBFT):	
			make -C $(LIBFT_DIR)

clean:		
			make clean -C $(LIBFT_DIR)
			rm -f ${OBJS}

fclean:		
			make fclean -C $(LIBFT_DIR)
			rm -f ${OBJS}
			rm -f ${NAME}

re:			fclean all

playground:	$(LIBS) $(SRCS_PG)
			$(COMPILE) $(SRCS_PG) -o srcs/playground/minishell_pg.out
			./srcs/playground/minishell_pg.out

.PHONY:		clean fclean all re 
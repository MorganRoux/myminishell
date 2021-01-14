NAME		=	minishell

LIBFT_DIR	=	./libs/libftprintf
LIBFT		=	$(LIBFT_DIR)/libftprintf.a
LIBS		=	$(LIBFT)

SRCS		=	srcs/main.c \
				srcs/get_next_line/get_next_line.c \
				srcs/get_next_line/get_next_line_utils.c \
				srcs/parsing/parse.c \
				srcs/parsing/split_tokens.c \
				srcs/utils/extract/extract.c \
				srcs/exec/exec.c \
				srcs/exec/commands.c \
				srcs/exec/redirections.c \
				srcs/exec/pipes.c \
				srcs/env/env.c \
				srcs/utils/prints/prints.c \
				srcs/utils/free/frees.c \
				srcs/utils/path/path.c \
				srcs/utils/list/ft_lstinit.c \
				srcs/utils/list/ft_lstof.c \
				srcs/utils/tokens/is_meta.c \
				srcs/built_ins/cd.c \
				srcs/built_ins/echo.c \
				srcs/built_ins/env.c \
				srcs/built_ins/exit.c \
				srcs/built_ins/export.c \
				srcs/built_ins/pwd.c \
				srcs/built_ins/split_mod.c \
				srcs/built_ins/unset.c \
				srcs/built_ins/sig.c \
				srcs/built_ins/env_manag.c

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

test:		all
			sh ./test/test.sh

.PHONY:		clean fclean all re 
NAME		=	minishell

LIBFT_DIR	=	./libs/libftprintf
LIBFT		=	$(LIBFT_DIR)/libftprintf.a
LIBS		=	$(LIBFT)

SRCS		=	srcs/main.c \
				srcs/get_next_line/get_next_line.c \
				srcs/get_next_line/get_next_line_utils.c \
				srcs/parsing/parse1.c \
				srcs/parsing/parse2.c \
				srcs/parsing/parse3.c \
				srcs/parsing/parse4.c \
				srcs/parsing/parse5.c \
				srcs/parsing/parse6.c \
				srcs/parsing/split_tokens.c \
				srcs/utils/extract/extract.c \
				srcs/exec/exec.c \
				srcs/exec/commands.c \
				srcs/exec/redirections.c \
				srcs/exec/pipes.c \
				srcs/exec/pipe_redir_sup.c \
				srcs/exec/pipes_redir_sup2.c \
				srcs/exec/tools_exec.c \
				srcs/env/env.c \
				srcs/utils/prints/prints.c \
				srcs/utils/free/frees.c \
				srcs/utils/path/path.c \
				srcs/utils/list/ft_lstinit.c \
				srcs/utils/list/ft_lstof.c \
				srcs/utils/tokens/is_meta.c \
				srcs/utils/split_commands/split_commands.c \
				srcs/utils/split_commands/s_c_sup.c \
				srcs/utils/ft_isalpha_u/ft_isalpha_u.c \
				srcs/built_ins/cd.c \
				srcs/built_ins/echo.c \
				srcs/built_ins/env.c \
				srcs/built_ins/exit.c \
				srcs/built_ins/export.c \
				srcs/built_ins/export_sup.c \
				srcs/built_ins/pwd.c \
				srcs/built_ins/split_join_mod.c \
				srcs/built_ins/unset.c \
				srcs/built_ins/sig.c \
				srcs/built_ins/tools.c \
				srcs/built_ins/env_manag.c \
				srcs/built_ins/env_manage2.c \
				srcs/builtins/echo/echo.c \
				srcs/builtins/env/env.c \
				srcs/builtins/pwd/pwd.c \
				srcs/builtins/cd/cd.c \
				srcs/builtins/exit/exit.c \
				srcs/builtins/unset/unset.c

SRCS_PG		=	playground/main.c

OBJS		=	$(SRCS:.c=.o)
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror -g
INC_PATH	=	-I./incs
COMPILE		=	$(CC) $(FLAGS) $(INC_PATH) -L$(LIBFT_DIR) -lftprintf

%.o : %.c	
			$(CC) $(FLAGS) $(INC_PATH) -c $<  -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(LIBS) ${OBJS}
			$(COMPILE) $(OBJS) $(LIBS) -o $(NAME)
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
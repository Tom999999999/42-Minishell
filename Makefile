# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 17:09:19 by dolifero          #+#    #+#              #
#    Updated: 2024/06/10 18:32:34 by dolifero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 18:40:32 by dolifero          #+#    #+#              #
#    Updated: 2024/05/10 16:56:03 by dolifero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c builtin_commands
vpath %.c environment
vpath %.c execution
vpath %.c parsing
vpath %.c prompts
vpath %.c utilities

NAME			= minishell

SRCS			=	prompt.c\
					utils.c\
					parsing.c\
					token.c\
					executing.c\
					if_builtin.c\
					execute_builtin.c\
					change_dir.c\
					echo.c\
					pwd.c\
					exit.c\
					freeing.c\
					minishell.c

OBJS			= $(SRCS:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror
LDFLAGS			= -lreadline

LIBFT_DIR 		= Libft
LIBFT			= $(LIBFT_DIR)/libft.a

BOLD_PURPLE	=	\033[1;35m
BOLD_CYAN	=	\033[1;36m
BOLD_YELLOW	=	\033[1;33m
BOLD_WHITE	=	\033[1;97m
BOLD_GREEN	=	\033[1;92m
NO_COLOR	=	\033[0m
DEF_COLOR	=	\033[0;39m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[0;92m
YELLOW		=	\033[0;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[2;96m
BR_CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

all:			$(NAME)
				clear;
				@$(MAKE) SHELL_CYAN
				@$(MAKE) loading
				clear;
				@$(MAKE) SHELL_GREEN
				@echo "             $(BOLD_GREEN)${NAME} DONE!\n$(DEF_COLOR)"

$(NAME):		$(OBJS) $(LIBFT)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) -L $(LIBFT_DIR) -lft

$(LIBFT):
				@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@echo "$(CYAN)"
				$(RM) $(OBJS) $(LIBFT_DIR)/*.o
				@echo "$(DEF_COLOR)"

fclean:
				@echo "$(CYAN)"
				$(RM) $(OBJS) $(NAME) $(LIBFT_DIR)/*.o $(LIBFT)
				@echo "$(DEF_COLOR)"

re:				fclean all

SHELL_CYAN:
				@echo "\n$(BR_CYAN)              _       _      __         ____"
				@echo "   ____ ___  (_)___  (_)____/ /_  ___  / / /"
				@echo "  / __  __ \/ / __ \/ / ___/ __ \/ _ \/ / / "
				@echo " / / / / / / / / / / (__  ) / / /  __/ / /  "
				@echo "/_/ /_/ /_/_/_/ /_/_/____/_/ /_/\___/_/_/   "
				@echo "                                            $(BOLD_CYAN)\n"

SHELL_GREEN:
				@echo "\n$(GREEN)              _       _      __         ____"
				@echo "   ____ ___  (_)___  (_)____/ /_  ___  / / /"
				@echo "  / __  __ \/ / __ \/ / ___/ __ \/ _ \/ / / "
				@echo " / / / / / / / / / / (__  ) / / /  __/ / /        $(BOLD_GREEN)-tecker$(GREEN)"
				@echo "/_/ /_/ /_/_/_/ /_/_/____/_/ /_/\___/_/_/        $(BOLD_GREEN)-dolifero$(GREEN)"
				@echo "                                            $(DEF_COLOR)\n"

loading:
				@for i in {1..42}; do \
					printf '%s' "█"; \
					sleep 0.01; \
				done

.PHONY:			all clean fclean re

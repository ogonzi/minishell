# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/18 10:00:13 by ogonzale          #+#    #+#              #
#    Updated: 2022/11/15 16:50:23 by cpeset-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -=-=-=-=- NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

NAME 		:= minishell
BNAME		:= minishell_bonus

MKFL        = Makefile

# -=-=-=-=- CLRS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

DEF_COLOR 	:= \033[0;39m
GRAY 		:= \033[0;90m
RED 		:= \033[0;91m
GREEN 		:= \033[0;92m
YELLOW 		:= \033[0;93m
BLUE 		:= \033[0;94m
MAGENTA 	:= \033[0;95m
CYAN 		:= \033[0;96m
WHITE 		:= \033[0;97m

# -=-=-=-=- CMND -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

CFLAGS      = -Wall -Wextra -Werror -W
XFLAGS      = -fsanitize=address -g

RM      = rm -f
MK      = mkdir -p
CP      = cp -f

# -=-=-=-=- PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

MND_DIR	= mandatory/
INC_DIR = inc/
SRC_DIR = src/
TUL_DIR = tools/
UTL_DIR = util/
OBJ_DIR = .obj/

LIB_DIR = library/
LFT_DIR = $(LIB_DIR)libft/
PRT_DIR = $(LIB_DIR)ft_printf/
GNL_DIR = $(LIB_DIR)ft_gnl/

# -=-=-=-=- FILE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

INCLUDE = -I./$(INC_DIR) -I./$(LFT_DIR)$(INC_DIR)

PRS_DIR	= parser/
PRS_FLS	= split_cmd_line.c ft_split_mod.c split_words.c split_words_2.c \
	           split_utils.c split_utils_2.c

MND_FLS	= minishell.c signals.c free.c exec.c get_exec_path.c util.c

UTL_DIR	= errors.c

SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(TUL_DIR), $(addprefix $(PRS_DIR), $(PRS_FILES))))
SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(SRC_DIR), $(MND_FLS)))

OBJS	= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
DEPS	= $(addsuffix .d, $(basename $(OBJS)))

# -=-=-=-=- RULE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

$(OBJ_DIR)%.o: %.c $(MKFL)
	@mkdir -p $(dir $@)
	@printf "\r$(GREEN)\tCompiling: $(YELLOW)$< $(DEF_CLR)                   \r"
	@$(CC) -MT $@ -MMD -MP $(CFLAGS) $(INCLUDE) -c $< -o $@

all:
	@$(MAKE) -C $(LFT_DIR)
	@$(MAKE) $(NAME)

$(NAME):: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@printf "\n\t$(WHITE)Program \033[1;31mMinishell $(WHITE)has been compiled!$(DEF_COLOR)\n"

$(NAME)::
	@printf "\t$(WHITE)Nothing more to be done for program \033[1;31mMinishell$(DEF_COLOR)\n"

-include $(DEPS)

clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -sC $(LIBFT_DIR)
	@echo "$(BLUE)	Minishell object and dependencies files cleaned.$(DEF_COLOR)"

fclean:
	@$(RM) -r $(OBJ_DIR)
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LFT_DIR)
	@rm -rf *.dSYM
	@find . -name ".DS_Store" -delete
	@echo "$(WHITE)	All objects, dependencies and executables removed.$(DEF_COLOR)"

re:
	@$(MAKE) fclean
	@$(MAKE)
	@echo "$(GREEN)Cleaned and rebuilt everything for $(NAME)project.$(DEF_COLOR)"

norm:
	@clear
	@norminette $(SRC_DIR) $(INC) $(LIBFT_DIR) | grep -v Norme -B1 || true
	
.PHONY:	all clean fclean re norm bonus rebonus $(LIBFT)


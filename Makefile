# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/18 10:00:13 by ogonzale          #+#    #+#              #
#    Updated: 2023/01/15 20:53:25 by cpeset-c         ###   ########.fr        #
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
DFLAGS		= -MT $@ -MMD -MP
XFLAGS      = -fsanitize=address -g3
LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib
RL_INC		= -I/Users/$(USER)/.brew/opt/readline/include

RM      = rm -f
MK      = mkdir -p
CP      = cp -f

# -=-=-=-=- PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

MND_DIR	= mandatory/
BNS_DIR	= bonus/
INC_DIR = inc/
SRC_DIR = src/
TUL_DIR = tools/
UTL_DIR = utils/
OBJ_DIR = .obj/
BIN_DIR	= bin/

PRS_DIR	= parser/
EXE_DIR	= exec/
EXP_DIR	= expand/

LIB_DIR = library/
LFT_DIR = $(LIB_DIR)libft/
OUT_DIR = $(LIB_DIR)liboutput/

# -=-=-=-=- FILE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

LIBFT	= $(LIB_DIR)libft.a
PRINT	= $(OUT_DIR)liboutput.a

INCLUDE = -I$(INC_DIR) -I$(LFT_DIR)$(INC_DIR) -I$(OUT_DIR)$(INC_DIR) $(RL_INC)

# -=-=- ECHO
# -=-=- CD
# -=-=- PWD
# -=-=- EXPORT
# -=-=- UNSET
# -=-=- EXIT

EXT_FLS	= exit.c

# -=-=- ENV

ENV_FLS	= env.c

# -=-=- 

SRC_FLS	= minishell.c \
		signals.c \
		enviroment.c

PRS_FLS	= split_mod.c \
		split_cmd_line.c \
		split_words.c \
		split_words_2.c \
		split_words_3.c \
		split_utils.c \
		split_utils_2.c

EXP_FLS	= expand_words.c \
		expand_words_2.c \
		expand_words_3.c \
		expand_words_utils.c

EXE_FLS	= exec.c \
		exec_utils.c \
		get_exec_path.c \
		redir_in.c \
		redir_out.c

UTL_FLS	= errors.c \
		utils.c \
		free.c

SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(SRC_DIR), $(SRC_FLS)))
SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(TUL_DIR), $(TUL_FLS)))
SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(TUL_DIR), $(addprefix $(PRS_DIR), $(PRS_FLS))))
SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(TUL_DIR), $(addprefix $(EXP_DIR), $(EXP_FLS))))
SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(TUL_DIR), $(addprefix $(EXE_DIR), $(EXE_FLS))))
SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(UTL_DIR), $(UTL_FLS)))

OBJS	= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

BLT_SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(TUL_DIR), $(EXT_FLS)))
BLT_SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(TUL_DIR), $(ENV_FLS)))

BLT_OBJS	= $(addprefix $(OBJ_DIR), $(BLT_SRCS:.c=.o))

DEPS	+= $(addsuffix .d, $(basename $(OBJS)))
DEPS	+= $(addsuffix .d, $(basename $(BLT_OBJS)))

# -=-=-=-=- RULE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

$(OBJ_DIR)%.o: %.c $(MKFL)
	@$(MK) $(dir $@)
	@printf "\r$(GREEN)\tCompiling: $(YELLOW)$< $(DEF_CLR)                   \n"
	@$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

all:
	@$(MAKE) -C $(LIB_DIR)
	@$(MAKE) $(NAME)

$(NAME):: $(OBJS) $(BLT_OBJS)
	@$(MAKE) builtin
	@$(CC) $(CFLAGS) $(XFLAGS) $(OBJS) $(LIBFT) $(PRINT) $(LDFLAGS) -lreadline -o $(NAME)
	@printf "\n\t$(WHITE)Program \033[1;31mMinishell $(WHITE)has been compiled!$(DEF_COLOR)\n"

$(NAME)::
	@printf "\t$(WHITE)Nothing more to be done for program \033[1;31mMinishell$(DEF_COLOR)\n"

-include $(DEPS)

builtin:
	@$(MK) $(BIN_DIR)
	@$(CC) $(CFLAGS) $(XFLAGS) $(OBJ_DIR)$(MND_DIR)$(TUL_DIR)env.o $(LIBFT) $(PRINT) -o $(BIN_DIR)env
	@$(CC) $(CFLAGS) $(XFLAGS) $(OBJ_DIR)$(MND_DIR)$(TUL_DIR)exit.o $(LIBFT) $(PRINT) -o $(BIN_DIR)exit


clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -sC $(LIB_DIR)
	@echo "$(BLUE)	Minishell object and dependencies files cleaned.$(DEF_COLOR)"

fclean:
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r $(BIN_DIR)
	@$(RM) $(NAME)
	@$(MAKE) fclean -sC $(LIB_DIR)
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


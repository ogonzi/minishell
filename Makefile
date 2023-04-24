# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 11:54:08 by cpeset-c          #+#    #+#              #
#    Updated: 2023/04/24 20:48:44 by cpeset-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -=-=-=-=- NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

NAME 		:= minishell

MKFL        := Makefile

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
DFLAGS		= -MT $@ -MMD
XFLAGS      = #-fsanitize=address -fsanitize-recover=address -g3
LFLAGS		= #-fsanitize=leak
LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib
RL_INC		= -I/Users/$(USER)/.brew/opt/readline/include

RM      = rm -f
MK      = mkdir -p
CP      = cp -f

# -=-=-=-=- PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

BIN_DIR	= bin/

MND_DIR	= mandatory/

INC_DIR = inc/
SRC_DIR = src/
TUL_DIR = tools/
UTL_DIR = utils/
OBJ_DIR = .objs/
DEP_DIR	= .deps/

PRS_DIR	= parser/
WRD_DIR	= words/
EXE_DIR	= exec/
EXP_DIR	= expand/
BLT_DIR	= builtin/

LIB_DIR = library/
LFT_DIR = $(LIB_DIR)libft/
OUT_DIR = $(LIB_DIR)liboutput/

# -=-=-=-=- FILE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

LIBFT	= $(LIB_DIR)libft.a
PRINT	= $(OUT_DIR)liboutput.a

INCLUDE = -I$(MND_DIR)$(INC_DIR) -I$(LFT_DIR)$(INC_DIR) -I$(OUT_DIR)$(INC_DIR) $(RL_INC)

SRC_FLS	= minishell.c \
		enviroment.c \
		custom_enviroment.c \
		signals.c

BLT_FLS	= builtins.c \
		ft_pwd.c \
		ft_env.c \
		ft_exit.c \
		ft_echo.c \
		ft_export.c \
		ft_export_utils.c \
		ft_unset.c \
		ft_cd.c \
		ft_cd_utils.c \
		ft_cd_tools.c \
		ft_cd_auxiliar.c

EXE_FLS	= exec.c \
		redir_in.c \
		redir_out.c \
		exec_utils.c \
		exec_path.c \
		exec_extra.c

EXP_FLS	= expand_words.c \
		expand_words_tools.c \
		expand_words_utils.c \
		expand_words_env_utils.c

PRS_FLS	= split.c \
		split_utils.c \
		split_mod.c \
		split_mod_utils.c

WRD_FLS	= split_words.c \
		split_words_token.c \
		split_words_tools.c \
		split_words_utils.c

UTL_FLS = mnshll_utils.c \
		env_lst.c \
		error.c \
		banner.c

SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(SRC_DIR), $(SRC_FLS)))
SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(UTL_DIR), $(UTL_FLS)))
SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(TUL_DIR), $(addprefix $(PRS_DIR), $(PRS_FLS))))
SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(TUL_DIR), $(addprefix $(WRD_DIR), $(WRD_FLS))))
SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(TUL_DIR), $(addprefix $(EXP_DIR), $(EXP_FLS))))
SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(TUL_DIR), $(addprefix $(EXE_DIR), $(EXE_FLS))))
SRCS	+= $(addprefix $(MND_DIR), $(addprefix $(TUL_DIR), $(addprefix $(BLT_DIR), $(BLT_FLS))))

OBJS	= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
DEPS	= $(addprefix $(DEP_DIR), $(addsuffix .d, $(basename $(SRCS))))

# -=-=-=-=- RULE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: makelib $(NAME) $(BLTN)

makelib:
	@$(MAKE) -C $(LIB_DIR)

$(NAME):: $(OBJS)
	@$(CC) $(CFLAGS) $(XFLAGS) $(OBJS) $(LIBFT) $(PRINT) $(LDFLAGS) -lreadline -o $(NAME)
	@$(MK) $(BIN_DIR)
	@mv $(NAME) $(BIN_DIR)$(NAME)
	@printf "\n\t$(WHITE)Program \033[1;31mMinishell $(WHITE)has been compiled!$(DEF_COLOR)\n"

$(NAME)::
	@printf "\t$(WHITE)Nothing more to be done for program \033[1;31mMinishell$(DEF_COLOR)\n"

-include $(DEPS)

clean:
	@$(RM) -r $(OBJ_DIR) $(DEP_DIR)
	@make clean -sC $(LIB_DIR)
	@find . -name ".DS_Store" -delete
	@echo "$(BLUE)	Minishell object and dependencies files cleaned.$(DEF_COLOR)"

fclean:
	@$(RM) -r $(OBJ_DIR) $(DEP_DIR)
	@$(RM) -r $(BIN_DIR)
	@$(MAKE) fclean -sC $(LIB_DIR)
	@find . -name ".DS_Store" -delete
	@echo "$(WHITE)	All objects, dependencies and executables removed.$(DEF_COLOR)"

re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything for $(NAME)project.$(DEF_COLOR)"

norm:
	@clear
	@norminette $(SRC_DIR) $(TUL_DIR) $(UTL_DIR) $(INC_DIR) $(LIB_DIR) | grep -v Norme -B1 || true

$(OBJ_DIR)%.o: %.c $(MKFL)
	@$(MK) $(dir $@) $(dir $(subst $(OBJ_DIR), $(DEP_DIR), $@))
	@printf "$(WHITE)\r\tCompiling: $(YELLOW)$<$(DEF_COLOR)                           \r"
	@$(CC) $(CFLAGS) $(DFLAGS) $(XFLAGS) $(INCLUDE) -c $< -o $@
	@mv $(patsubst %.o, %.d, $@) $(dir $(subst $(OBJ_DIR), $(DEP_DIR), $@))

.PHONY:	all makelib clean fclean re norm

NAME := philo

NAME_C := $(NAME).c
HDR_DIR = .

#Libs
SRC_DIR := .
SRC_ARC :=	./srcs/srcs.a 	\

ALL_ARC := $(SRC_ARC)

ALL_C := $(foreach arc, $(ALL_ARC), $(wildcard $(dir $(arc))*.c))

#Vars
MAKEFLAGS += --no-print-directory

FLAGS := -Wall -Wextra -Werror

RM := rm -f

blank :=
define NEWLINE

$(blank)
endef

COLOUR_GREEN := \033[1;32m
COLOUR_RED := \033[1;31m
COLOUR_YELLOW := \033[1;33m
COLOUR_BLUE := \033[1;34m
COLOR_WHITE := \033[0m

all: $(NAME)

$(NAME): $(ALL_ARC) $(NAME_C)
	@cc $(FLAGS) -o $@ -I$(HDR_DIR) $(NAME_C) $(ALL_ARC)
	@echo "$(COLOUR_GREEN)Made main file$(COLOR_WHITE)"

%.a: $(ALL_C)
ifeq ($($?),)
	@echo "$(COLOUR_BLUE)Updating archives of $@$(COLOR_WHITE)"
	@cd $(dir $@ ) && make
	@touch $@
endif

clean:
	@echo "$(COLOUR_YELLOW)Cleaning archives$(COLOR_WHITE)"
	@$(foreach dir,$(dir $(ALL_ARC)), cd $(dir) && make fclean && echo$(NEWLINE)$(NEWLINE))

fclean: 
	@echo "$(COLOUR_YELLOW)Cleaning everything$(COLOR_WHITE)"
	@$(RM) $(NAME)
	@$(foreach dir,$(dir $(ALL_ARC)), cd $(dir) && make fclean && echo$(NEWLINE)$(NEWLINE))

re: re_libs all
	
re_libs:
	@echo "$(COLOUR_BLUE)Remaking everything$(COLOR_WHITE)"
	@$(foreach dir,$(dir $(ALL_ARC)), cd $(dir) && make re && echo$(NEWLINE)$(NEWLINE))

.PHONY: all clean fclean re
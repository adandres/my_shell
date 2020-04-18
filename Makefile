# **************************************************************************** #
#                                                                              #
#                                                     .-***-.  /\_!/\    \!    #
#    Makefile                                        /       \.'`  `',.--//    #
#                                                  -(        I       I   @\    #
#    By: adandres                                    \       /'.____.'\___|    #
#                                                     '-...-' __/ | \   (`)    #
#    Created: 2020/04/06 17:14:21 by adandres               /    /  /          #
#    Updated: 2020/04/19 01:02:06 by adandres                                  #
#                                                                              #
# **************************************************************************** #

NAME = my_shell
CC = gcc
FLAGS = -Werror -Wextra -Wall
VPATH = src: \
	src/states: \
	src/states/parsing_state: \
	src/states/expansion_state \
	src/states/building_state: \
	src/states/execution_state \
	src/builtin \
	src/utils

SRC = starting_state.c read_input.c read_file.c parse_input.c \
	get_token.c check_redir.c reverse_redir.c first_is_cmd.c sort_list.c \
	build_tree.c expand_input.c create_branch.c get_env_var.c get_cmd_path.c \
	print_tree.c execute_tree.c redir.c exec.c expands.c main.c tab.c \
	change_directory.c env_index.c my_env.c my_unsetenv.c echo.c my_set.c \
	free.c my_export.c add_env.c extend.c get_cmd_data.c relaunch.c \
	get_word.c utils_parse.c

H_PATH = include
O_PATH = obj
O_NAME = $(SRC:.c=.o)
OBJ = $(addprefix $(O_PATH)/,$(O_NAME))
LDFLAGS = -Llibme -lme
LIB = libme/libme.a
HEADERS = -Iinclude -Ilibme/include

all : lib $(NAME)

$(NAME) : $(OBJ) $(LIB)
	$(CC) $(FLAGS) $(HEADERS) $(LDFLAGS) -o $@ $(OBJ)

$(O_PATH)/%.o : %.c
	mkdir $(O_PATH) 2> /dev/null || true
	$(CC) $(FLAGS) $(HEADERS) -o $@ -c $<

lib :
	$(MAKE) -C libme

clean :
	rm -rf $(O_PATH) 2> /dev/null || true

fclean : clean
	rm -f $(NAME)

re : fclean all
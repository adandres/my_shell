# **************************************************************************** #
#                                                                              #
#                                                     .-***-.  /\_!/\    \!    #
#    Makefile                                        /       \.'`  `',.--//    #
#                                                  -(        I       I   @\    #
#    By: adandres                                    \       /'.____.'\___|    #
#                                                     '-...-' __/ | \   (`)    #
#    Created: 2020/04/06 17:14:21 by adandres               /    /  /          #
#    Updated: 2020/06/21 13:28:30 by adandres                                  #
#                                                                              #
# **************************************************************************** #

NAME = my_shell
CC = gcc
FLAGS = -Wextra -Wall
VPATH = src: \
	src/states: \
	src/states/reading_state: \
	src/states/reading_state/line_editing: \
	src/states/parsing_state: \
	src/states/parsing_state/sort/:\
	src/states/building_state: \
	src/states/execution_state: \
	src/builtin: \
	src/utils

SRC =	starting_state.c read_input.c read_file.c parse_input.c assign.c\
	get_token.c check_redir.c reverse_redir.c first_is_cmd.c sort_list.c \
	build_tree.c create_branch.c get_env_var.c get_cmd_path.c \
	print_tree.c execute_tree.c exec_redir.c exec_cmd.c main.c tab.c \
	change_directory.c env_index.c my_env.c my_unsetenv.c echo.c my_set.c \
	free.c my_export.c add_env.c extend.c get_cmd_data.c relaunch.c \
	get_word.c utils_parse.c exec_loop.c exec_builtin.c error.c sort.c \
	parser.c expand_redir.c write_hdoc.c handle_multiple_command.c \
	handle_user_input.c apply_term.c print_cmd.c handle_arrows.c \
	count.c get_cursor_position.c print_cursor.c get_cmd.c \
	check_quotes.c check_sep.c

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

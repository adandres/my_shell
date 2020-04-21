# **************************************************************************** #
#                                                                              #
#                                                     .-***-.  /\_!/\    \!    #
#    Makefile                                        /       \.'`  `',.--//    #
#                                                  -(        I       I   @\    #
#    By: adandres                                    \       /'.____.'\___|    #
#                                                     '-...-' __/ | \   (`)    #
#    Created: 2020/03/16 11:52:14 by adandres               /    /  /          #
#    Updated: 2020/04/19 02:15:50 by adandres                                  #
#                                                                              #
# **************************************************************************** #

NAME = libme.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
VPATH = .:src/my_put:src/my_is:src/my_mem:src/my_str:src/my_lst:src/my_other:src/my_printf\
	src/my_printf/print:src/my_printf/print/parse:src/my_printf/print/get_spec

SRC = my_putchar.c my_putendl.c my_putnbr.c my_putstr.c my_putchar_fd.c \
	my_putendl_fd.c my_putnbr_fd.c my_putstr_fd.c \
	my_isalnum.c my_isalpha.c my_isascii.c my_isdigit.c my_isprint.c \
	my_bzero.c my_memccpy.c my_memcmp.c my_memdel.c my_memset.c \
	my_memalloc.c my_memchr.c my_memcpy.c my_memmove.c \
	my_strcat.c my_strdup.c my_strlen.c my_strnequ.c my_strsub.c \
	my_strchr.c my_strequ.c my_strmap.c my_strnew.c my_strtrim.c \
	my_strclr.c my_striter.c my_strmapi.c my_strnstr.c my_strtoupper.c \
	my_strcmp.c my_striteri.c my_strncat.c my_strrchr.c my_strtolower.c \
	my_strcpy.c my_strjoin.c my_strncmp.c my_strsplit.c \
	my_strdel.c my_strlcat.c my_strncpy.c my_strstr.c my_strcdel.c\
	my_lst_add.c my_lst_push_tab.c my_lst_new.c my_lst_reverse.c \
	my_tolower.c my_toupper.c my_itoa.c my_atoi.c my_uitoa_base.c \
	my_uitoa.c my_printf.c parse_padding.c print_format.c print_init.c \
	get_dec.c get_specifier.c get_udec.c utils.c parse_lenght.c get_addr.c \
	get_next_line.c my_strndup.c my_strjoin_free.c my_realloc.c \
	my_strjoin_tab.c my_strichr.c my_memswap.c my_lst_len.c my_lst_pass.c \
	my_lst_free.c

H_PATH = include
O_PATH = obj
O_NAME = $(SRC:.c=.o)
OBJ = $(addprefix $(O_PATH)/,$(O_NAME))
DEPDIR = $(O_PATH)/odeps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
DEPFILES = $(SRC:%.c=$(DEPDIR)/%.d)

CURSOR = \033[1A
LCLEAR = \033[2K

all : $(NAME)

$(NAME) : $(O_PATH) $(OBJ)
	@ar -rc $@ $(OBJ)
	@ranlib $@
	@echo "library created"

$(O_PATH)/%.o : %.c $(DEPDIR)/%.d
	@$(CC) $(DEPFLAGS) $(FLAGS) -I$(H_PATH) -o $@ -c $<
	@echo "$(LCLEAR)Compiling $<"

$(O_PATH) :
	@mkdir $(O_PATH)
	@mkdir $(DEPDIR)

$(DEPFILES) :
-include $(DEPFILES)

clean :
	@rm -rf $(DEPDIR)
	@rm -rf $(O_PATH)

fclean : clean
	@rm -f $(NAME)

re : fclean all

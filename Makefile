GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m

SDIR	= ./src
UDIR	= ./utils

SSRCS	= main create_pipe execve_cmd handle_error
USRCS	= access_path_checker ft_split ft_splitpath ft_strcmp ft_strcpy ft_strlen ft_substr get_path free_double_array ft_strchr close_all_fd

OSSRCS = $(addprefix $(SDIR)/,$(addsuffix .c,$(SSRCS)))
OUSRCS = $(addprefix $(UDIR)/,$(addsuffix .c,$(USRCS)))

FILES	= $(OSSRCS) $(OUSRCS)
OBJS	= $(FILES:.c=.o)
CFLAGS	= -Wall -Werror -Wextra
ifeq ($(DEBUG),debug)
	CFLAGS	+= -fsanitize=address -g3
endif
NAME	= pipex
CC		= cc $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)\n\nCompiling pipex..."
	@$(CC) -o $(NAME)  $(OBJS)
	@echo "$(GREEN)Done"

%.o: %.c
	@echo "$(YELLOW)Generating pipex objects..." $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "$(RED)\nDeleting objects..."
	@rm -f $(OBJS)

fclean: clean
	@echo "$(RED)\nDeleting executable..."
	@rm -f $(NAME)

re: fclean all

bonus: $(NAME)

.PHONY:	clean fclean all bonus re


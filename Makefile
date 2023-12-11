DIR = ..

NAME = ps_tester.out
NAME_BONUS = checker_tester.out

PUSH_SWAP = $(DIR)/push_swap
CHECKER = $(DIR)/checker

LIBFT = libft.a
LIBFT_DIR = ../libft
LIBFT_FULL = $(LIBFT_DIR)/$(LIBFT)

SOURCES = tester_ps.c
SOURCES_BONUS = tester_checker.c

CFLAGS += -Wall -Wextra -Werror

all: $(NAME)

$(PUSH_SWAP):
	make -C $(DIR)

$(CHECKER):
	make bonus -C $(DIR)

$(NAME): $(PUSH_SWAP)
	cc $(CFLAGS) -o $(NAME) $(SOURCES) $(LIBFT_FULL)
	./$(NAME)

$(NAME_BONUS): $(PUSH_SWAP) $(CHECKER)
	cc $(CFLAGS) -o $(NAME_BONUS) $(SOURCES_BONUS) $(LIBFT_FULL)
	./$(NAME_BONUS)

bonus: $(NAME_BONUS)

clean:
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

.PHONY: all bonus clean $(NAME) $(NAME_BONUS)

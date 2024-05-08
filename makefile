NAME = pipex
SOURCES = ft_split.c ft_strjoin.c get_envp.c paths.c pipes.c pipex.c
BSOURCES = ft_split_bonus.c ft_strjoin_bonus.c get_envp_bonus.c pipes_bonus.c paths_bonus.c pipex_bonus.c here_docs.c get_next_line.c get_next_line_utils.c
CC = CC
OBJECTS = $(SOURCES:.c=.o)
BOBJECTS = $(BSOURCES:.c=.o)
BONUS = .macos
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

bonus: $(BONUS)

$(BONUS) : $(BOBJECTS)
	cc $(CFLAGS) $(BOBJECTS) -o pipex
	@touch $(BONUS)
$(NAME): $(OBJECTS)
	cc  $(CFLAGS) $(OBJECTS) -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(BOBJECTS)
fclean: clean
	rm -rf $(NAME)
	rm -rf $(OBJECTS) $(BOBJECTS)


.PHONY : bonus all clean fclean
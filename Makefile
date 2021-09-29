##
## FZWID, 2021
## Makefile
##

SRC         =   $(wildcard src/**.c)
OBJ         =   $(SRC:.c=.o)
NAME        =   fzwid

CFLAGS      =   -Wall           \
                -W              \
                -I include

all:    $(NAME)

$(NAME):$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:		fclean all

##
## FZWID, 2021
## Makefile
##

SRC         =   $(wildcard src/**.c)
OBJ         =   $(SRC:.c=.o)
NAME        =   test/fzwid.wasm

CFLAGS      =   -Wall           \
                -W              \
                -I include      \
                -O3

all:    $(NAME)

$(NAME):$(OBJ)
	$(CC) -lZydis -Llib --no-entry -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:		fclean all

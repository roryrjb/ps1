LDFLAGS = `pkg-config --libs libgit2`
CFLAGS = -std=c99 -pedantic -O2 \
	 -Wall -Wextra -Wsign-compare \
	 -fstack-protector-strong -fpie \
	 -D_FORTIFY_SOURCE=2
NAME = ps1

$(NAME): main.o
	$(CC) $(CFLAGS) -o $(NAME) $< $(LDFLAGS)

install: $(NAME)
	install -m755 $(NAME) /usr/local/bin/

clean:
	rm -f *.o $(NAME)

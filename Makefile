LDFLAGS = `pkg-config --libs libgit2`
CFLAGS = -std=c99 -pedantic -O2 \
	 -Wall -Wextra -Wsign-compare \
	 -fstack-protector-strong -fpie \
	 -D_FORTIFY_SOURCE=2
NAME = ps1

$(NAME): main.o
	$(CC) $(CFLAGS) -o $(NAME) $< $(LDFLAGS)

ps1.1: ps1.1.scd
	scdoc < $< > $@

install: $(NAME) ps1.1
	install -m755 $(NAME) /usr/local/bin/
	install -m444 ps1.1 /usr/local/man/man1/
clean:
	rm -f *.o $(NAME)

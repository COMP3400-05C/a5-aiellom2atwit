CFLAGS += -Wall -Wextra -Wfatal-errors -g3
CFLAGS += -Werror=vla -Werror=shadow -Wno-unused -Wno-unused-parameter
CFLAGS += -fsanitize=address -fsanitize=undefined

all: parta partb partc

parta: parta.c
	$(CC) $(CFLAGS) -o parta parta.c

partb: partb.c
	$(CC) $(CFLAGS) -o partb partb.c

partc: partc.c
	$(CC) $(CFLAGS) -o partc partc.c

.PHONY: clean
clean:
	rm -rf parta partb partc


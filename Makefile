CFLAGS ?= -Wall -Werror
OUTPUTS = mergesort

.PHONY: all
all: ${OUTPUTS}

.PHONY: clean
clean: ${OUTPUTS}
	rm -f -- ${OUTPUTS}

%.o: %.c
mergesort: mergesort.c

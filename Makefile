include Config
all:

# ************* #
# Real targets. #
# ************* #

# Build directory.
build:
	mkdir -p build

# Interface headers.
FACE_INCS = $(wildcard bbdump/*.h)

# Main program.
MAIN_INCS = $(wildcard *.h)
MAIN_SRCS = $(wildcard *.c)
MAIN_OBJS = $(patsubst %.c, build/%.o, $(MAIN_SRCS))
MAIN_BIN  = build/bbdump

$(MAIN_OBJS): build/%.o: %.c $(MAIN_INCS) $(FACE_INCS) build
	$(CC) $(ALL_CFLAGS) -c $< -I. -o $@

$(MAIN_BIN): $(MAIN_OBJS)
	$(CC) $(ALL_CFLAGS) $(ALL_LDFLAGS) $^ -o $@

# Demo programs.
DEMO_SRCS = $(wildcard demo/*.c)
DEMO_BINS = $(patsubst demo/%.c, build/%, $(DEMO_SRCS))

$(DEMO_BINS): build/%: demo/%.c $(FACE_INCS) build
	$(CC) $(ALL_CFLAGS) $(ALL_LDFLAGS) $< -I. -o $@

# ************** #
# Phony targets. #
# ************** #

.PHONY: all show demo install clean dist

all: $(MAIN_BIN)
show: all
	$(MAIN_BIN) < demo/256_bytes
demo: $(DEMO_BINS)

install: all
	install -m644 $(FACE_INCS) -Dt $(DESTDIR)$(INCDIR)/bbdump
	install -m755 $(MAIN_BIN) -Dt $(DESTDIR)$(BINDIR)
clean:
	rm -rf build
dist: build
	tar -zcf build/$(TARNAME).tar.gz --transform="s/^\./$(TARNAME)/" \
		--exclude="./build" --exclude="./.*" .

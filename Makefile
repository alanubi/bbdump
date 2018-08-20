include Config
all:

# ************* #
# Real targets. #
# ************* #

# Main program.
MAIN_INCS = $(wildcard src/*.h)
MAIN_SRCS = $(wildcard src/*.c)
MAIN_OBJS = $(patsubst src/%.c, build/%.o, $(MAIN_SRCS))
MAIN_BIN  = build/bbdump

$(MAIN_OBJS): build/%.o: src/%.c $(MAIN_INCS) $(FACE_INCS)
	@mkdir -p build
	$(CC) $(ALL_CFLAGS) -c $< -I. -o $@

$(MAIN_BIN): $(MAIN_OBJS)
	$(CC) $(ALL_CFLAGS) $(ALL_LDFLAGS) $^ -o $@

# ************** #
# Phony targets. #
# ************** #

.PHONY: all show install clean dist

all: $(MAIN_BIN)
show: all
	$(MAIN_BIN) < ./all_bytes

install: all
	install -m755 $(MAIN_BIN) -Dt $(DESTDIR)$(BINDIR)
clean:
	rm -rf build
dist:
	@mkdir -p build
	tar -zcf build/$(TARNAME).tar.gz --transform="s/^\./$(TARNAME)/" \
		--exclude="./build" --exclude="./.*" .

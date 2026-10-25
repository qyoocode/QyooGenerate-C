CC ?= cc
CFLAGS ?= -O2 -Wall -Wextra -std=c11
GD_CFLAGS ?= $(shell pkg-config --cflags gdlib 2>/dev/null)
GD_LIBS ?= $(shell pkg-config --libs gdlib 2>/dev/null)
CPPFLAGS += $(GD_CFLAGS)
LDLIBS += $(GD_LIBS)
SRCS = qyoo.c qyoo_generator.c image_renderer.c svg_renderer.c svg.c
EXEDIR ?= ../bin
OBJDIR ?= ../obj
OUTPUTDIR ?= ../output
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
OUTPUT = $(EXEDIR)/qyoo
.PHONY: all test
all: $(OUTPUT) $(OUTPUTDIR)
$(OBJDIR) $(EXEDIR) $(OUTPUTDIR):
	mkdir -p $@
$(OBJDIR)/%.o: %.c $(wildcard *.h) | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
$(OUTPUT): $(OBJS) | $(EXEDIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)
test: all
	python3 ../tests/test_cli.py
	$(CC) $(CFLAGS) ../tests/test_svg_allocation.c -o $(OBJDIR)/test-svg-allocation
	$(OBJDIR)/test-svg-allocation
	$(CC) $(CFLAGS) ../tests/test_svg_document.c svg.c -o $(OBJDIR)/test-svg-document
	$(OBJDIR)/test-svg-document

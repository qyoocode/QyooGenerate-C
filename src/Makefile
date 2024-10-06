# Define the compiler and flags
CC = gcc
CFLAGS = -I/opt/homebrew/include  # Compiler flags (for header files)
LDFLAGS = -L/opt/homebrew/lib -lgd  # Linker flags (for libraries)

# Define the source files and the output executable
SRCS = qyoo.c qyoo_generator.c image_renderer.c svg_renderer.c svg.c
EXEDIR = ../bin
OBJDIR = ../obj
OUTPUTDIR = ../output
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))  # Object files in ../obj
OUTPUT = $(EXEDIR)/qyoo

# Default target
all: $(OUTPUT) $(OUTPUTDIR)

# Debugging: print OBJS to see what's being generated
debug:
	@echo "Object files: '$(OBJS)'"

# Create the object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Create the output and executable directories if they don't exist
$(EXEDIR) $(OUTPUTDIR):
	mkdir -p $@

# Compile individual source files into object files in the ../obj directory
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Link the object files and create the executable
$(OUTPUT): $(OBJS) | $(EXEDIR)
	$(CC) -o $(OUTPUT) $(OBJS) $(LDFLAGS)

# Clean up object files and the executable
clean:
	rm -f $(OBJS)  # Remove object files
	rm -f $(OUTPUT)  # Remove the executable

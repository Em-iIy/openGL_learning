# ----------------------------------------Name
NAME = out

# ----------------------------------------Files
FILES_SRCS =	main.cpp \
				EBO.cpp \
				VAO.cpp \
				VBO.cpp \
				Cube_vec3.cpp \
				glad.cpp \
				readFile.cpp \
				shaderClass.cpp \
				window.cpp \

FILES_OBJS = $(FILES_SRCS:.cpp=.o)

# ----------------------------------------Directories
DIR_SRCS = ./src/
DIR_OBJS = ./obj/

vpath %.cpp $(DIR_SRCS)

# ----------------------------------------Sources
SRCS = $(FILES_SRCS:%=$(DIR_SRCS)%)

# ----------------------------------------Objects
OBJS = $(FILES_OBJS:%=$(DIR_OBJS)%)

# ----------------------------------------Flags
CC = c++
# CFLAGS = -std=c++98
# CFLAGS += -Wall -Wextra -Werror
CFLAGS += -g -fsanitize=address
LFLAGS += -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit # Apple flags
# LFLAGS += -lglfw -ldl # Linux flags
INC = -Iinc -Iinc/glm

# ----------------------------------------Making
all:
	@$(MAKE) $(NAME) -j4

$(NAME): $(DIR_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INC) $(LFLAGS)

$(DIR_OBJS)%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(DIR_OBJS):
	mkdir -p $@

# ----------------------------------------Cleaning
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

# ----------------------------------------Name
NAME = out

# ----------------------------------------Files
FILES_SRCS =	main.cpp \
				EBO.cpp \
				VAO.cpp \
				VBO.cpp \
				Cube_vec3.cpp \
				Curve.cpp \
				glad.cpp \
				readFile.cpp \
				shaderClass.cpp \
				VectorClass.cpp \
				Camera.cpp \
				window.cpp \
				stb.cpp \
				glmPrintUtils.cpp \

FILES_OBJS = $(FILES_SRCS:.cpp=.o)

# ----------------------------------------Directories
DIR_SRCS = ./src/
DIR_OBJS = ./obj/

vpath %.cpp $(DIR_SRCS)

# ----------------------------------------Sources
SRCS = $(FILES_SRCS:%=$(DIR_SRCS)%)

# ----------------------------------------Objects
OBJS = $(FILES_OBJS:%=$(DIR_OBJS)%)

# ----------------------------------------Libs
GLM = inc/glm/.git

# ----------------------------------------Flags
CC = c++
CFLAGS = -std=c++11
# CFLAGS += -Wall -Wextra -Werror
# CFLAGS += -g -fsanitize=address
UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	LFLAGS = -lglfw -ldl # Linux flags
endif
ifeq ($(UNAME), Darwin)
	LFLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit # Apple flags
endif
INC = -Iinc -Iinc/glm

# ----------------------------------------Making
all:
	@$(MAKE) $(NAME) -j4

$(NAME): $(DIR_OBJS) $(OBJS) $(GLM)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INC) $(LFLAGS)

$(GLM):
	@echo "fetching submodules..."
	git submodule init
	git submodule update

$(DIR_OBJS)%.o: %.cpp $(GLM)
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

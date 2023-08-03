# ----------------------------------------Name
NAME = out

# ----------------------------------------Files
FILES_SRCS =	main.cpp \
				EBO.cpp \
				VAO.cpp \
				VBO.cpp \
				glad.cpp \
				readFile.cpp \
				shaderClass.cpp \
				Camera.cpp \
				window.cpp \
				stb.cpp \
				glmPrintUtils.cpp \
				loadTex.cpp \
				inputProcessing.cpp \
				# Cube_vec3.cpp \
				# Curve.cpp \
				# VectorClass.cpp \

FILES_OBJS = $(FILES_SRCS:.cpp=.o)

# ----------------------------------------Directories
DIR_SRCS = ./src/
DIR_OBJS = ./obj/
DIR_ASSIMP = ./src/lib/assimp/

vpath %.cpp $(DIR_SRCS) \
			$(DIR_SRCS)utils/ \
			$(DIR_SRCS)lib/ \

# ----------------------------------------Sources
SRCS = $(FILES_SRCS:%=$(DIR_SRCS)%)

# ----------------------------------------Objects
OBJS = $(FILES_OBJS:%=$(DIR_OBJS)%)

# ----------------------------------------Libs
GLM_SM = inc/glm/.git
ASSIMP = $(DIR_ASSIMP)bin/libassimp.5.2.5.dylib
ASSIMP_SM = $(DIR_ASSIMP).git

SUBMODULES =	$(GLM_SM) \
				$(ASSIMP_SM) \


# ----------------------------------------Flags
CC = c++
CFLAGS = -std=c++11
CFLAGS += -Wall -Wextra -Werror
# CFLAGS += -g -fsanitize=address
UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	LFLAGS = -lglfw -ldl # Linux flags
endif
ifeq ($(UNAME), Darwin)
	LFLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit # Apple flags
endif
INC =  -Iinc -Iinc/glm -Isrc

# ----------------------------------------Making
all:
	@$(MAKE) $(NAME) -j4

$(NAME): $(DIR_OBJS) $(OBJS) $(SUBMODULES) $(ASSIMP)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INC) $(LFLAGS) $(ASSIMP)

$(SUBMODULES):
	@echo "fetching submodules..."
	git submodule init
	git submodule update

$(ASSIMP):
	cmake $(DIR_ASSIMP)CMakeLists.txt -B $(DIR_ASSIMP)
	make -C $(DIR_ASSIMP)


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

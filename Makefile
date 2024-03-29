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
ASSIMP = $(DIR_ASSIMP)bin
ASSIMP_SM = $(DIR_ASSIMP).git


# ----------------------------------------Flags
CC = c++
CFLAGS = -std=c++11
CFLAGS += -Wall -Wextra -Werror
# CFLAGS += -g -fsanitize=address
UNAME = $(shell uname)

ASSIMP_FLAGS = -L$(ASSIMP) -lassimp -Wl,-rpath=$(ASSIMP)

ifeq ($(UNAME), Linux)
	LFLAGS = -lglfw -ldl $(ASSIMP_FLAGS) # Linux flags
endif
ifeq ($(UNAME), Darwin)
	LFLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit $(ASSIMP_FLAGS) # Apple flags
endif
INC =  -Iinc -Iinc/glm -Isrc

# ----------------------------------------Making
all: $(GLM_SM) $(ASSIMP)
	@$(MAKE) $(NAME) -j4


$(NAME): $(DIR_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INC) $(LFLAGS)


$(ASSIMP): $(ASSIMP_SM) 
	cmake $(DIR_ASSIMP)CMakeLists.txt -B $(DIR_ASSIMP)
	make -j4 -C $(DIR_ASSIMP)


$(DIR_OBJS)%.o: %.cpp $(GLM)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(DIR_OBJS):
	mkdir -p $@

$(ASSIMP_SM): 
	@$(MAKE) submodule
$(GLM_SM): 
	@$(MAKE) submodule

submodule:
	@echo "fetching submodules..."
	git submodule init
	git submodule update

# ----------------------------------------Cleaning
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re submodule

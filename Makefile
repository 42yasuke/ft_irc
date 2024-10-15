CPP = c++

CPP_FLAGS = -MMD -Wall -Wextra -Werror -std=c++98 -c

RM = rm -f

INC = -I includes/

CPP_FILES =	

OBJ = $(CPP_FILES:.cpp=.o)
DEP = $(CPP_FILES:.cpp=.d)

SRC = src/
BUILD = build/

OBJ := $(addprefix $(BUILD), $(OBJ))
DEP := $(addprefix $(BUILD), $(DEP))

NAME = ircserv

all : $(NAME)

$(BUILD) :
			mkdir -p $(BUILD)

$(BUILD)%.o : $(SRC)%.cpp | $(BUILD)
			$(CPP) $(CPP_FLAGS) $(INC) $< -o $@

$(NAME) : $(OBJ)
			$(CPP) $(OBJ) -o $(NAME)

clean :
		$(RM) $(OBJ) $(DEP)
		$(RM) -r $(BUILD)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY : all fclean clean re

-include $(DEP)
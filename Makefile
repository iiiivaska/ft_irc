FLAGS	= -Wall -Wextra -Werror -I. -std=c++98

HEADER	= Server/Server.hpp utils.hpp

SRCS	= Server/Server.cpp main.cpp

OBJS	= $(SRCS:.cpp=.o)

CXX		= clang++

%.o: %.cpp $(HEADER)
	$(CXX) $(FLAGS) -c $< -o $@

NAME	= ircserv

all:	$(NAME)

$(NAME):	$(OBJS)
				$(CXX) $(FLAGS) -o $(NAME) $(OBJS)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean $(NAME)

run:		$(NAME)
			./ircserv 54000 pass

lrun:		$(NAME)
			leaks -atExit -- ./ircserv 54000 pass

.PHONY:		all clean fclean re run
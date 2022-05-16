FLAGS	= -I.

HEADER	= Server/Server.hpp utils.hpp User/User.hpp Channel/Channel.hpp commands/includes/Command.hpp commands/includes/CommandParser.hpp commands/utilities/utilities.hpp

SRCS	= Server/Server.cpp main.cpp User/User.cpp Channel/Channel.cpp commands/src/Command.cpp commands/src/CommandParser.cpp commands/utilities/utilities.cpp

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
			./ircserv 3491 pass

lrun:		$(NAME)
			leaks -atExit -- ./ircserv 3491 pass

.PHONY:		all clean fclean re run
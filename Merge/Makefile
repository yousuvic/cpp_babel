CC			=	g++

RM			=	rm -f

SRC			=	Client/AudioManager.cpp		\
				Client/ClientController.cpp	\
				Client/ClientTCPLinux.cpp	\
				Client/UDPExchangeLinux.cpp	\
				Client/EncodeManager.cpp	\
				Client/Main.cpp				\
				Client/NetworkServices.cpp	\

OBJ			=	$(SRC:.cpp=.o)

NAME		=	bin/babel_client

GCCFLAGS	=	-lportaudio -lopus

CXXFLAGS	=	-I/usr/local/Cellar/opus/1.1/include/opus -I/usr/local/Cellar/portaudio/19.20140130/include

all			:	$(NAME)

$(NAME)		:	$(OBJ)
				g++ -o $(NAME) $(OBJ) -L/usr/local/Cellar/opus/1.1/lib -L/usr/local/Cellar/portaudio/19.20140130/lib $(GCCFLAGS)

clean		:
				$(RM) $(OBJ)

fclean		:	clean
				$(RM) $(NAME)

re			:	fclean all
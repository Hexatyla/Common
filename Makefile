##
## Makefile for  in /home/geoffrey/Projects/pfa
## 
## Made by geoffrey bauduin
## Login   <baudui_g@epitech.net>
## 
## Started on  Wed Feb  5 14:00:43 2014 geoffrey bauduin
## Last update Fri Apr  4 17:33:57 2014 geoffrey bauduin
##

NAME=			hexatylaCommon.so

SRCDIR=			src
NETWORKDIR=		$(SRCDIR)/Network
THREADDIR=		$(SRCDIR)/Threading
PROTOCOLDIR=		$(SRCDIR)/Protocol
GAMEDIR=		$(SRCDIR)/Game
FACTORYDIR=		$(SRCDIR)/Factory
KERNELDIR=		$(SRCDIR)/Kernel
PARSERDIR=		$(SRCDIR)/Parser
ALGODIR=		$(SRCDIR)/Algo
UTILSDIR=		$(SRCDIR)/Utils
TESTDIR=		tests

NAME_TEST=		common_test

SRC_NETWORK=		$(NETWORKDIR)/Socket.cpp		\
			$(NETWORKDIR)/SSocket.cpp		\
			$(NETWORKDIR)/Exception.cpp

SRC_THREADING=		$(THREADDIR)/Mutex.cpp			\
			$(THREADDIR)/Thread.cpp			\
			$(THREADDIR)/ScopeLock.cpp		\
			$(THREADDIR)/CondVar.cpp		\
			$(THREADDIR)/Pool.cpp

SRC_PROTOCOL=		$(PROTOCOLDIR)/Error.cpp		\
			$(PROTOCOLDIR)/Job.cpp			\
			$(PROTOCOLDIR)/Color.cpp		\
			$(PROTOCOLDIR)/Command.cpp		\
			$(PROTOCOLDIR)/Difficulty.cpp		\
			$(PROTOCOLDIR)/Race.cpp			\
			$(PROTOCOLDIR)/User.cpp			\
			$(PROTOCOLDIR)/JobResolver.cpp

SRC_GAME=		$(GAMEDIR)/Ressources.cpp		\
			$(GAMEDIR)/Position.cpp			\
			$(GAMEDIR)/Movable.cpp			\
			$(GAMEDIR)/Amelioration.cpp		\
			$(GAMEDIR)/AElement.cpp			\
			$(GAMEDIR)/Building.cpp			\
			$(GAMEDIR)/Hero.cpp			\
			$(GAMEDIR)/Unit.cpp			\
			$(GAMEDIR)/Player.cpp			\
			$(GAMEDIR)/Race.cpp			\
			$(GAMEDIR)/Projectile.cpp		\
			$(GAMEDIR)/Requirements.cpp		\
			$(GAMEDIR)/Capacity.cpp			\
			$(GAMEDIR)/Team.cpp			\
			$(GAMEDIR)/Effect.cpp			\
			$(GAMEDIR)/Map.cpp			\
			$(GAMEDIR)/Controller.cpp		\
			$(GAMEDIR)/Object.cpp			\
			$(GAMEDIR)/RessourcesSpot.cpp		\
			$(GAMEDIR)/ProductionQueue.cpp		\
			$(GAMEDIR)/ABase.cpp			\
			$(GAMEDIR)/Action.cpp			\
			$(GAMEDIR)/CanUseCapacity.cpp

SRC_FILES=		$(SRCDIR)/Date.cpp			\
			$(SRCDIR)/Logger.cpp			\
			$(SRCDIR)/Clock.cpp			\
			$(SRCDIR)/HasSerial.cpp			\
			$(SRCDIR)/HasInfos.cpp			\
			$(SRCDIR)/HasID.cpp			\
			$(SRCDIR)/FileLoader.cpp		\
			$(SRCDIR)/NoDeleteWhileUsedByAThread.cpp

SRC_FACTORY=		$(FACTORYDIR)/Factory.cpp		\
			$(FACTORYDIR)/Kernel.cpp		\
			$(FACTORYDIR)/Protocol.cpp		\
			$(FACTORYDIR)/Game.cpp

SRC_PARSER=		$(PARSERDIR)/JSON.cpp			\
			$(PARSERDIR)/ARace.cpp			\
			$(PARSERDIR)/Map.cpp

SRC_UTILS=		$(UTILSDIR)/FileReader.cpp		\
			$(UTILSDIR)/Hexagon.cpp

SRC_KERNEL=		$(KERNELDIR)/Data.cpp			\
			$(KERNELDIR)/Cost.cpp			\
			$(KERNELDIR)/ElementRessources.cpp	\
			$(KERNELDIR)/Time.cpp			\
			$(KERNELDIR)/Manager.cpp		\
			$(KERNELDIR)/CapacityList.cpp		\
			$(KERNELDIR)/Serial.cpp			\
			$(KERNELDIR)/CapacityData.cpp		\
			$(KERNELDIR)/BuildingData.cpp		\
			$(KERNELDIR)/ID.cpp			\
			$(KERNELDIR)/Effect.cpp			\
			$(KERNELDIR)/Config.cpp

SRC_ALGO=		$(ALGODIR)/MD5.cpp

SRC=			$(SRC_NETWORK)				\
			$(SRC_THREADING)			\
			$(SRC_PROTOCOL)				\
			$(SRC_GAME)				\
			$(SRC_FILES)				\
			$(SRC_FACTORY)				\
			$(SRC_PARSER)				\
			$(SRC_UTILS)				\
			$(SRC_KERNEL)				\
			$(SRC_ALGO)

SRC_TEST=		$(TESTDIR)/main.cpp			\
			$(TESTDIR)/Algo/MD5.cpp			\
			$(SRC)

OBJ=			$(SRC:.cpp=.o)

OBJ_TEST=		$(SRC_TEST:.cpp=.o)

DEPS=			$(OBJ:.o=.deps)

LDFLAGS=		-lssl -lcrypto -lpthread

INCLUDES=		-Iincludes/

CXXFLAGS=		$(INCLUDES) -std=c++11 -Wall -Wextra -fPIC -shared

CXX=			g++

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) -shared

server:		CXXFLAGS += -D__SERVER__
server:		all

%.o:		%.cpp
		@$(CXX) -c $(CXXFLAGS) -MMD $< -o $@ -MF $(patsubst %.o, %.deps, $@) && echo "CXX\t$<"

client:		CXXFLAGS += -DCLIENT__
client:		all

test:		comp_test $(NAME_TEST)
		./$(NAME_TEST)

comp_test:
		cd gtest-1.7.0/
		test -s Makefile || ( ./configure && $(MAKE) )
		cd -

$(NAME_TEST):	CXXFLAGS += -Igtest-1.7.0/include/
$(NAME_TEST):	LDFLAGS += ./libs/libjson.a -Wl,-rpath,./gtest-1.7.0/lib/.libs/ -L./gtest-1.7.0/lib/.libs/ -lgtest
$(NAME_TEST):	$(OBJ_TEST)
		$(CXX) -o $(NAME_TEST) $(OBJ_TEST) $(LDFLAGS)

clean:
		rm -f $(OBJ)
		rm -f $(OBJ_TEST)

fclean:		clean
		rm -f $(NAME)
		rm -f $(NAME_TEST)

re:		hardclean all

hardclean:	fclean
		rm -f $(DEPS)

-include $(DEPS)

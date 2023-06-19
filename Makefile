CXX = g++
CXXFLAGS = -std=c++14 
EXEC = straights
OBJECTS = main.o Card.o Game.o Player.o Round.o View.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
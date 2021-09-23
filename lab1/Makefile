CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Wextra -MMD -Wno-implicit-fallthrough
#CXXFLAGS = -std=c++14 -i Wall -MMD
EXEC = simulate
OBJECTS = main.o event.o packet.o networkqueue.o simulator.o csvwriter.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
		${CXX} ${CXXFLAGS} ${OBJECTS} ${LIBDIR} -o ${EXEC} ${LIBRARIES} 

-include ${DEPENDS}

.PHONY: clean

clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}
	
graph:
		python plotq3.py
		python plotq6.py

graphq3:
		python plotq3.py

graphq6:
		python plotq6.py

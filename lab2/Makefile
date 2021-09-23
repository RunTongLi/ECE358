CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Wextra -MMD -Wno-implicit-fallthrough
#CXXFLAGS = -std=c++14 -i Wall -MMD
EXEC = simulate
OBJECTS = main.o channel.o node.o packetqueue.o packet.o csvwriter.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
		${CXX} ${CXXFLAGS} ${OBJECTS} ${LIBDIR} -o ${EXEC} ${LIBRARIES} 

-include ${DEPENDS}

.PHONY: clean

clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}

graph:
		python plotq1.py
		python plotq2.py

graphq1:
		python plotq3.py

graphq2:
		python plotq6.py

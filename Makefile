BIN = pi
OBJS = calc.o expression.o main.o 
CC = g++
CXXFLAGS = -Wall -O3 -std=c++17

all : ${BIN}
${BIN}: ${OBJS}  
	${CC} ${CXXFLAGS} -o ${BIN} ${OBJS}
${OBJS}: %.o: %.cpp 
	${CC}  -c ${CXXFLAGS} $< -o $@
.PHONY: clean
clean:
	rm ${OBJS} ${BIN}


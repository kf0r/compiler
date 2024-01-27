
TARGET = compiler

CXX = g++

CXXFLAGS = -g -std=c++11 -Wall

SOURCES = lexer.l parser.ypp Types.cpp Vertex.cpp Block.cpp Architecture.cpp ProgramStructure.cpp Assembly.cpp LowLevelProgram.cpp AssemblyAlgerba.cpp

BISON_OUTPUT = parser.tab.cpp
FLEX_OUTPUT = lex.yy.c

OBJECTS = $(BISON_OUTPUT:.cpp=.o) $(FLEX_OUTPUT:.cpp=.o) Types.o Vertex.o Block.o Architecture.o ProgramStructure.o Assembly.o LowLevelProgram.o AssemblyAlgerba.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

$(BISON_OUTPUT): parser.ypp
	bison -H $^

$(FLEX_OUTPUT): lexer.l
	flex $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(BISON_OUTPUT) $(FLEX_OUTPUT) $(OBJECTS)

.PHONY: all clean


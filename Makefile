# Makefile

# Nazwa programu wynikowego
TARGET = compiler

# Kompilator C++
CXX = g++

# Flagi kompilacji
CXXFLAGS = -g -std=c++11 -Wall

# Pliki źródłowe
SOURCES = lexer.l parser.ypp Types.cpp Vertex.cpp Block.cpp Architecture.cpp ProgramStructure.cpp Assembly.cpp LowLevelProgram.cpp AssemblyAlgerba.cpp

# Pliki wykonywalne Bison i Flex
BISON_OUTPUT = parser.tab.cpp
FLEX_OUTPUT = lex.yy.c

# Pliki obiektowe
OBJECTS = $(BISON_OUTPUT:.cpp=.o) $(FLEX_OUTPUT:.cpp=.o) Types.o Vertex.o Block.o Architecture.o ProgramStructure.o Assembly.o LowLevelProgram.o AssemblyAlgerba.o

# Domyślne zadanie
all: $(TARGET)

# Cel główny
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	rm -f *.o
	rm -f /cores/*
	codesign -s - -f --entitlements compiler.entitlements compiler

# Bison
$(BISON_OUTPUT): parser.ypp
	bison -H $^

# Flex
$(FLEX_OUTPUT): lexer.l
	flex $^

# Reguła ogólna dla plików obiektowych
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Reguła czyszczenia
clean:
	rm -f $(TARGET) $(BISON_OUTPUT) $(FLEX_OUTPUT) $(OBJECTS)

.PHONY: all clean


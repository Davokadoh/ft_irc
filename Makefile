# Compiler
CXX = c++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -Iinc

# Directories
INC_DIR = inc
SRC_DIR = src
CMD_DIR = $(SRC_DIR)/cmds
OBJ_DIR = obj
TST_DIR = tests

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(CMD_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, obj/%.o, $(SRC_FILES))
TEST_FILES = $(wildcard $(TST_DIR)/*.cpp)
TEST_OBJ_FILES = $(patsubst $(TST_DIR)/%.cpp, obj/%.o, $(TEST_FILES))

# Executable name
EXECUTABLE = bin/ft_irc

# Google Test libraries
GTEST = -lgtest -lgtest_main -lpthread

# Targets
all: $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) $(TEST_EXECUTABLE) obj/*.o bin/*

# Object files
obj/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/%.o: $(TST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/cmds:
	mkdir -p $(OBJ_DIR)/cmds

# Executable
$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $^

test: test_parser

parser.o : $(SRC_DIR)/parser.cpp $(INC_DIR)/parser.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/parser.cpp -o $(OBJ_DIR)/parser.o

parser_test.o: $(TST_DIR)/parser_test.cpp $(INC_DIR)/parser.hpp
	$(CXX) $(CXXFLAGS) -c $(TST_DIR)/parser_test.cpp -o $(OBJ_DIR)/parser_test.o

test_parser: parser.o parser_test.o
	$(CXX) $(CXXFLAGS) $^ $(GTEST) -o $@

.PHONY: all clean test

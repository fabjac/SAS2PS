CXX=g++
LIB_FLAGS = 
CXXFLAGS = -I inc
CXXFLAGS += -g --std=c++0x -Wall -Wextra -Wfatal-errors

SRC_DIR=src
INC_DIR=inc
BIN_DIR=bin

all : $(BIN_DIR)/fileConverter

SRC_FILES += fileConverter.cpp \
	shareasale_record.cpp \
	prestashop_record.cpp \
	wrapper.cpp

re: clean all

OBJ_FILES = $(SRC_FILES:%.cpp=$(BIN_DIR)/%.o)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS) -c -o $@  $< $(LIB_FLAGS)

$(BIN_DIR)/fileConverter.o: $(SRC_DIR)/fileConverter.cpp
	$(CXX) $(CXXFLAGS) -c -o $@  $< $(LIB_FLAGS)

$(BIN_DIR)/fileConverter: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $+ $(LIB_FLAGS)

.PHONY: clean
clean:
	cd $(BIN_DIR) && rm -f fileConverter *.o


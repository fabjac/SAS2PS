CXX=g++
LIB_FLAGS = 
CXXFLAGS = -I inc -I /usr/include/mysql++ -I /usr/include/mysql
CXXFLAGS += -g --std=c++0x -Wall -Wextra -Wfatal-errors
LDFLAGS = -L/usr/local/lib -lmysqlpp -lmysqlclient -lnsl -lz -lm

SRC_DIR=src
INC_DIR=inc
BIN_DIR=bin

all : dirs $(BIN_DIR)/sas2ps

SRC_FILES += sas2ps.cpp \
	database.cpp \
	tools.cpp \
	shareasale_record.cpp \
	prestashop_record.cpp \
	wrapper.cpp

re: clean all

OBJ_FILES = $(SRC_FILES:%.cpp=$(BIN_DIR)/%.o)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS) -c -o $@  $< $(LIB_FLAGS)

$(BIN_DIR)/sas2ps.o: $(SRC_DIR)/sas2ps.cpp
	$(CXX) $(CXXFLAGS) -c -o $@  $< $(LIB_FLAGS)

$(BIN_DIR)/sas2ps: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $+ $(LIB_FLAGS) $(LDFLAGS)

.PHONY: dirs
dirs:
	@test -d $(BIN_DIR) || mkdir $(BIN_DIR)

.PHONY: clean
clean:
	cd $(BIN_DIR) && rm -f sas2ps *.o


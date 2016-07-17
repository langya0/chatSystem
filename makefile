ROOT_PATH=$(shell pwd)
SERVER_PATH=$(ROOT_PATH)/server
CLIENT_PATH=$(ROOT_PATH)/client
DATA_PATH=$(ROOT_PATH)/data_pool
COMM_PATH=$(ROOT_PATH)/comm
# LIB_PATH=$(ROOT_PATH)/lib
WINDOW_PATH=$(ROOT_PATH)/window

# /////////////

SER=udp_server
CLI=udp_client
CC=g++

FIND_INCLUDE=-I$(COMM_PATH) -I$(DATA_PATH) -I$(WINDOW_PATH)
# -I$(LIB_PATH)/include

FIND_LIB=-L$(LIB_PATH)/lib

LDFLAGS=-ljson -lpthread
FLAGS=-D_FAST_


SER_SRC=$(shell ls $(SERVER_PATH) | grep -E '*.cpp')
SER_SRC+=$(shell ls $(COMM_PATH) | grep -E '*.cpp')
SER_SRC+=$(shell ls $(DATA_PATH) | grep -E '*.cpp')
SER_OBJ=$(SER_SRC:.cpp=.o)

CLI_SRC=$(shell ls $(CLIENT_PATH) | grep -E '*.cpp')
CLI_SRC+=$(shell ls $(COMM_PATH) | grep -E '*.cpp')
CLI_SRC+=$(shell ls $(WINDOW_PATH) | grep -E '*.cpp')
CLI_OBJ=$(CLI_SRC:.cpp=.o)


.PHONY:all
all:$(SER) $(CLI)
# all:$(SER)
# all:$(CLI)
	@echo "make all"

# $^代表整个依赖列表
$(SER):$(SER_OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
	@# $(FIND_LIB) 
	@echo "Linking [ $^ ] to [ $@ ] ... done"

# $^代表整个依赖列表
$(CLI):$(CLI_OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS) -lcurses 
	@echo "Linking [ $^ ] to [ $@ ] ... done"

# $<代表依次取得
%.o:$(SERVER_PATH)/%.cpp
	@$(CC) -c $< $(FIND_INCLUDE)
	@echo "Compiling [ $< ] to [ $@ ] ... done"

# $<代表依次取得
%.o:$(CLIENT_PATH)/%.cpp
	@$(CC) -c $< $(FIND_INCLUDE) 
	@echo "Compiling [ $< ] to [ $@ ] ... done"

%.o:$(COMM_PATH)/%.cpp
	@$(CC) -c $< $(FIND_INCLUDE)
	@echo "Compiling [ $< ] to [ $@ ] ... done"

%.o:$(DATA_PATH)/%.cpp 
	@$(CC) -c $< $(FIND_INCLUDE)
	@echo "Compiling [ $< ] to [ $@ ] ... done"

%.o:$(WINDOW_PATH)/%.cpp 
	@$(CC) -c $< $(FIND_INCLUDE) -lcurses
	@echo "Compiling [ $< ] to [ $@ ] ... done"

.PHONY:debug
debug:
	@echo $(ROOT_PATH)
	@echo $(SER_SRC)
	@echo $(SER_OBJ)

.PHONY:clean
clean:
	@rm -rf $(SER) $(CLI) *.o output
	@echo "clean ... done"
.PHONY:output
output:
	@mkdir -p output/server
	@mkdir -p output/client
	@cp -rf log output/server
	@cp -rf conf output/client
	@cp -rf conf output/server

	@cp -f $(SER) output/server
	@cp -f $(CLI) output/client
	@cp plugin/ctl_server.sh output/server
	@cp plugin/ctl_client.sh output/client


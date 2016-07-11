ROOT_PATH=$(shell pwd)
SERVER_PATH=$(ROOT_PATH)/server
CLIENT_PATH=$(ROOT_PATH)/client
COMM_PATH=$(ROOT_PATH)/comm

DATA_PATH=$(ROOT_PATH)/data_pool

SER=udp_server
CLI=udp_client
CC=g++

FIND_INCLUDE=-I$(COMM_PATH) -I$(DATA_PATH)

SER_SRC=$(shell ls $(SERVER_PATH) | grep -E '*.cpp')
SER_SRC+=$(shell ls $(COMM_PATH) | grep -E '*.cpp')
SER_SRC+=$(shell ls $(DATA_PATH) | grep -E '*.cpp')
# tihuan
SER_OBJ=$(SER_SRC:.cpp=.o)

CLI_SRC=$(shell ls $(CLIENT_PATH) | grep -E '*.cpp')
CLI_SRC+=$(shell ls $(COMM_PATH) | grep -E '*.cpp')
CLI_OBJ=$(CLI_SRC:.cpp=.o)


.PHONY:all
all:$(SER) $(CLI)
# all:$(SER)
# all:$(CLI)
	@echo "make all"

# $^代表整个依赖列表
$(SER):$(SER_OBJ)
	@$(CC) -o $@ $^ -lpthread -ljson -g
	@echo "Linking [ $^ ] to [ $@ ] ... done"

# $^代表整个依赖列表
$(CLI):$(CLI_OBJ)
	@$(CC) -o $@ $^ -ljson -g
	@echo "Linking [ $^ ] to [ $@ ] ... done"

# $<代表依次取得
%.o:$(SERVER_PATH)/%.cpp
	@$(CC) -c $< $(FIND_INCLUDE) -ljson -g
	@echo "Compiling [ $< ] to [ $@ ] ... done"

# $<代表依次取得
%.o:$(CLIENT_PATH)/%.cpp
	@$(CC) -c $< $(FIND_INCLUDE) -ljson -g
	@echo "Compiling [ $< ] to [ $@ ] ... done"

%.o:$(COMM_PATH)/%.cpp
	@$(CC) -c $< $(FIND_INCLUDE) -ljson -g
	@echo "Compiling [ $< ] to [ $@ ] ... done"

%.o:$(DATA_PATH)/%.cpp 
	@$(CC) -c $< $(FIND_INCLUDE) -ljson -g
	@echo "Compiling [ $< ] to [ $@ ] ... done"

.PHONY:debug
debug:
	@echo $(ROOT_PATH)
	@echo $(SER_SRC)
	@echo $(SER_OBJ)

.PHONY:clean
clean:
	@rm -rf $(SER) $(CLI) *.o
	@echo "clean ... done"

CC = gcc
CFLAGS = -Wall

CLIENT_SRC_DIR = TCP_Client
SERVER_SRC_DIR = TCP_Server
TEST_SRC_DIR = HW7_20231

CLIENT_OBJ_DIR = $(CLIENT_SRC_DIR)/obj
SERVER_OBJ_DIR = $(SERVER_SRC_DIR)/obj
TEST_OBJ_DIR = $(TEST_SRC_DIR)/obj

CLIENT_SRC_FILES = $(wildcard $(CLIENT_SRC_DIR)/*.c)
CLIENT_OBJ_FILES = $(patsubst $(CLIENT_SRC_DIR)/%.c, $(CLIENT_OBJ_DIR)/%.o, $(CLIENT_SRC_FILES))

SERVER_SRC_FILES = $(wildcard $(SERVER_SRC_DIR)/*.c)
SERVER_OBJ_FILES = $(patsubst $(SERVER_SRC_DIR)/%.c, $(SERVER_OBJ_DIR)/%.o, $(SERVER_SRC_FILES))

TEST_SRC_FILES = $(wildcard $(TEST_SRC_DIR)/*.c)
TEST_OBJ_FILES = $(patsubst $(TEST_SRC_DIR)/%.c, $(TEST_OBJ_DIR)/%.o, $(TEST_SRC_FILES))

.PHONY: all clean

all: client server test

client: $(CLIENT_OBJ_FILES)
	$(CC) $^ -o $@

server: $(SERVER_OBJ_FILES)
	$(CC) $^ -o $@

test: $(TEST_OBJ_FILES)
	$(CC) $^ -o $@

$(CLIENT_OBJ_DIR)/%.o: $(CLIENT_SRC_DIR)/%.c
	@mkdir -p $(CLIENT_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVER_OBJ_DIR)/%.o: $(SERVER_SRC_DIR)/%.c
	@mkdir -p $(SERVER_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	@mkdir -p $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@	

clean:
	rm -rf $(CLIENT_OBJ_DIR) $(SERVER_OBJ_DIR) $(TEST_OBJ_DIR) client server test

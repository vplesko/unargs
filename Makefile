CC = clang

BIN_DIR = bin

BUILD_FLAGS = -std=c99 -Wall -Wextra -Wconversion -pedantic -Werror -I./ -O0 -g -fno-omit-frame-pointer
ifdef VC
	BUILD_FLAGS += -D_CRT_SECURE_NO_WARNINGS
endif

test: $(BIN_DIR)/tested.txt

$(BIN_DIR)/tested.txt: unargs.h $(wildcard test/*)
	@mkdir -p $(@D)
	$(CC) $(BUILD_FLAGS) test/test.c -o $(BIN_DIR)/test
	$(BIN_DIR)/test
	@touch $@

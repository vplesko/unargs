CC = clang

BIN_DIR = bin

BUILD_FLAGS = -std=c99 -Wall -Wextra -Wconversion -pedantic -Werror -I./ -O0 -g -fno-omit-frame-pointer
ifdef VC
	BUILD_FLAGS += -D_CRT_SECURE_NO_WARNINGS
endif

test: $(BIN_DIR)/tested.txt

# MSan and Valgrind don't work on Windows, so skip them in that case.
TEST_MSAN_PATH =
TEST_VALGRIND_CMD =
ifndef WIN
	TEST_MSAN_PATH = $(BIN_DIR)/test_msan
	TEST_VALGRIND_CMD = valgrind -q --leak-check=yes $(BIN_DIR)/test
endif

$(BIN_DIR)/tested.txt: $(BIN_DIR)/test $(BIN_DIR)/test_asan $(TEST_MSAN_PATH)
	$(BIN_DIR)/test
	$(BIN_DIR)/test_asan
	$(TEST_MSAN_PATH)
	$(TEST_VALGRIND_CMD)
	@touch $@

$(BIN_DIR)/test: unargs.h $(wildcard test/*)
	@mkdir -p $(@D)
	$(CC) $(BUILD_FLAGS) test/test.c -o $@

$(BIN_DIR)/test_asan: unargs.h $(wildcard test/*)
	@mkdir -p $(@D)
	$(CC) $(BUILD_FLAGS) -fsanitize=address,undefined test/test.c -o $@

$(BIN_DIR)/test_msan: unargs.h $(wildcard test/*)
	@mkdir -p $(@D)
	$(CC) $(BUILD_FLAGS) -fsanitize=memory -fsanitize-memory-track-origins -fPIE -pie test/test.c -o $@

clean:
	rm -rf $(BIN_DIR)

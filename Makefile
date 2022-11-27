CC = gcc
DEV_CFLAGS = -Wall -g -fsanitize=address
RELEASE_CFLAGS = -Wall -g -O2 -shared

MKDIR_P ?= mkdir -p
BUILD_DIR ?= ./build

DEV_TARGET=$(BUILD_DIR)/test_neostring
RELEASE_TARGET=$(BUILD_DIR)/libneostring.so
TESTS_TARGET=$(BUILD_DIR)/tests

dev: $(DEV_TARGET)
release: clean $(RELEASE_TARGET)
tests: $(TESTS_TARGET)

$(DEV_TARGET): src/neostring.c src/main.c
	$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(DEV_CFLAGS) src/neostring.c src/main.c -g -o $@ 

$(RELEASE_TARGET): src/neostring.c
	$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(RELEASE_CFLAGS) src/neostring.c -o $@ 

install: release 
	sudo cp ./src/neostring.h /usr/include 
	sudo cp ./build/libneostring.so /usr/lib

$(TESTS_TARGET): src/tests.c ./src/neostring.c
	$(MKDIR_P) $(BUILD_DIR)
	$(CC) src/tests.c ./src/neostring.c -Wall -g -o  $@ 


.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

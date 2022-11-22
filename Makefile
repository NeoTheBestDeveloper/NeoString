CC = clang
DEV_CFLAGS = -Wall -g
RELEASE_CFLAGS = -Wall -O2 -shared

MKDIR_P ?= mkdir -p
BUILD_DIR ?= ./build

DEV_TARGET=$(BUILD_DIR)/test_neostring
RELEASE_TARGET=$(BUILD_DIR)/libneostring.so

dev: $(DEV_TARGET)
release: clean $(RELEASE_TARGET)

$(DEV_TARGET): src/neostring.c src/main.c
	$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(DEV_CFLAGS) src/neostring.c src/main.c -o $@ 

$(RELEASE_TARGET): src/neostring.c
	$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(RELEASE_CFLAGS) src/neostring.c -o $@ 

install: release 
	sudo cp ./src/neostring.h /usr/include 
	sudo cp ./build/libneostring.so /usr/lib


.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

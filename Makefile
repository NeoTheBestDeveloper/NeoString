CC = clang
DEV_CFLAGS = -Wall -g
RELEASE_CFLAGS = -Wall -O2 -shared

MKDIR_P ?= mkdir -p
BUILD_DIR ?= ./build

DEV_TARGET=$(BUILD_DIR)/test_dynstr
RELEASE_TARGET=$(BUILD_DIR)/libdynstr.so

dev: $(DEV_TARGET)
release: clean $(RELEASE_TARGET)

$(DEV_TARGET): src/dyn_str.c src/main.c
	$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(DEV_CFLAGS) src/dyn_str.c src/main.c -o $@ 

$(RELEASE_TARGET): src/dyn_str.c
	$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(RELEASE_CFLAGS) src/dyn_str.c -o $@ 


.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

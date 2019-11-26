ifeq ($(CC),)
	CC := clang
endif

ifeq ($(CXX),)
	CXX := clang++
endif

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

ifeq ($(BUILD_DIR),)
	BUILD_DIR := build
endif

ifeq ($(OBJ_DIR),)
	OBJ_DIR = obj
endif

BINARY := piyo-piyo
HEADER_DIR := piyo-piyo
OBJS := Window.o Engine.o main.o
OBJS_C :=

ifeq ($(OS),Windows_NT)

else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		ifneq ($(WAYLAND_DISPLAY),)
			CCFLAGS += -D__WAYLAND
		else
			LIB += -lX11 -lGLX -lGL
		endif
	else ifeq ($(UNAME_S),Darwin)

	endif
endif

output: $(OBJS_C) $(OBJS)
	@mkdir -p $(BUILD_DIR)
	cd $(OBJ_DIR); $(CXX) $(CCFLAGS) -Wall -o ../$(BUILD_DIR)/$(BINARY) $(LIB) $(OBJS_C) $(OBJS)

$(OBJS_C): %.o: %.c
	@mkdir -p ${OBJ_DIR}
	cd $(OBJ_DIR); $(CC) $(CFLAGS) -Wall -c ../$<

$(OBJS): %.o: %.cpp
	@mkdir -p ${OBJ_DIR}
	cd $(OBJ_DIR); $(CXX) $(CCFLAGS) -Wall -std=c++14 -c ../$<

run:
	$(BUILD_DIR)/$(BINARY)

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

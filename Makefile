OUTPUT	:= Szczur
PARAMS	:=
ARCH	:= 32

ifdef EDITOR
_EDITOR	:= -DSZCZUR_EDITOR
endif

CC		:= g++
CFLAGS	:= -Iinclude -std=c++11 -O -g -rdynamic $(_EDITOR)
LFLAGS	:= -lsfml-system -lsfml-window -lsfml-graphics -ldl -g -rdynamic

OBJS_32	:= $(patsubst src/%.cpp, obj_32/%.o, $(shell find src -type f -name '*.cpp'))
OBJS_64	:= $(patsubst src/%.cpp, obj_64/%.o, $(shell find src -type f -name '*.cpp'))
HEADERS	:= $(shell find include -type f)
DIRS_32	:= $(patsubst src/%, obj_32/%, $(sort $(shell find src/* -type d)))
DIRS_64	:= $(patsubst src/%, obj_64/%, $(sort $(shell find src/* -type d)))

default: $(ARCH)
32: dirs32 out/$(OUTPUT)_32bit
64: dirs64 out/$(OUTPUT)_64bit
all: 32 64

dirs32: $(DIRS_32)
dirs64: $(DIRS_64)

run: $(ARCH)
	@(cd out && ./$(OUTPUT)_$(ARCH)bit $(PARAMS)) 2>&1 | c++filt
	
run32: 32
	@(cd out && ./$(OUTPUT)_32bit $(PARAMS))

run64: 64
	@(cd out && ./$(OUTPUT)_64bit $(PARAMS))

out/$(OUTPUT)_32bit: $(OBJS_32)
	$(CC) $(OBJS_32) -o $@ $(LFLAGS) -m32
	
out/$(OUTPUT)_64bit: $(OBJS_64)
	$(CC) $(OBJS_64) -o $@ $(LFLAGS) -m64

$(OBJS_32): obj_32/%.o: src/%.cpp $(HEADERS)
	$(CC) -c $< -o $@ $(CFLAGS) -m32

$(OBJS_64): obj_64/%.o: src/%.cpp $(HEADERS)
	$(CC) -c $< -o $@ $(CFLAGS) -m64

$(DIRS_32): obj_32/%: src/%
	@if [ ! -e "$@" ]; then mkdir -p $@; fi

$(DIRS_64): obj_64/%: src/%
	@if [ ! -e "$@" ]; then mkdir -p $@; fi

obj_32:
	@mkdir obj_32
	
obj_64:
	@mkdir obj_64

clean: clean32 clean64

clean32:
	@if [ -e obj_32 ]; then find obj_32; rm -rf obj_32; fi
	@if [ -e out/Szczur_32bit ]; then echo ./out/Szczur_32bit; rm -rf out/Szczur_32bit; fi
	
clean64:
	@if [ -e obj_64 ]; then find obj_64; rm -rf obj_64; fi
	@if [ -e out/Szczur_64bit ]; then echo ./out/Szczur_64bit; rm -rf out/Szczur_64bit; fi


OUTPUT	:= Szczur
PARAMS	:=
ARCH	:= 32

CC		:= g++
CFLAGS	:= -Iinclude -Iinclude/Windows -std=c++11
LFLAGS	:= -lsfml-system -lsfml-window -lsfml-graphics


OBJS_32	:= $(patsubst src/%.cpp, obj_32/%.o, $(wildcard src/*.cpp)) $(patsubst src/%.cpp, obj_32/%.o, $(wildcard src/*/*.cpp))
OBJS_64	:= $(patsubst src/%.cpp, obj_64/%.o, $(wildcard src/*.cpp)) $(patsubst src/%.cpp, obj_64/%.o, $(wildcard src/*/*.cpp))
HEADERS	:= $(wildcard include/*.h) $(wildcard include/*/*.h)
DIRS_32	:= $(patsubst src/%, obj_32/%, $(sort $(dir $(wildcard src/*/*))))
DIRS_64	:= $(patsubst src/%, obj_64/%, $(sort $(dir $(wildcard src/*/*))))

default: $(ARCH)
32: dirs32 out/$(OUTPUT)_32bit
64: dirs64 out/$(OUTPUT)_64bit
all: 32 64

dirs32: $(DIRS_32)
dirs64: $(DIRS_64)

run: $(ARCH)
	@(cd out && ./$(OUTPUT)_$(ARCH)bit $(PARAMS))
	
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

$(DIRS_32): obj_32/%: obj_32
	@if [ ! -e "$@" ]; then mkdir $@; fi

$(DIRS_64): obj_64/%: obj_64
	@if [ ! -e "$@" ]; then mkdir $@; fi

obj_32:
	@mkdir obj_32
	
obj_64:
	@mkdir obj_64

clean: clean32 clean64

clean32:
	@if [ -e obj_32 ]; then find obj_32; rm -rf obj_32; fi
	
clean64:
	@if [ -e obj_64 ]; then find obj_64; rm -rf obj_64; fi


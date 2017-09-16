OBJS	:= $(patsubst %.cpp, %.o, $(wildcard *.cpp))
CC		:= g++
CFLAGS	:= -I../../include -std=c++11 -O -m32 -fPIC
LFLAGS	:= -L../module -lszczur -m32 -shared

OUTPUT	:= menu


all: ../../out/Modules/$(OUTPUT).so
../../out/Modules/$(OUTPUT).so: $(OUTPUT).so
	cp $< $@

$(OUTPUT).so: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LFLAGS)

$(OBJS): %.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o
	rm -f $(OUTPUT).so


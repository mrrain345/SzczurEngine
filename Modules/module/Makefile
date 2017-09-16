OBJS	:= Color.o Hash.o Rect.o Vector2.o Window.o WindowContent.o
CC		:= g++
AR		:= ar
CFLAGS	:= -I../../include -std=c++11 -O -m32 -fPIC

_OBJS	:= $(patsubst %.o, ../../obj_32/Szczur/%.o, $(OBJS))


libszczur.a: module.o $(_OBJS)
	$(AR) rcs $@ $<

module.o: module.cpp
	$(CC) -c module.cpp -o $@ $(CFLAGS)

clean:
	rm -f module.o
	rm -f libszczur.a

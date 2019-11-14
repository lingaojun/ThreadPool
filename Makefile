CXXFILES := main.cpp  
OBJS :=
TARGET := lingjThreadPool

CC := g++
LIBS := -lpthread
LDFLAGS := -L.
DEFINES :=
INCLUDE := -I ./
CFLAGS :=
CXXFLAGS := -std=c++11

all:
	$(CC) $(CXXFILES) $(INCLUDE) $(LDFLAGS)  $(LIBS) $(CXXFLAGS) -o $(TARGET)
clean:
	rm -rf *.o
	rm -rf $(TARGET)




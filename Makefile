LIB := -lprotobuf -lprotoc -lpthread  -lstdc++ -lc  
WARNINGS := -Wall -Wcast-qual -Wsign-compare
MACROS := -DMFP_EPOLL -DSYSEPOLL  -D_LARGEFILE_SOURCE
CFLAGS= -g ${WARNINGS}  ${MACROS}  

CC=g++ $(CFLAGS)

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJS = $(SOURCES:%.cc=objs/%.o)


BIN= rpc_generator

all: ${BIN}

$(OBJS): objs/%.o: %.cpp $(HEADERS)
	@mkdir -p objs
	$(CC) -c $< -o $@ 

rpc_generator: $(OBJS)
	${CC} ${CFLAGS} -o $@ $^  ${LIB}
clean:
	rm -f $(OBJS) ${BIN}

INC :=  
LIBDIRS =
LIB := -lprotobuf -lprotoc -lpthread  -lstdc++ -lc  


SHAREDLIB =
WARNINGS := -Wall -Wcast-qual -Wsign-compare
MACROS := -DMFP_EPOLL -DSYSEPOLL  -D_LARGEFILE_SOURCE
CFLAGS= -g ${WARNINGS}  ${MACROS}  

CC=g++ $(CFLAGS)

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
RELOBJFILES = $(SOURCES:%.cc=objs/%.o)

EXTLIBS= 

BIN= rpc_generator

all: ${BIN}

$(RELOBJFILES): objs/%.o: %.cpp $(HEADERS)
	@mkdir -p objs
	$(CC) -c $< -o $@ $(INC)

rpc_generator: $(RELOBJFILES)
	${CC} ${CFLAGS} ${INC} $(LIBDIRS)  -o $@ $^ $(SHAREDLIB) ${LIB} ${EXTLIBS}
clean:
	rm -f $(RELOBJFILES) ${BIN}

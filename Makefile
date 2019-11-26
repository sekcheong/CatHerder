UNAME := $(shell uname)

DEBUG=0

SLIB=lib739kv.so

VPATH=./src/:./testing

OBJDIR=./obj/


CC=gcc

CPP=g++ -std=c++11

OPTS=-Ofast

LDFLAGS= -lm -pthread -ldl

COMMON= -Iinclude/ -Isrc/

CFLAGS=-Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC

# CFLAGS_PYTHON = `pkg-config --cflags python3`

# LDFLAGS_PYTHON = `pkg-config --libs python3`

ifeq ($(DEBUG), 1)
	OPTS=-O0 -g
else
	OPTS=-Ofast -DNDEBUG
endif


#for MacOS clang we need to add libc++
ifeq ($(UNAME),Darwin)
	CPP += -stdlib=libc++
endif


CFLAGS+=$(OPTS)


#list of objects to build
OBJ=	sqlite3.o \
	    debug.o \
		sqlstatement.o \
		datastore.o \
		message.o \
		dsserver.o \
		dsclient.o \
		lib739kv.o \
		rpcclient.o \
		rpcserver.o \


#list of executable to build
EXEC =  test \
# 		server_test \
# 		client_test \
# 		api_test \
# 		test_speed \
# 		kvdaemon \
# 		rpcc \
# 		rpcs \


EXECOBJA = $(addprefix $(OBJDIR), $(EXEC))

EXECOBJ = $(addsuffix .o, $(EXECOBJA))

OBJS = $(addprefix $(OBJDIR), $(OBJ))

DEPS = $(wildcard src/*.h) Makefile 


#build etags only if the command exist
ifneq (, $(shell which etags))
	ETAGS = TAGS
endif

all: obj $(EXECOBJ) $(EXEC) 

# $(SLIB): $(OBJS)
# 	$(CPP) $(CFLAGS) -shared $^ -o $@ $(LDFLAGS)

$(OBJDIR)%.o: %.cpp $(DEPS)
	$(CPP) $(COMMON) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: %.c $(DEPS)
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

$(EXEC): $(EXECOBJ) 
	$(CPP) $(COMMON) $(CFLAGS) $(OBJDIR)$@.o -o $@ $(LDFLAGS) $(SLIB)

obj:
	mkdir -p obj

.PHONY: clean

clean:
	rm -rf $(OBJS) $(SLIB) $(EXEC) $(EXECOBJ) $(OBJDIR) $(TESTFILES) ./testing/*.so kvs.so TAGS ./testing/basic_server.py ./testing/kvlib.py ./testing/server_manager.py ./testing/test1.py ./testing/withsqlite.py ./testing/__pycache__

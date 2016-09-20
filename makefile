CXXOBJ= xRedisServerLib.o
COBJ = sds.o

server: $(COBJ) $(CXXOBJ)
	g++ -shared  -o libxredis_server.so  $(COBJ) $(CXXOBJ) -fPIC
	ar -rc  -o libxredis_server.a  $(COBJ) $(CXXOBJ)

$(CXXOBJ): %.o : src/%.cpp
	g++ -c $< -o $@ -D__STDC_FORMAT_MACROS -fPIC

$(COBJ) : %.o : src/%.c
	gcc -c $< -o $@ -fPIC

clean:
	rm -rf *.o libxredis_server.so libxredis_server.a example/*.o xRedisServer

example: example/xRedisServer.o
	g++ -o xRedisServer example/xRedisServer.cpp -I./src -levent -lxredis_server -L./




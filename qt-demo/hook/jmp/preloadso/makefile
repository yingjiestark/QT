preloadso.so:clean
	g++ -o preloadso.so -shared -fPIC preloadso.c common.cc common.h
clean:
	rm -rf preloadso.so


install:
	rm -rf ../main/preloadso.so
	cp preloadso.so ../main/
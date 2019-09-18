src=$(wildcard *.cpp)
obj=$(src:.cpp=.o)

main:$(obj)
	g++ -std=c++11 $(obj) -o main -lhdf5 -lhdf5_cpp

.PHONY: clean
clean:
	rm -f $(obj) main

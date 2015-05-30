life: main.o TheLife.o
	g++ -g -o $@ $^

%.o: %.cpp
	g++ -std=c++11 -g -c -o $@ $<

clean:
	rm -f *.o
	rm -f life

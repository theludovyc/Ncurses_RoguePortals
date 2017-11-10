a.out:
	g++ main.c -lncurses

clean:
	rm -rf *.o
	rm -rf a.out

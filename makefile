screlex:
	gcc main.c -o bright

install: screli
	cp screli ${HOME}/.local/bin

clean:
	rm ./bright

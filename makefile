screli:
	gcc main.c -o screli

install: screli
	cp screli ${HOME}/.local/bin

clean:
	rm ./screli

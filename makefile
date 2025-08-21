screlex:
	gcc main.c -o bright

install: screli
	cp bright ${HOME}/.local/bin


uninstall:
	rm ${HOME}/.local/bin/bright

clean:
	rm ./bright

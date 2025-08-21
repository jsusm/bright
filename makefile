bright:
	gcc main.c -o bright

install: bright
	cp bright ${HOME}/.local/bin


uninstall:
	rm ${HOME}/.local/bin/bright

clean:
	rm ./bright

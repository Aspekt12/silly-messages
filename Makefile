build-and-run:
	gcc -o server.elf server.c -Wall
	gcc -o client.elf client.c -Wall
	konsole& -e ./server.elf
	konsole& -e ./client.elf
build:
	gcc -o server.elf server.c -Wall
	gcc -o client.elf client.c -Wall
run:
	konsole& -e ./server.elf
	konsole& -e ./client.elf
clean:
	rm server.elf
	rm client.elf

all:
	gcc -pthread game.c terminal_settings.c mapper.c highlander.c && ./a.out

clear:
	rm a.out

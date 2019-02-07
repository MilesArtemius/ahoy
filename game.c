#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include "mapper.h"
#include "terminal_settings.h"
#include "highlander.h"

void* main_thread(void* cmd);

int main() {
	int command = 'p';

	pthread_t mainThread;
        pthread_create(&mainThread, NULL, main_thread, &command);

	while (command != 'Q') {
		command = getchar();
	}

	pthread_join(mainThread, NULL);

    	return 0;
}

void milli_sleep(int millis) {
	struct timespec ts;
	ts.tv_sec = millis / 1000;
	ts.tv_nsec = (millis % 1000) * 1000000;
	nanosleep(&ts, NULL);
}

void* main_thread(void* cmd) {
	int* command = (int*) cmd;

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	int sWidth, sHeight;
	sWidth = w.ws_row; // NB that the last symbol will be '/n'
	sHeight = w.ws_col;
	char** all = create(sWidth, sHeight);

	disable_waiting_for_enter();

    	/* FPS loop */
	int FPScounter = 0;
    	while (1) {
		if (*command == 'Q') break;
		/* getting action argument */
		int action = *command;
		*command = 'p';

		milli_sleep(50);
        	system("clear");

		// game logic
		fill(&all, sWidth, sHeight, FPScounter++);

		// drawing
		for (int i = 0; i < sHeight-1; i++) {
			printf("%s", all[i]);
		}

		if (FPScounter > 128) FPScounter = 0;
    	}

    	restore_terminal_settings();
	system("clear");
	return NULL;
}

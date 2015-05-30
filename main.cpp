#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <sys/ioctl.h>
#include <getopt.h>
#include <string.h>
#include "TheLife.h"


int main(int argc, char** argv) {
	char *fileName = NULL;
	int width = 0, height = 0;
	bool manual = false;
	bool random = true;
	int step = 50000;


	struct option long_options[] = {
		{"file", required_argument, 0, 'f'},
		{"width", required_argument, 0, 'w'},
		{"height", required_argument, 0, 'h'},
		{"manual", optional_argument, 0, 'm'},
		{"random", optional_argument, 0, 'r'},
		{"step", required_argument, 0, 't'},
		{NULL, 0, NULL, 0}
	};

	int option_index = 0;
	int c;
	while ((c = getopt_long(argc, argv, "f:w:h:mrt:", long_options, &option_index)) != -1) {
		switch(c) {
			case 'f':
				fileName = optarg;
				break;

			case 'w':
				width = atoi(optarg);
				break;

			case 'h':
				height = atoi(optarg);
				break;

			case 'm':
				manual = true;
				break;

			case 'r':
				random = true;
				break;

			case 't':
				step = atoi(optarg) * 1000;
				break;
		}
	}

	if(width == 0 || height == 0) {
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);

		if(width == 0) {
			width = w.ws_col - 2;
		}

		if(height == 0) {
			height = w.ws_row - 3;
		}
	}

	TheLife life(width, height);

	if(fileName) {
		FILE* f = fopen(fileName, "r");
		if(f == NULL) {
			printf("Failed to open file");
			return 1;
		}

		int x = 0, y = 0;
		char c;
		while(fscanf(f, "%c", &c) == 1) {
			if(c == '\n') {
				x = 0;
				y++;
			}

			if(c == '1') {
				life.setLive(x, y);
			}

			x++;
		}
	} else if(random) {
		life.generate();
	}

	life.render();

	while(1) {
		if(manual) {
			getchar();
		} else {
			usleep(step);
		}

		life.step();
		life.render();
	}
}
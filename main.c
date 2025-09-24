#include <pcl.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 20

int main(void) {
	struct Console* console = start();

	char plane[HEIGHT][WIDTH];

	srand(time(NULL));
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			int r = rand() % 2;
			if (r == 0) {
				plane[i][j] = '.';
			}
			else {
				plane[i][j] = '.';
			}
		}
	}
/*
	// glider
	plane[1][0] = '#';
	plane[2][1] = '#';
	plane[0][2] = '#';
	plane[1][2] = '#';
	plane[2][2] = '#';
*/
	int generations = 0;
	int menusize = 1;
	int sleep = 100;

	while (1) {
		clear(console);

		setstringformatted(console, "Generation: %d | speed: %d | space => pause/enter insert mode", generations, sleep);

		char input = getchr(console);
		if (input == 'q') {
			break;
		}


		switch (input) {
			case '+': {
				if (sleep == 300)
					break;
				sleep += 10;
				break;
			}
			case '-': {
				if (sleep == 0)
					break;
				sleep -= 10;
				break;
			}
			default: break;
		}


		if (input == ' ') {
			int posrow = 0, poscol = 0;
			while (1) {
				clear(console);
				setstringformatted(console, "Generation: %d | space => start/enter view mode", generations);

				input = getchr(console);
				if (input == ' ') {
					break;
				}

				switch (input) {
					case 'w': {
						if (posrow == 0)
							break;
						posrow--;
						break;
					}
					case 'a': {
						if (poscol == 0)
							break;
						poscol--;
						break;
					}
					case 's': {
						if (posrow == HEIGHT - 1)
							break;
						posrow++;
						break;
					}
					case 'd': {
						if (poscol == WIDTH - 1)
							break;
						poscol++;
						break;
					}
					case 'r': {
						for (int i = 0; i < HEIGHT; i++) {
							for (int j = 0; j < WIDTH; j++) {
								int r = rand() % 2;
								if (r == 0) {
									plane[i][j] = '.';
								}
								else {
									plane[i][j] = '#';
								}
							}
						}
						break;
					}
					case 'e': {
						plane[posrow][poscol] = '#';
						break;
					}
					default: break;
				}

				set2darray(console, (const char*)plane, 0 + menusize, 0, WIDTH, HEIGHT);

				setcharcursor(console, '@', posrow + menusize, poscol);

				refresh(console);
			}
		}

		char new[HEIGHT][WIDTH];
		for (int i = 0; i < HEIGHT; ++i) {
			for (int j = 0; j < WIDTH; ++j) {
				new[i][j] = '.';
				int neighbours = 0;

				for (int k = -1; k <= 1; ++k) {
					for (int l = -1; l <= 1; ++l) {
						if (k == 0 && l == 0)
							continue;

						int row = (i + k + HEIGHT) % HEIGHT;
						int col = (j + l + WIDTH) % WIDTH;

						if (plane[row][col] == '#') {
							neighbours++;
						}
					}
				}

				if (plane[i][j] == '.' && neighbours == 3) {
					new[i][j] = '#';
				}
				else if (plane[i][j] == '#' && (neighbours == 2 || neighbours == 3)) {
					new[i][j] = '#';
				}
			}
		}

		set2darray(console, (const char*)plane, 0 + menusize, 0, WIDTH, HEIGHT);

		memcpy(plane, new, WIDTH * HEIGHT * sizeof(char));

		generations++;
		refresh(console);
		_sleep(sleep);
	}

	end(console);
	return 0;
}

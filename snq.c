/* See LICENSE for details*/
/* snq: Simple N Queen solver*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIDE 8


int
queenattacks(int *way, int k) {
	int i;

	for (i = 0; i < k; i++) {
		if ((way[i] == way[k]) || (abs(way[i] - way[k]) == (k-i))) {
			return 0;
		}
	}
	return 1;
}


void
snqt(FILE* f, int* way, int k, int n) {
	int i;

	if (k == n) {
		for (i = 0; i < n; i++) {
			fprintf(f, "%d", way[i]);
		}
		fprintf(f, "\n");
		return;
	}

	for (i = 0; i < n; i++) {
		way[k] = i;
		if (queenattacks(way, k)) {
			snqt(f, way, k + 1, n);
		}
	}

}

void
snq(FILE* f, int* way, int n) {
	int i;

	for (i = 0; i < n; i++) {
		way[0] = i;
		snqt(f, way, 1, n);
	}
}

void
usage(void) {
	fprintf(stdout, "snq is a simple N-Queen Problem solver.\n");
	fprintf(stdout, "Usage: snq [OPTIONS] SIZE_OF_SIDE(1-8)\n\n");

	fprintf(stdout, "Options:\n");
	fprintf(stdout, "    -h,--help   -- display help and exit\n");
	fprintf(stdout, "    --version   -- display version and exit\n");
	fprintf(stdout, "    -o [FILE]   -- output to file\n\n");

	fprintf(stdout, "Examples:\n");
	fprintf(stdout, "snq 4           -- solve 4x4 board\n\n");
	fprintf(stdout, "snq -o out 8    -- solve 8x8 board, output to out\n\n");

	fprintf(stdout, "Report bugs to <cpmachado@protonmail.com> or\n");
	fprintf(stdout, "file a issue at https://github.com/cpmachado/cpa\n");
}

void
version(void) {
	fprintf(stdout, "snq " VERSION "\n");
	fprintf(stdout, "Copyright (C) 2019 Carlos Pinto Machado\n");
	fprintf(stdout, "Written by Carlos A. Pinto Machado\n");
}

int
main(int argc, char *argv[]) {
	int c;
	FILE *f = stdout;
	int way[MAXSIDE] = {0};
	int n = 0;

	while (--argc > 0 && (*++argv)[0] ==  '-') {
		while ((c = *++argv[0])) {
			switch (c) {
				case 'o':
					++argv;
					--argc;
					if (!(f = fopen(*argv, "w"))) {
						fprintf(stderr, "Failed to open %s\n", *argv);
						exit(1);
					}
					break;
				case 'h':
					usage();
					exit(0);
					/* FALLTHROUGH */
				case '-':
					if (!strcmp("-help", *argv)) {
						usage();
						exit(0);
					}
					if (!strcmp("-version", *argv)) {
						version();
						exit(0);
					}
					/* FALLTHROUGH */
				default:
					usage();
					exit(1);
			}
			if (f != stdout) {
				break;
			}
		}
	}

	if (argc != 1) {
		usage();
		exit(1);
	}

	n = atoi(*argv);
	if (n < 1 || n > 8) {
		usage();
		exit(1);
	}

	snq(f, way, n);

	fclose(f);
	return 0;
}


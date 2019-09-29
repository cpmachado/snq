/* See LICENSE for details*/
/* snq: Simple N Queen solver*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void
usage(void) {
	fprintf(stdout, "snq is a simple N-Queen Problem solver.\n");
	fprintf(stdout, "Usage: snq [OPTIONS] SIZE_OF_SIDE\n\n");

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
	fprintf(stdout, "snq " VERSION "\n\n");
	fprintf(stdout, "Copyright (C) 2019 Carlos Pinto Machado\n\n");
	fprintf(stdout, "Written by Carlos A. Pinto Machado\n");
}

int
main(int argc, char *argv[]) {
	int c;
	FILE *out = stdout;

	while (--argc > 0 && (*++argv)[0] ==  '-') {
		while ((c = *++argv[0])) {
			switch (c) {
				case 'o':
					++argv;
					if (!(out = fopen(*argv, "w"))) {
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
			if (out != stdout) {
				break;
			}
		}
	}

	if (argc != 1) {
		usage();
		exit(1);
	}

	fclose(out);
	return 0;
}


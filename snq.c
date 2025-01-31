/* See LICENSE for details*/
/* snq: Simple N Queen solver*/
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef VERSION
#define VERSION "unknown"
#endif

#define MAXSIDE 8

extern int errno;
extern char *optarg;

void usage(void);

void version(void);

int queenattacks(int *way, int k);

void snqt(FILE *f, int *way, int k, int n);

void snq(FILE *f, int *way, int n);

int main(int argc, char *argv[]) {
  FILE *f = NULL;
  int way[MAXSIDE] = {0};
  int64_t n = 0;
  int opt;

  while ((opt = getopt(argc, argv, "hvn:o:")) != -1) {
    switch (opt) {
    case 'h':
      usage();
      exit(0);
    case 'v':
      version();
      exit(0);
    case 'n':
      n = strtoll(optarg, NULL, 10);
      if (errno) {
        fprintf(stderr, "%s\n", strerror(errno));
        usage();
        exit(1);
      }
      if (n < 1 || n > 8) {
        fprintf(stderr, "Number should be in [1, 8]\n");
        exit(1);
      }
      break;
    case 'o':
      if (f) {
        fprintf(stderr, "Output file was already set\n");
        fclose(f);
        exit(1);
      }
      if (!(f = fopen(optarg, "w"))) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
      }
      break;
    default:
      usage();
      exit(1);
    }
  }

  if (!f) {
    f = stdout;
  }

  if (!n) {
    n = 8;
  }

  snq(f, way, n);

  fclose(f);
  return 0;
}

void usage(void) {
  fprintf(stdout, "snq is a simple N-Queen Problem solver.\n");
  fprintf(stdout, "Usage: snq [OPTIONS]\n\n");

  fprintf(stdout, "Options:\n");
  fprintf(stdout, "    -h          -- display help and exit\n");
  fprintf(stdout, "    -v          -- display version and exit\n");
  fprintf(stdout, "    -n [NUMBER] -- Length of side(defaults to 8, should be "
                  "in [1, 8])\n");
  fprintf(stdout, "    -o [FILE]   -- output to file(defaults to stdout)\n");
}

void version(void) {
  fprintf(stdout, "snq-" VERSION " Copyright (C) 2019 Carlos Pinto Machado\n");
}

int queenattacks(int *way, int k) {
  int i;

  for (i = 0; i < k; i++) {
    if ((way[i] == way[k]) || (abs(way[i] - way[k]) == (k - i))) {
      return 0;
    }
  }
  return 1;
}

void snqt(FILE *f, int *way, int k, int n) {
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

void snq(FILE *f, int *way, int n) {
  int i;

  for (i = 0; i < n; i++) {
    way[0] = i;
    snqt(f, way, 1, n);
  }
}

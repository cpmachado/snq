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

#define MAXSIDE 8L

extern int errno;
extern char *optarg;

/* usage: Prints usage */
void usage(void);

/* version: Prints version */
void version(void);

/* valid_position: returns if position is valid, which means that queens aren't
 * atacking each other
 */
int valid_position(int64_t *way, int k);

/* snq: Checks and prints solutions for puzzle given a 'n' side chess board,
 * for given step k of combination
 */
void snq(FILE *f, int64_t *way, int k, int n);

int main(int argc, char *argv[]) {
  FILE *f = NULL;
  int64_t way[MAXSIDE] = {0};
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
      n = strtol(optarg, NULL, 10);
      if (errno) {
        fprintf(stderr, "%s\n", strerror(errno));
        usage();
        exit(1);
      }
      if (n < 1 || n > MAXSIDE) {
        fprintf(stderr, "Number should be in [1, %ld]\n", MAXSIDE);
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
    n = MAXSIDE;
  }

  snq(f, way, 0, n);

  fclose(f);
  return 0;
}

void usage(void) {
  fprintf(stdout, "snq is a simple N-Queen Problem solver.\n"
                  "Usage: snq [OPTIONS]\n\n"

                  "Options:\n"
                  "    -h          -- display help and exit\n"
                  "    -v          -- display version and exit\n"
                  "    -n [NUMBER] -- Length of side(defaults to 8, should be "
                  "in [1, 8])\n"
                  "    -o [FILE]   -- output to file(defaults to stdout)\n");
}

void version(void) {
  fprintf(stdout, "snq-" VERSION " Copyright (C) 2019 Carlos Pinto Machado\n");
}

int valid_position(int64_t *way, int k) {
  int i;
  int64_t d;

  for (i = 0; i < k; i++) {
    d = labs(way[i] - way[k]);
    if ((way[i] == way[k]) || d == (k - i)) {
      return 0;
    }
  }
  return 1;
}

void print_solution(FILE *f, int64_t *way, int n) {
  int i;
  for (i = 0; i < n; i++) {
    fprintf(f, "%ld", way[i]);
  }
  fprintf(f, "\n");
}

void snq(FILE *f, int64_t *way, int k, int n) {
  int i;

  if (k == n) {
    print_solution(f, way, n);
    return;
  }

  for (i = 0; i < n; i++) {
    way[k] = i;
    if (valid_position(way, k)) {
      snq(f, way, k + 1, n);
    }
  }
}

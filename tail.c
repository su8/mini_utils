/*
Copyright 08/25/2024 https://github.com/su8
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static void read_from_stdin(void);

static char *filename = "/tmp/tail3c5glqe92xns3128njrdtdsrdl234";

int main(int argc, char *argv[]) {
  char *buf = NULL, *tok = NULL, *filenam2 = NULL;
  char *ptrtofree = buf;
  char **arr;
  size_t dummy = 0, fz = 0;
  int fd = 0;
  long int iters = 0, x = 0, z = 0, y = 0;
  FILE *fp = NULL;
  off_t file_size = 0;
  struct stat st;

  if (1 == argc) {
    fprintf(stderr, "%s\n", "Missing argument(s)");
    return EXIT_FAILURE;
  }

  iters = atol(argv[1]);

  if (2 == argc) {
    read_from_stdin();
  }

  filenam2 = 2 == argc ? filename : argv[2];
  if (-1 == (fd = open(filenam2, O_RDONLY))) {
    fprintf(stderr, "%s\n", "open() failed");
    return EXIT_FAILURE;
  }
  if (NULL == (fp = fdopen(fd, "r"))) {
    fprintf(stderr, "%s\n", "fdopen() failed");
    goto err;
  }

  if (0 != (fstat(fd, &st)) || (!S_ISREG(st.st_mode))) {
    fprintf(stderr, "%s\n", "The program operates only on filename(s)");
    goto err;
  }

  if (0 != fseeko(fp, 0, SEEK_END)) {
    fprintf(stderr, "%s\n", "fseeko() failed");
    goto err;
  }
  if (-1 == (file_size = ftello(fp))) {
    fprintf(stderr, "%s\n", "ftello() failed");
    goto err;
  }
  rewind(fp);
  
  fz = (size_t)file_size;

  buf = (char *)(malloc(fz));
  if (NULL == buf) {
    fprintf(stderr, "%s\n", "malloc() failed");
    goto err;
  }
  
  dummy = fread(buf, 1, fz, fp);
  (void)dummy;

  arr = (char **)malloc(fz);
  while ((tok = strsep(&buf, "\n"))) {
    arr[x++] = tok;
  }
  x--;
  x--;

  for (y = x; x >= 0; x--) {
    if (arr[x]) {
      if (y-iters == x) {
        for (z = y-iters; z < y;z++) {
          puts(arr[z]);
        }
        break;
      }
    }
  }

err:
  close(fd);
  if (NULL != fp) {
    fclose(fp);
  }
  if (NULL != ptrtofree) {
    free(ptrtofree);
  }
  if (NULL != arr[0]) {
    free(arr);
  }
  remove(filename);

  return EXIT_SUCCESS;
}

static void 
read_from_stdin(void) {
  char buf[256] = {'\0'};
  size_t dummy = 0;
  FILE *fp = NULL;

  if (NULL != (fp = fopen(filename, "w"))) {
    while (0 != (dummy = fread(buf, 1, 255, stdin))) {
      buf[dummy] = '\0';
      fprintf(fp, "%s", buf);
    }
  }
  
  if (EOF == (fclose(fp))) {
    fprintf(stderr, "%s\n", "fclose() failed");
    exit(EXIT_FAILURE);
  }
}

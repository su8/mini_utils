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

int main(int argc, char *argv[]) {
  size_t len = 0, x = 0, cut_here = 0;
  char *srcptr = NULL, *temp = NULL, *src = NULL;
  char buf[5000];

  if (1 == argc) {
    fprintf(stderr, "%s\n", "Missing argument(s)");
    return EXIT_FAILURE;
  }
  src  = argv[1];
  temp = argv[1];

  len = strlen(argv[1]);

  if (NULL == (srcptr = strrchr(temp, '/'))) {
    goto out;
  }

  if (!*(srcptr+1)) {
    src[len - 1] = '\0';
  }

  for (; *temp; x++, temp++) {
    if ('/' == *temp) {
      cut_here = x;
    }
  }

  if (0 == cut_here) {
    goto out;
  }

  memcpy(buf, src, cut_here);
  buf[cut_here] = '\0';

  puts(buf);

out:
  return EXIT_SUCCESS;
}
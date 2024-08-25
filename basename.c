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
  size_t len = 0;
  char *srcptr = NULL, *temp = NULL, *temp2 = NULL;

  if (1 == argc) {
    fprintf(stderr, "%s\n", "Missing argument(s)");
    return EXIT_FAILURE;
  }
  temp  = argv[1];
  temp2 = argv[1];

  if (NULL == (srcptr = strrchr(temp, '/'))) {
    goto out;
  }

  if (!*(srcptr+1)) {
    if (1 >= (len = strlen(argv[1]))){
      goto out;
    }
    temp2[len - 1] = '\0';
    if (NULL == (srcptr = strrchr(temp2, '/'))) {
      goto out;
    }
  }

  ++srcptr;
  puts(srcptr);

out:
  return EXIT_SUCCESS;
}
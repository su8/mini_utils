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

#define MAX_STRING_SIZE 256

void output_file(FILE *in, FILE *out);

int main(int argc, char **argv) {
  int arg_count = argc;
  char **arguments = argv;

  if (arg_count == 1) {
    output_file(stdin, stdout);
    return 0;
  }

  FILE *read_file;
  while (--arg_count > 0) {
    read_file = fopen(*++arguments, "r");

    if (read_file == NULL) {
      perror(*arguments);
      return 1;
    }

    output_file(read_file, stdout);
    fclose(read_file);
  } // end while

}

void output_file(FILE *in, FILE *out) {
  static char buffer[MAX_STRING_SIZE];

  size_t size; // Number of bytes read by fread()
  while ( (size = fread(buffer, 1, MAX_STRING_SIZE - 1, in) ) != 0) {
    buffer[size] = '\0';
    fwrite(buffer, 1, size, out);
  }
}
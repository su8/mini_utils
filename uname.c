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
#include <unistd.h>
#include <sys/utsname.h>

#define MAX_STRING_SIZE 256

int main(int argc, char *argv[]) {
  int ch = 0;
  char buf[MAX_STRING_SIZE] = {'\0'};
  char *all = buf;
  struct utsname KerneL;

  memset(&KerneL, 0, sizeof(struct utsname));

  if (-1 == (uname(&KerneL))) {
    fprintf(stderr, "%s\n", "uname() failed");
    return EXIT_FAILURE;
  }

  if (1 == argc) {
    puts(KerneL.sysname);
  }

  while (-1 != (ch = getopt(argc, argv, "asnrvm"))) {
    switch(ch) {
      case 'a':
        all += snprintf(all, MAX_STRING_SIZE-1, "%s %s %s %s %s ",
            KerneL.sysname, KerneL.nodename, KerneL.release,
            KerneL.version, KerneL.machine);
        break;
      case 's':
        all += snprintf(all, MAX_STRING_SIZE-1, "%s ", KerneL.sysname);
        break;
      case 'n':
        all += snprintf(all, MAX_STRING_SIZE-1, "%s ", KerneL.nodename);
        break;
      case 'r':
        all += snprintf(all, MAX_STRING_SIZE-1, "%s ", KerneL.release);
        break;
      case 'v':
        all += snprintf(all, MAX_STRING_SIZE-1, "%s ", KerneL.version);
        break;
      case 'm':
        all += snprintf(all, MAX_STRING_SIZE-1, "%s ", KerneL.machine);
        break;
    }
  }

  *(--all) = '\0';
  puts(buf);

  return EXIT_SUCCESS;
}
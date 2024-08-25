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

#if defined(__linux__)
# include <sys/sysinfo.h>
#endif /* __linux__ */

int main(void) {

#if defined(__linux__)
  struct sysinfo up;
  memset(&up, 0, sizeof(up));

  if (-1 == (sysinfo(&up))) {
    fprintf(stderr, "%s\n", "sysinfo() failed");
    return EXIT_FAILURE;
  }

  printf("%.2f %.2f %.2f\n",
      (float)up.loads[0] / 65535.0f,
      (float)up.loads[1] / 65535.0f,
      (float)up.loads[2] / 65535.0f);

#elif defined(__FreeBSD__) || defined(__OpenBSD__)
  double up[3] = { 0, 0, 0 };

  if (-1 == (getloadavg(up, 3))) {
    fprintf(stderr, "%s\n", "getloadavg() failed");
    return EXIT_FAILURE;
  }
  printf("%.2f %.2f %.2f\n",
      (float)up[0], (float)up[1], (float)up[3]);
#endif /* __linux__ */

  return EXIT_SUCCESS;
}
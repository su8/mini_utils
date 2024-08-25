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
#include <inttypes.h>
#include <time.h>

#if defined(__FreeBSD__) || defined(__OpenBSD__)
# include <sys/types.h>
# include <sys/sysctl.h>
#endif /* __FreeBSD__  || __OpenBSD__ */

#define UINT "%"PRIuMAX

int main(void) {
  uintmax_t now = 1;
  struct timespec tc = {0L, 0L};

#if defined(__linux__)
  if (-1 == (clock_gettime(CLOCK_BOOTTIME, &tc))) {
    fprintf(stderr, "%s\n", "clock_gettime() failed");
    return EXIT_FAILURE;
  }
  now = (uintmax_t)tc.tv_sec;

#elif defined(__FreeBSD__) || defined(__OpenBSD__)
  int mib[] = { CTL_KERN, KERN_BOOTTIME };
  time_t t;
  size_t len = sizeof(tc);

  if (0 != (sysctl(mib, 2, &tc, &len, NULL, 0))) {
    fprintf(stderr, "%s\n", "sysctl() failed");
    return EXIT_FAILURE;
  }
  if (-1 == (t = time(NULL))) {
    fprintf(stderr, "%s\n", "time() failed");
    return EXIT_FAILURE;
  }

  now = (uintmax_t)t - (uintmax_t)tc.tv_sec;
#endif /* __linux__ */

  if (0 != (now / 86400)) { /* days */
    printf("up " UINT "d " UINT "h " UINT "m\n",
        (now / 86400),
        ((now / 3600) % 24),
        ((now / 60) % 60));
    return EXIT_SUCCESS;
  }
  if (59 < (now / 60)) { /* hours */
    printf("up " UINT "h " UINT "m\n", ((now / 3600) % 24), ((now / 60) % 60));
    return EXIT_SUCCESS;
  }

  printf("up " UINT "m\n", ((now / 60) % 60));

  return EXIT_SUCCESS;
}
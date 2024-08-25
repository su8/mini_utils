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
#include <signal.h>

void init_da_handler(void);
void sighandler(int num);

static volatile sig_atomic_t call_it_quits = 0;

int main(int argc, char *argv[]) {
  const char *const input = argv[1];

  init_da_handler();

  if (1 == argc) {
    fprintf(stderr, "%s\n", "Missing argument");
    return EXIT_FAILURE;
  }

  while (1) {
    puts(input);
    if (1 == call_it_quits) {
      break;
    }
  }

  return EXIT_SUCCESS;
}

void init_da_handler(void) {
  struct sigaction setup_action;
  memset(&setup_action, 0, sizeof(struct sigaction));

  setup_action.sa_handler = sighandler;

  if (-1 == (sigaction(SIGINT, &setup_action, NULL))) {
    fprintf(stderr, "%s\n", "sigaction() failed");
    exit(EXIT_FAILURE);
  }
}

/* !!! WARNING !!! */
void sighandler(int num) {
/* ASYNC CODE ONLY */
  (void)num;
  call_it_quits = 1;
}
/*
 * This file is part of PCAPdroid.
 *
 * PCAPdroid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef PCAPdroid_BOYER_MOORE_H
#define PCAPdroid_BOYER_MOORE_H

#include <stdbool.h>

/* True when pattern occurs in text. Matching ignores ASCII case. */
bool boyer_moore_contains_ci(const char *text, const char *pattern);

#endif

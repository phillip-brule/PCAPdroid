/*
 * This file is part of PCAPdroid.
 *
 * PCAPdroid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "boyer_moore.h"

#include <ctype.h>
#include <stddef.h>
#include <string.h>

bool boyer_moore_contains_ci(const char *text, const char *pattern) {
    size_t n, m, i;
    unsigned char pat[256];
    int shift[256];

    if(!text || !pattern || !pattern[0])
        return false;

    n = strlen(text);
    m = strlen(pattern);
    if((m > n) || (m > sizeof(pat)))
        return false;

    for(i = 0; i < m; i++)
        pat[i] = (unsigned char)tolower((unsigned char)pattern[i]);

    for(i = 0; i < 256; i++)
        shift[i] = (int)m;
    for(i = 0; i + 1 < m; i++)
        shift[pat[i]] = (int)(m - 1 - i);

    i = 0;
    while(i + m <= n) {
        size_t j = m;

        while(j > 0 &&
              (unsigned char)tolower((unsigned char)text[i + j - 1]) == pat[j - 1])
            j--;

        if(j == 0)
            return true;

        {
            unsigned char last = (unsigned char)tolower((unsigned char)text[i + m - 1]);
            int step = shift[last];
            if(step < 1)
                step = 1;
            i += (size_t)step;
        }
    }

    return false;
}

#ifdef BOYER_MOORE_TEST
#include <stdio.h>

int main(void) {
    if(!boyer_moore_contains_ci("api.alibaba.com", "alibaba")) return 1;
    if(!boyer_moore_contains_ci("ALIBABA", "alibaba")) return 1;
    if(!boyer_moore_contains_ci("xxalibaba", "alibaba")) return 1;
    if(!boyer_moore_contains_ci("alibaba", "alibaba")) return 1;
    if(boyer_moore_contains_ci("ali", "alibaba")) return 1;
    if(boyer_moore_contains_ci("not-this", "alibaba")) return 1;
    if(boyer_moore_contains_ci("", "alibaba")) return 1;
    if(boyer_moore_contains_ci("example.com", "alibaba")) return 1;
    puts("ok");
    return 0;
}
#endif

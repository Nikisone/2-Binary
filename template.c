//
//  template.c
//  Tietokoneverkot
//
//  Created by Olli-Pekka Pennanen on 10.3.2021.
//

#include <stdio.h>
#include "template.h"


int parse_str(const char *str, struct numbers *n)
{
    int ret;
    unsigned short sa, sc;
    ret = sscanf(str, "%hu %u %hu %hu %u", &sa, &n->b, &sc, &n->d, &n->e);
    n->a = sa;
    n->c = sc;
    return ret;
}

void output_str(char *str, size_t len, const struct numbers *n)
{
    snprintf(str, len, "%u %u %u %u %u", n->a, n->b, n->c, n->d, n->e);
}

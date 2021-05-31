//
//  template.h
//  Tietokoneverkot
//
//  Created by Olli-Pekka Pennanen on 10.3.2021.
//
#ifndef NWP_TEMPLATE_H
#define NWP_TEMPLATE_H

#include <stdlib.h>

struct numbers {
    uint8_t a;
    uint32_t b;
    uint8_t c;
    uint16_t d;
    uint32_t e;
};

int parse_str(const char *str, struct numbers *n);
void output_str(char *str, size_t len, const struct numbers *n);


#endif /* template_h */

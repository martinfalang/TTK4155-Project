#ifndef IR_H
#define IR_H

#include <stdbool.h>
#include "../../lib/inc/defines.h"

void ir_init(void);
void ir_reset(void);
bool ir_beam_broken(void);

#if DEBUG
void ir_test(void);
#endif // DEBUG

#endif // IR_H
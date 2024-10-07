#include "int.h"

void int_init(void)
{
    GIC_Init();
    __set_VBAR(0x87800000);
}
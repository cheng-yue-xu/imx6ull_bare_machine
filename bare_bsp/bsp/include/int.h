#ifndef __INT_H__
#define __INT_H__

#include "imx6ull.h"
typedef void (*system_irq_handler_t)(unsigned int gicciar,void *param);
typedef struct _sys_irq_handle
{
    system_irq_handler_t irqHandler;
    void *userparam;
}sys_irq_handle_t;
void int_init(void);
void default_irqhandler(unsigned int gicciar,void *userparam);
void system_register_irqhandler(IRQn_Type irq,system_irq_handler_t irqhandler, void *userparam);
#endif
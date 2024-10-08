#include "int.h"
static unsigned int irqnesting;
//中断处理函数表
static sys_irq_handle_t irqTable[NUMBER_OF_INT_VECTORS];
//初始化中断处理函数表
void system_irqtable_init(void)
{
    unsigned int i = 0;
    irqnesting = 0;
    for (i = 0; i < NUMBER_OF_INT_VECTORS; i++)
    {
        irqTable[i].irqHandler = default_irqhandler;
        irqTable[i].userparam = NULL;
    }
}

void int_init(void)
{
    GIC_Init();
    system_irqtable_init();
    __set_VBAR(0x87800000);
}
//具体的中断处理函数
void system_irqhandler(unsigned int gicciar)
{
    u32 intnum = gicciar & 0x3ff;
    if(intnum >= NUMBER_OF_INT_VECTORS)
    {
        return ;
    }
    
    irqnesting++;
    
    irqTable[intnum].irqHandler(intnum,irqTable[intnum].userparam);
    
    irqnesting--;
    
}

//默认中断处理函数
void default_irqhandler(unsigned int gicciar,void *userparam)
{
    while(1);
}

//注册中断处理函数
void system_register_irqhandler(IRQn_Type irq,system_irq_handler_t irqhandler, void *userparam)
{
    irqTable[irq].irqHandler = irqhandler;
    irqTable[irq].userparam = userparam;
}
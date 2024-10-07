#include "beep.h"

void beep_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0x10b0);
    GPIO5->GDIR |= (1<<1);
    GPIO5->DR &= ~(1<<1);
}

void beep_ring(void)
{
    GPIO5->DR &= ~(1<<1);
}

void beep_stop(void)
{
    GPIO5->DR |= (1<<1);
}
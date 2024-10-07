#ifndef __BEEF_H__
#define __BEEF_H__

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

void beep_init(void);
void beep_ring(void);
void beep_stop(void);
#endif
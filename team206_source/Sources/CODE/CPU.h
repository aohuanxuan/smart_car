

#ifndef   CPU_H
#define   CPU_H


/*
*********************************************************************************************************
* Description: _EntryPoint
*********************************************************************************************************
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED

void _EntryPoint(void);

#pragma CODE_SEG DEFAULT


/*
*********************************************************************************************************
* Description: No
*********************************************************************************************************
*/
void Cpu_Delay100US(uint16_t us100);


#endif
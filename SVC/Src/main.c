/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */


#include<stdio.h>
#include<stdint.h>
int main(void)
{

	uint32_t data1;
	uint32_t data2;

	data1 = 4;
	data2 = 5;
	data1 = data2 *4 +data1;
	data2 = data1*data1*data2;

	__asm volatile ("SVC #25");

//	register uint32_t data __asm("r0");

	uint32_t data;

	__asm volatile ("MOV %0,R0": "=r"(data) ::);

	printf(" data = %ld\n",data);

	for(;;);
}


__attribute__ ((naked)) void SVC_Handler(void)
{
	//1 . get the value of the MSP
	__asm("MRS R0,MSP");
	__asm("B SVC_Handler_c");
}

void SVC_Handler_c(uint32_t *pBaseOfStackFrame)
{
	printf("in SVC handler\n");

	uint8_t *pReturn_addr = (uint8_t*)pBaseOfStackFrame[6];

	//2. decrement the return address by 2 to point to
	//opcode of the SVC instruction in the program memory
	pReturn_addr-=2;


	//3. extract the SVC number (LSByte of the opcode)
    uint8_t svc_number = *pReturn_addr;

    printf("Svc number is : %d\n",svc_number);

    svc_number+=4;

    pBaseOfStackFrame[0] = svc_number;

}

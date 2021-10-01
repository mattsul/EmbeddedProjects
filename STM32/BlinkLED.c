#include <stdint.h>

int main(void)
{
    /* Loop forever */
	/*
	 * 1. Identify GPIO Port (A) Base: 0x4002 0000 + offset:  0x14
	 * 2. Identify GPIO Pin (5) Value: 100000
	 * 3. Activate GPIOA peripheral (enable the clock; RCC: Reset and Clock Control) Base: 0x4002 3800  Offset: 0x30
	 * 4. Configure GPIO pin as output (pin on MCU) Mode Register: 0x4002 0000 and assign 0b01
	 * 5. Write to the GPIO pin (send data to LED) program 1 to bit 5 of address 0x4002 0014
	 * 6. Celebrate
	 * */

	/* Point to address' then change the address's values */
	uint32_t *pointClock 	  = (uint32_t*)0x40023830; // clock register
	uint32_t *pointOutputMode = (uint32_t*)0x40020001; // output mode on MCU pin
	uint32_t *pointOutputReg  = (uint32_t*)0x40020014; // change this bit/bus on the pin

	// 1. Enable clock
	*pointClock = *pointClock | 0x08; // bitwise OR allows other bits to stay zero :)

	// 2. Activate output mode
	*pointOutputMode &= 0xFFFFF3FF; // clear
	*pointOutputMode |= 0x00000100; 	  // change output mode by making 5th position HIGH

	// 3. Set value to high!
	*pointOutputReg |= 0x0010;

	while(1); // infinite empty loop
}

// ----------------------------------------------------------------------------
// Lab1.c
// Jonathan Valvano
// December 31, 2024
// Possible main program to test the lab
// Feel free to edit this to match your specifications
#include <stdint.h>
#include "../inc/PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/SysTick.h"

void Clock_Delay1ms(uint32_t n);
void LED_Init(void);
void LED_Out(uint32_t data);
void Switch_Init(void);
uint32_t Switch_In(void);

int main(void){
  PLL_Init(Bus80MHz); 
  LED_Init();
  Switch_Init();
  // write this
	
	uint32_t state = 0;
  while(1){

			uint32_t input = !Switch_In();
			
			switch(state) {
				case 0:
					if (input == 1) {
						state = 1;
					} else {
						state = 0;
					}
					
					LED_Out(0);
					break;
				
				case 1:
					if (input == 1) {
						state = 2;
					} else {
						state = 0;
					}
					
					LED_Out(0);
					break;
				
				case 2:
					if (input == 1) {
						state = 3;
					} else {
						state = 0;
					}
					
					LED_Out(0);
					break;

				case 3:
				if (input == 1) {
					state = 1;
				} else {
					state = 0;
				}
				
				LED_Out(1);
				break;				
				
				
				default:
					if (input == 1) {
						state = 1;
					} else {
						state = 0;
					}
					
					LED_Out(0);

					break;
				
				
			}
		
      
  } 
} 

void LED_Init(void){
    // write this, initialize LED pins here
		// for testing, lets make PF1 (internal LED) an output
		
		SYSCTL_RCGCGPIO_R |= 0x20;        // 1) activate clock for Port F
    while((SYSCTL_PRGPIO_R&0x20) == 0){}; // 2) ready?
//		GPIO_PORTF_LOCK_R = 0x4C4F434B; // 3) unlock GPIO Port F
//		GPIO_PORTF_CR_R = 0x02; 
    GPIO_PORTF_AMSEL_R &= ~0x02;      // 4) disable analog on PF1
    GPIO_PORTF_PCTL_R &= ~0x000000F0; // 5) PCTL GPIO on PF1
    GPIO_PORTF_DIR_R |= 0x02;         // 6) PF1 out
    GPIO_PORTF_DR8R_R |= 0x02;        // 7) enable 8mA drive on PF1
    GPIO_PORTF_AFSEL_R &= ~0x02;      // 8) disable alt funct on PF1
    GPIO_PORTF_DEN_R |= 0x02;         // 9) enable digital I/O on PF1
}
void LED_Out(uint32_t data){
    GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & ~0x02) | (data << 1);
    
}
void Switch_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x20;      // 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R&0x20) == 0){};// 2) ready?
  GPIO_PORTF_LOCK_R = 0x4C4F434B; // 3) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0xFF;         // allow changes to PF0
  GPIO_PORTF_AMSEL_R &= ~0x01;    // 4) disable analog on PF0
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFFFF0); // 5) PCTL GPIO on PF0
  GPIO_PORTF_DIR_R &= ~0x01;      // 6) PF0 in
  GPIO_PORTF_AFSEL_R &= ~0x01;    // 8) disable alt funct on PF0
	GPIO_PORTF_PUR_R |= 0x01;        // enable pull-up on PF0
  GPIO_PORTF_DEN_R |= 0x01;       // 9) enable digital I/O on PF0
}
uint32_t Switch_In(void){
  return ((GPIO_PORTF_DATA_R&0x01)>>0); // read PF0 input
}







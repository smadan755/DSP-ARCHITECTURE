// ----------------------------------------------------------------------------
// Lab1.c
// Jonathan Valvano
// December 31, 2024
// Possible main program to test the lab
// Feel free to edit this to match your specifications
#define R0  0
#define T1  1
#define R1  2
#define T2  3
#define R2  4
#define T3  5
#define R3  6
#define T4  7
#define R4  8
#define T5  9
#define R5 10
#define T0 11







#include <stdint.h>
#include "../inc/PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/SysTick.h"

typedef struct {
	uint32_t Output;
	uint32_t Next[2];
} State;

State FSM[12] = {
    {0, {R0, T1}},   // State R0 (1): LED=0, if input=0 stay in R0, if input=1 go to T1
    {0, {R1, T1}},   // State T1 (2): LED=0, if input=0 go to R1, if input=1 stay in T1
    {0, {R1, T2}},   // State R1 (3): LED=0, if input=0 stay in R1, if input=1 go to T2
    {0, {R2, T2}},   // State T2 (4): LED=0, if input=0 go to R2, if input=1 stay in T2
    {0, {R2, T3}},   // State R2 (5): LED=0, if input=0 stay in R2, if input=1 go to T3
    {1, {R3, T3}},   // State T3 (6): LED=1, if input=0 go to R3, if input=1 stay in T3
    {1, {R3, T4}},   // State R3 (7): LED=1, if input=0 stay in R3, if input=1 go to T4
    {1, {R4, T4}},   // State T4 (8): LED=1, if input=0 go to R4, if input=1 stay in T4
    {1, {R4, T5}},   // State R4 (9): LED=1, if input=0 stay in R4, if input=1 go to T5
    {1, {R5, T5}},   // State T5 (10): LED=1, if input=0 go to R5, if input=1 stay in T5
    {1, {R5, T0}},   // State R5 (11): LED=1, if input=0 stay in R5, if input=1 go to T0
    {0, {R0, T0}}    // State T0 (12): LED=0, if input=0 go to R0, if input=1 stay in T0
};



void Clock_Delay1ms(uint32_t n);
void LED_Init(void);
void LED_Out(uint32_t data);
void Switch_Init(void);
uint32_t Switch_In(void);

int main(void){
  PLL_Init(Bus80MHz); 
  LED_Init();
  Switch_Init();
	SysTick_Init();
  // write this
	
	uint32_t state = R0;
  while(1){
			uint32_t input = Switch_In();
		
			
			
			LED_Out(FSM[state].Output);
		
			state = FSM[state].Next[input];
		
			SysTick80_Wait10ms(1);
			
		
//			switch(state) {
//				case 1:
//					if (input == 1) {
//						state = 2;
//					} else {
//						state = 1;
//					}
//					
//					LED_Out(0);
//					break;
//				
//				case 2:
//					if (input == 1) {
//						state = 2;
//					} else {
//						state = 3;
//					}
//					
//					LED_Out(0);
//					break;

//				case 3:
//				if (input == 1) {
//					state = 4;
//				} else {
//					state = 3;
//				}
//				
//				LED_Out(0);
//				break;

//				case 4:
//					if (input == 1) {
//						state = 4;
//					} else {
//						state = 5;
//					}
//					
//					LED_Out(0);
//					break;
//					
//				case 5:
//					if (input == 1) {
//						state = 6;
//					} else {
//						state = 5;
//					}
//					
//					LED_Out(0);
//					break;
//					
//				case 6:
//					if (input == 1) {
//						state = 6;
//					} else {
//						state = 7;
//					}
//					
//					LED_Out(1);
//					break;
//					
//					case 7:
//					if (input == 1) {
//						state = 8;
//					} else {
//						state = 7;
//					}
//					
//					LED_Out(1);
//					break;
//				
//				case 8:
//					if (input == 1) {
//						state = 8;
//					} else {
//						state = 9;
//					}
//					
//					LED_Out(1);
//					break;
//				
//				case 9:
//					if (input == 1) {
//						state = 10;
//					} else {
//						state = 9;
//					}
//					
//					LED_Out(1);
//					break;

//				case 10:
//				if (input == 1) {
//					state = 10;
//				} else {
//					state = 11;
//				}
//				
//				LED_Out(1);
//				break;

//				case 11:
//					if (input == 1) {
//						state = 12;
//					} else {
//						state = 11;
//					}
//					
//					LED_Out(1);
//					break;
//					
//				case 12:
//					if (input == 1) {
//						state = 12;
//					} else {
//						state = 1;
//					}
//					
//					LED_Out(0);
//					break;
//					
//				
//				
//				
//				default:	// default to state 0
//					if (input == 1) {
//						state = 2;
//					} else {
//						state = 1;
//					}
//					
//					LED_Out(0);

//					break;
//				
//				
//			}
		
      
  } 
} 

void LED_Init(void){
    // write this, initialize LED pins here
		// for testing, lets make PF1 (internal LED) an output
		
		SYSCTL_RCGCGPIO_R |= 0x04;        // 1) activate clock for Port F
    while((SYSCTL_PRGPIO_R&0x04) == 0){}; // 2) ready?
//		GPIO_PORTF_LOCK_R = 0x4C4F434B; // 3) unlock GPIO Port F
//		GPIO_PORTF_CR_R = 0x02; 
    GPIO_PORTC_AMSEL_R &= ~0x80;      // 4) disable analog on PF1
    GPIO_PORTC_PCTL_R &= ~0xF0000000; // 5) PCTL GPIO on PF1
    GPIO_PORTC_DIR_R |= 0x80;         // 6) PF1 out
    GPIO_PORTC_DR8R_R |= 0x80;        // 7) enable 8mA drive on PF1
    GPIO_PORTC_AFSEL_R &= ~0x80;      // 8) disable alt funct on PF1
    GPIO_PORTC_DEN_R |= 0x80;         // 9) enable digital I/O on PF1
}
void LED_Out(uint32_t data){
    GPIO_PORTC_DATA_R = (GPIO_PORTC_DATA_R & ~0x80 | (data << 7));
    
}
void Switch_Init(void){
    SYSCTL_RCGCGPIO_R |= 0x02;      // 1) activate clock for Port B
    while((SYSCTL_PRGPIO_R&0x02) == 0){};// 2) ready?
    
    GPIO_PORTB_AMSEL_R &= ~0x10;    // 3) disable analog on PB4
    GPIO_PORTB_PCTL_R &= ~0xFFF0FFFF; // 4) PCTL GPIO on PB4
    GPIO_PORTB_DIR_R &= ~0x10;      // 5) PB4 in
    GPIO_PORTB_AFSEL_R &= ~0x10;    // 6) disable alt funct on PB4
    GPIO_PORTB_DEN_R |= 0x10;       // 8) enable digital I/O on PB4
}
uint32_t Switch_In(void){
  return ((GPIO_PORTB_DATA_R&0x10)>>4); // read PB4 input
	// 0, 1, 2, 3, 4
	// 0	0		0	0  1 000
}







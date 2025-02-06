// Lab3Main.c
// Runs on LM4F120/TM4C123
// Uses ST7735.c to display the clock
// patterns to the LCD.
//    16-bit color, 128 wide by 160 high LCD
// Mark McDermott, Daniel Valvano and Jonathan Valvano
// Lab solution, do not post
// August 3,2024

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2024

 Copyright 2025 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// Hardware connections (adjust as needed):
//  PD0 is squarewave output to speaker
//  PE0 is mode select
//  PE1 is left
//  PE2 is right 
//  PE3 is up
//  PE4 is down
//  If alarm is sounding, any button will quiet the alarm

#include <stdio.h>
#include <stdint.h>
#include "../inc/ST7735.h"
#include "../inc/PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/Timer0A.h"
#include "Lab3.h"

// ---------- Prototypes   -------------------------
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode
void EdgeInterrupt_Init(void);
void GPIOPortE_Handler(void);
void LED_Init(void);
void LED_Out(uint32_t data);

int FallingEdges;

int main(void){
  DisableInterrupts();
  PLL_Init(Bus80MHz);    // bus clock at 80 MHz

  EdgeInterrupt_Init();    // Configure PE0 for edge-triggered interrupt
  EnableInterrupts();
  LED_Init();            // Initialize on-board LED (PF1)
  
  while(1){
    WaitForInterrupt();  // Low-power mode waiting for interrupts
  }
}

// ------------ EdgeInterrupt_Init ------------
// Configure PE0 as input and arm it for edge-triggered interrupts (rising edge).
// PE0 can be used as a switch or button input.
//
// Steps:
// 1) Enable clock for Port E
// 2) Wait until the port is ready
// 3) Make PE0 input
// 4) Enable digital functionality
// 5) [Optional] Enable internal pull-up resistor on PE0 (commented out)
// 6) Configure for edge-trigger on the rising edge
// 7) Clear any prior interrupt flag
// 8) Unmask interrupt for PE0
// 9) Set priority to 5 (bits 15-13 in NVIC_PRI5_R)
// 10) Enable Port E interrupt (#4 in external IRQ numbering) in NVIC_EN0
// 11) Enable global interrupts
void EdgeInterrupt_Init(void){
  // 1) Activate clock for Port E (bit 4 in RCGCGPIO)
  SYSCTL_RCGCGPIO_R |= 0x10;            
  // 2) Wait until Port E is ready
  while((SYSCTL_PRGPIO_R & 0x10) == 0){};

  // 3) Make PE0 input (clear bit 0 in DIR)
  GPIO_PORTE_DIR_R &= ~0x01;
  // 4) Enable digital functionality on PE0
  GPIO_PORTE_DEN_R |= 0x01;

  // 5) [Optional] Enable internal pull-up resistor on PE0
  //    This keeps PE0 at logic HIGH if switch is open
  // GPIO_PORTE_PUR_R |= 0x01;

  // 6) Configure PE0 for edge-sensitive interrupt on rising edge
  //    IS=0 (edge), IBE=0 (one edge), IEV=1 (rising)
  GPIO_PORTE_IS_R  &= ~0x01;  // edge-sensitive
  GPIO_PORTE_IBE_R &= ~0x01;  // not both edges
  GPIO_PORTE_IEV_R |= 0x01;   // rising edge event

  // 7) Clear any prior interrupt on PE0
  GPIO_PORTE_ICR_R = 0x01;

  // 8) Arm interrupt for PE0 (unmask in IM)
  GPIO_PORTE_IM_R |= 0x01;

  // 9) Set priority of Port E (interrupt #4) to 5
  //    bits 15-13 in NVIC_PRI5_R
  NVIC_PRI5_R = (NVIC_PRI5_R & 0xFFFF1FFF) | 0x0000A000;

  // 10) Enable interrupt #4 in NVIC_EN0
  NVIC_EN0_R = 1 << 4;

  // 11) Enable global interrupts
  EnableInterrupts();
}

// ------------ GPIOPortE_Handler ------------
// ISR for PE0 interrupt on the rising edge.
// Toggles the on-board LED (PF1).
void GPIOPortE_Handler(void){
  // Acknowledge the interrupt by clearing the flag
  GPIO_PORTE_ICR_R = 0x01;  

  // Toggle PF1 output
  static uint32_t toggle = 0;
  toggle ^= 1;   // flip between 0 and 1
  LED_Out(toggle);
}

// ------------ LED_Init ------------
// Configure PF1 as output to drive the red LED.
void LED_Init(void){
  SYSCTL_RCGCGPIO_R |= 0x20;          // 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R & 0x20) == 0){};

  GPIO_PORTF_AMSEL_R &= ~0x02;        // 2) disable analog on PF1
  GPIO_PORTF_PCTL_R &= ~0x000000F0;   // 3) PCTL GPIO on PF1
  GPIO_PORTF_DIR_R |= 0x02;           // 4) PF1 out
  GPIO_PORTF_DR8R_R |= 0x02;          // 5) enable 8mA drive on PF1
  GPIO_PORTF_AFSEL_R &= ~0x02;        // 6) disable alt funct on PF1
  GPIO_PORTF_DEN_R |= 0x02;           // 7) enable digital I/O on PF1
}

// ------------ LED_Out ------------
// Set PF1 based on 'data' (0 => off, 1 => on).
void LED_Out(uint32_t data){
  // Clear PF1, then set it according to 'data'
  GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & ~0x02) | ((data & 0x01) << 1);
}

#include <stdint.h>
#include "tm4c123gh6pm.h"

// Initialize ADC0 on PE4 (Ain9), SS3, soft-trigger, single sample, busy-wait
void ADC0_InitSWTriggerSeq3_Ch9(void){
  // 1) Activate ADC0
  SYSCTL_RCGCADC_R |= 0x01;
  // 2) Activate clock for Port E
  SYSCTL_RCGCGPIO_R |= 0x10;
  
  // 3) Stabilization (optional extra delay if needed)
  while((SYSCTL_PRGPIO_R & 0x10) == 0){};
  
  // 4) Make PE4 input
  GPIO_PORTE_DIR_R &= ~0x10;
  // 5) Enable alternate function on PE4
  GPIO_PORTE_AFSEL_R |= 0x10;
  // 6) Disable digital I/O on PE4
  GPIO_PORTE_DEN_R &= ~0x10;
  // 7) Enable analog functionality on PE4
  GPIO_PORTE_AMSEL_R |= 0x10;
  
  // 8) Configure ADC clock as 125k samples/sec
  ADC0_PC_R &= ~0xF;
  ADC0_PC_R |= 0x1;
  
  // 9) Sequencer 3 is highest priority
  ADC0_SSPRI_R = 0x0123;
  
  // 10) Disable SS3 during configuration
  ADC0_ACTSS_R &= ~0x08;
  
  // 11) Software trigger for SS3
  ADC0_EMUX_R &= ~0xF000;
  
  // 12) Set channel for SS3 (PE4 => Channel 9)
  ADC0_SSMUX3_R &= ~0x000F;
  ADC0_SSMUX3_R += 9;
  
  // 13) Sample control bits: TS0=0, IE0=1, END0=1, D0=0 => 0x6
  ADC0_SSCTL3_R = 0x06;
  
  // 14) Disable SS3 interrupts (polling method)
  ADC0_IM_R &= ~0x08;
  
  // 15) Enable sample sequencer 3
  ADC0_ACTSS_R |= 0x08;
}

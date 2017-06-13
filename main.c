
//file name Main.c//
//Student: HanXi Huang, Student Number: 1303296   Student ID: huangh32//
#include <hidef.h> /* common defines and macros */
#include "derivative.h" /* derivative information */
#include "SCI.h"
char string[20];
unsigned int val;

void delayby1ms(int);
void setClk(void); 
//---------------------OutCRLF---------------------
// Output a CR,LF to SCI to move cursor to a new line
// Input: none
// Output: none
// Toggle LED each time through the loop
void OutCRLF(void){
SCI_OutChar(CR);
SCI_OutChar(LF);
PTJ ^= 0x20; // toggle LED D2
}

void main(void) {
// Setup and enable ADC channel 0
// Refer to Chapter 14 in S12G Reference Manual for ADC subsystem details
                          
ATDCTL1 = 0x0F; // set for 8-bit resolution
ATDCTL3 = 0x88; // right justified, one sample per sequence
ATDCTL4 = 0x02; // prescaler = 2; ATD clock = 6.25MHz / (2 * (2 + 1)) == 1.04MHz
ATDCTL5 = 0x29;   // 00101001
setClk();

// Setup LED and SCI
DDRJ |= 0x01; // PortJ bit 0 is output to LED D2 on DIG13
SCI_Init(9600); //baud rate


for(;;) {
PTJ ^= 0x01; // toggle LED
//SCI_OutString("huang hanxi 1303296 "); OutCRLF();
val=ATDDR0;
SCI_OutUDec(val);
OutCRLF();
delayby1ms(3); //sample frequency. 1/300 

}
}

void delayby1ms(int k)
{
      int ix;
      TSCR1 = 0x90;  /* enable timer and fast timer flag clear */
      TSCR2 = 0x00;  /* disable timer interrupt, set prescaler to 1*/
      TIOS |= 0x01; /* enable OC0 */        //(not necessary)
      TC0 = TCNT + 4000;
      for(ix = 0; ix < k; ix++) {
             while(!(TFLG1_C0F));
             TC0 += 4000;
      }
      TIOS  &= ~0x01;   /* disable OC0 */  //(not necessary)
}

void setClk(void){
 //COMUCLKS=0x00;
 //CPMUSYNR=initSYNR+VCOPRQ;
 //CPMUREFDIV=initREFDV+REFFRQ;
 CPMUCLKS = 0x80;  //PLLSEL = 1
 CPMUOSC  = 0x00;  //OSCE = 0
 CPMUPOSTDIV=0x00;     //POST DIV is 0
 CPMUSYNR = 0x03;  //VCOFRQ = 0, SYNDIV = 3
 CPMUFLG  = 0x08; //LOCK=1
 
}    

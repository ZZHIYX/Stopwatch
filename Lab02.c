#include "address_map_arm.h"



int main(void){
		
		
		
		
		
		volatile int * Switch_Ptr = (int*)SW_BASE;
		
		volatile int * HEX_ptr = (int *)HEX3_HEX0_BASE; //points to HEX Display
		
		volatile int * Butt_Ptr = (int*)KEY_BASE;
		
		volatile int * Timer_Ptr =(int *)TIMER_BASE; // interal timer base address
/* set the interval timer period for scrolling the HEX displays */
int counter = 1000000; // 1/(100 MHz) x 5x10^6 = 50 msec
*(Timer_Ptr + 0x2) = (counter & 0xFFFF);
*(Timer_Ptr + 0x3) = (counter >> 16) & 0xFFFF;
/* start interval timer, enable its interrupts */
*(Timer_Ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1
		
		
		
		int lookUpTable[10]= {0x3F, 0x6, 0x5B,0x4F,0x66,0x6D,0x7D,0x7,0x7f,0x67};
		int M_S = 0;
		int S=0;
		int M=0;
		int temp=0;
		int temp_M_S, temp_S, temp_M;
		
		
		
		while(1){
			if(temp != *Butt_Ptr && *Butt_Ptr!=0){
			temp = *Butt_Ptr; 
			}
			if(temp == 2){
				*(Timer_Ptr+1)=0b1000;
			}
			if(temp == 4){
				temp_M_S=M_S;
				temp_S=S;
				temp_M=M;
				temp=1;
			}
			if(temp ==8){
				M_S=0;
				S=0;
				M=0;			
			}
			if(*(Timer_Ptr)==1 && temp == 1){
				M_S++;
				*(Timer_Ptr+1)=0b0100;
			}
			if(M_S>=100){
				S++;
				M_S=0;
			}
			if(S>=60){
				M++;
				S=0;
		}
			if(*Switch_Ptr ==0){
			*(HEX_ptr) = 0x1000000*lookUpTable[S/10]+0x10000*lookUpTable[S%10]+0x100*lookUpTable[M_S/10]+ lookUpTable[M_S%10];
			*(HEX_ptr+4) = lookUpTable[M%10]+256*lookUpTable[M/10];
			}
			else{ 
			*(HEX_ptr) = 0x1000000*lookUpTable[temp_S/10]+0x10000*lookUpTable[temp_S%10]+0x100*lookUpTable[temp_M_S/10]+ lookUpTable[temp_M_S%10];
			*(HEX_ptr+4) = lookUpTable[temp_M%10]+256*lookUpTable[temp_M/10];
			}
		}

	}
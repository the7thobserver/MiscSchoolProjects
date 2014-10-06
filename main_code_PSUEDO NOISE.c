

#include "dsk6713_aic23.h"

#define DSK6713_AIC23_INPUT_MIC 0x0015
#define DSK6713_AIC23_INPUT_LINEIN 0x0011

Uint32 fs = DSK6713_AIC23_FREQ_8KHZ; // 1
Uint16 inputsource = DSK6713_AIC23_INPUT_LINEIN; // 0x011


/*
			Description  
					-This program is designed to emulate 
*/ 

short echo = 0;	//What we're calculating for
double gain = .80;	//What we're multiplying to gradually decrease the sound
short input = 0;	//What we're taking in
short output = 0;

double echoBuffer[15000];
//short buffer[10000];
int n = 0;


interrupt void c_int11()
{
	//get input sample send to output sample here
	input = input_sample();
	//output_sample(input*5);

		// error check 
		if(n - 1500 < 0)
		{
			echoBuffer[n] = input;
			output_sample(input);
		}
		else
		{
			//Calc echo
			echoBuffer[n] = input + (double)(gain*(echoBuffer[n-1500]));
			// Y[n] = x[n] + t[n-1] 
			output = input + echoBuffer[n - 1500];
			output_sample(output);
		}

		n++;	//Next sample
		
		if (n>15000)
		n=0;


}// end of "interrupt"
// =========================================================================================

void main()
{
	// step 1: Initialize interrupt mode
	comm_intr();

	while(1)
	{
		//step 2: 
	}
}



#include <xuartlite_l.h>

#include <xparameters.h>

#include <xil_io.h>

int main(void){
	while (1){

		unsigned char first, second, third;

		first = 0x00;
		second =0x00;
		third = 0x00;
			//reading
		while(first == 0x00){
			first = XUartLite_RecvByte(0x84000000);
		}
		XUartLite_SendByte(0x84000000,first);


		while(second == 0x00){
					second = XUartLite_RecvByte(0x84000000);
				}
				XUartLite_SendByte(0x84000000,second);

		while(third == 0x00){
					third = XUartLite_RecvByte(0x84000000);
						}
				XUartLite_SendByte(0x84000000,third);


				     XUartLite_SendByte(0x84000000,0x20);// space















				// end reading
		if ((first == 0x6C) && (second == 0x65) && (third == 0x64)){
			first = 0x00;
			second = 0x00;
			third = 0x00;

			while(first == 0x00){
						first = XUartLite_RecvByte(0x84000000) - 0x30;




				second = first -0x27;
				if ((first >= 0x00)&& first <= 0x9){
					third = first;
				}
				else if ((second >= 0xA) && (second <= 0xF))
				{ third = second;
				}
				else {third = 0x0;}}
			XUartLite_SendByte(0x84000000, first + 0x30);


			third = third<<4;
			first = 0x00;
			second = 0x00;

			while(first == 0x00){
					first = XUartLite_RecvByte(0x84000000) - 0x30;
						second = first - 0x27;
							if ((first >= 0x0) && (first <= 0x9)) {
								third += first;
							}
							else if ((second >= 0xA) && (second <=0xF)){

									third +=second;
							}
							else { third = third;
							}}
			XUartLite_SendByte(0x84000000, first + 0x30);
			Xil_Out8(0x83000000, third);
		}

				// end of LEDS

	if ( (first == 0x73) && (second == 0x77) && (third == 0x74)){
			first = 0x00;
			second = 0x00;
			third = 0x00;
			first = Xil_In8(0x83000004) & 0xF;
			second = Xil_In8(0x83000004) & 0xF0;
			second = second >> 4;
			if (first <= 0x9){
				first = first +0x30;
			} else {
				first = first + 0x57;
			}
			if (second <= 0x9){
				second = second + 0x30;}
			else { second = second + 0x57;
			}
			XUartLite_SendByte(0x84000000, second);
			XUartLite_SendByte(0x84000000, first);
	}
	XUartLite_SendByte(0x84000000,0xA);
	XUartLite_SendByte(0x84000000, 0xD);
} return 0;
}

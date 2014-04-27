Lab4
====

Implementation of microprocessors


Introduction
The purpose of this lab was to implement two softcore processors on the Spartan 6 FPGA. These two processors would both be used to interface a UART port with Leds and Switches on the board. The first processor implemented was picoblaze and the second was microblaze. All non VHDL programming was done in C. 



The labs: 
the biggest part of the labs was actually interfacing with the UART. This was done by hooking the UART to the output portof the microprocessors. In Pico this required using two modules, one for nibble to ascii, and another for the reverese. In microblaze this functionality was included in the processor so all that needed to be done was the creation and implementation of peripherals followed by the C code to make to processor function correctly. this is shown below. 

first, characters had to be read in from the input port (0x84000000). 
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
				     
following that, if the three chars read in matched the letters for LED (test was implemented with an if statement, ) two more chars were needed with conversions and bounds checking to obtain values for leds. these values were then written out as shown below. 


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
			
Last, switch functionality was obtained by testing the three letters read in and comparing them to "swt" with an if statement. if they matched, the switch settings were read in using the following code. 


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
	
	Testing and debugging: 
	I had several issues on the hardware side because I was trying to use a read32 and write32 command instead of an 8 bit command. Also, my c code had several errors (mainly in equality tests) because of simple syntax errors like using one equals sign instead of two. 


Ultimately I had a lot more trouble with installing software and getting programs to run/find the corrent directories than i did with the actual implementation and usage of the microprocessors. the processors themselves give the user a significant amount of leeway in using the hardware because once the hardware is set up, it's use can be implemented in thousands of ways just using c code. 


Testing: 

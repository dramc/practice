// RS = P1.16
// EN = P1.17					 
// D4 = P1.18						   
//  D5 = P1.19						   
// D6 = P1.20						   
// D7 = P1.21						   
					  
//#include "LPC214x.H" 									// LPC2148 MPU Register
#include <LPC214x.h>
#include <stdio.h>

						   						  
// Define LCD PinIO Mask 
#define  LCD_RS     0x00000400   						// P0.10(0000 0000 0000 000x 0000 0000 0000 0000)
#define  LCD_EN     0x00002000   						// P0.13(0000 0000 0000 00x0 0000 0000 0000 0000) 0x00000800
//#define  LCD_D4     0x00000010   						// P0.4(0000 0000 0000 0x00 0000 0000 0000 0000)
//#define  LCD_D5     0x00000020  						// P0.5(0000 0000 0000 x000 0000 0000 0000 0000)
//#define  LCD_D6     0x00000040  						// P0.60000 000x 0000 0000 0000 0000 0000)
//#define  LCD_D7     0x00000080   					// P0.7(0000 0000 00x0 0000 0000 0000 0000 0000)



#define  LCD_D4     0x00100000   						// P0.20(0000 0000 0000 0x00 0000 0000 0000 0000)
#define  LCD_D5     0x00200000  						// P0.21(0000 0000 0000 x000 0000 0000 0000 0000)
#define  LCD_D6     0x00400000  						// P0.22(0000 0000 000x 0000 0000 0000 0000 0000)
#define  LCD_D7     0x00800000   	          // P0.23(0000 0000 000x 0000 0000 0000 0000 0000)
	
#define  LCD_DATA   (LCD_D7|LCD_D6|LCD_D5|LCD_D4)
#define  LCD_IOALL  (LCD_D7|LCD_D6|LCD_D5|LCD_D4|LCD_RS|LCD_EN)

#define  lcd_rs_set() IOSET0 = LCD_RS	 				// RS = 1 (Select Instruction)
#define  lcd_rs_clr() IOCLR0 = LCD_RS					// RS = 0 (Select Data)
#define  lcd_en_set() IOSET0 = LCD_EN					// EN = 1 (Enable)
#define  lcd_en_clr() IOCLR0 = LCD_EN					// EN = 0 (Disable)

// xxxx xxx0 0000 0000 0000 0000 0000 0000
#define  lcd_dir_write()  IODIR0 |= 0x01FFFFFF			// LCD Data Bus = Write
//#define  lcd_dir_read()   IODIR1 &= 0xFFC3FFFF			// LCD Data Bus = Read 

#define  lcd_clear()          lcd_write_control(0x01)	// Clear Display
#define  lcd_cursor_home()    lcd_write_control(0x02)	// Set Cursor = 0
#define  lcd_display_on()     lcd_write_control(0x0E)	// LCD Display Enable
#define  lcd_display_off()    lcd_write_control(0x08)	// LCD Display Disable
#define  lcd_cursor_blink()   lcd_write_control(0x0F)	// Set Cursor = Blink
#define  lcd_cursor_on()      lcd_write_control(0x0E)	// Enable LCD Cursor
#define  lcd_cursor_off()     lcd_write_control(0x0C)	// Disable LCD Cursor
#define  lcd_cursor_left()    lcd_write_control(0x10)	// Shift Left Cursor
#define  lcd_cursor_right()   lcd_write_control(0x14)	// Shift Right Cursor
#define  lcd_display_sleft()  lcd_write_control(0x18)	// Shift Left Display
#define  lcd_display_sright() lcd_write_control(0x1C)	// Shift Right Display

/* pototype  section */
void lcd_init(void);										// Initial LCD
void lcd_out_data4(unsigned char);						// Strobe 4-Bit Data to LCD
void lcd_write_byte(unsigned char);						// Write 1 Byte Data to LCD
void lcd_write_control(unsigned char); 					// Write Instruction
void lcd_write_ascii(unsigned char); 					// Write LCD Display(ASCII)
void goto_cursor(unsigned char);						// Set Position Cursor LCD
void lcd_print(unsigned char *str);							// Print Display to LCD
//char busy_lcd(void);									// Read Busy LCD Status
void enable_lcd(void);	 								// Enable Pulse
void delay(unsigned long int);							// Delay Function
void UART0_init(void);
unsigned char UART0_RxChar(void);
void UART0_TxChar(unsigned char ch);

void uart_string(const char *s);

unsigned char h=0;
														
/* Main Program Start Here */
int main(void)
{  
  unsigned char data[16]; 
	unsigned char receive;
	UART0_init();

  lcd_init();											// Initial LCD

 
  // Loop Print Message to LCD16 x 2 //
  while(1)	  											// Loop Continue
  {
		
  	lcd_write_control(0x01);  							// Clear Display  (Clear Display,Set DD RAM Address=0) 
    goto_cursor(0x80);									// Set Cursor Line-1
    lcd_print("UART");						// Display LCD Line-1  
	
   goto_cursor(0xC0);									// Set Cursor = Line-2
    lcd_print("DATA TXN TEST ");						// Display LCD Line-2
    delay(100000);									// Display Delay

	lcd_write_control(0x01);  							// Clear Display  (Clear Display,Set DD RAM Address=0) 
	goto_cursor(0x80);									// Set Cursor Line-1
    lcd_print("TYPE ");						// Display LCD Line-1    
    goto_cursor(0xC0);									// Set Cursor = Line-2
    lcd_print("TYPE CHARACTER.");						// Display LCD Line-2
    delay(100000);	
		uart_string("start receiving....");
	  h=0;
		loop1 :  receive=UART0_RxChar();
		delay(10000);
	
		while(receive!='\n')
		{
	
		
			data[h]=receive;
			h++;
			goto loop1;
		}
			data[h]='\0';
		lcd_write_control(0x01);  							// Clear Display  (Clear Display,Set DD RAM Address=0) 
	goto_cursor(0x80);	
		lcd_print(data);
		delay(100000000);
		
	}
		
		
//	}


//UART0_TxChar('s');
//if(receive=='a')
//{
	//lcd_write_control(0x01);  							// Clear Display  (Clear Display,Set DD RAM Address=0) 
    //goto_cursor(0x80);									// Set Cursor Line-1
	//lcd_print("byte received.....");

		// Display Delay  
  //}  
//lcd_write_control(0x01);  							// Clear Display  (Clear Display,Set DD RAM Address=0) 
   // goto_cursor(0x80);									// Set Cursor Line-1
	//lcd_print("byte received successfully");

}
	


/****************************/
/* Strobe 4-Bit Data to LCD */
/****************************/
void lcd_out_data4(unsigned char val)
{
IOCLR0 = (LCD_DATA);	  								// Reset 4-Bit Pin Data
  IOSET0 = (val<<20); 									// EN,0,RW,RS:DDDD:0000:0000:0000:0000:0000:0000   
 
}

/****************************/
/* Write Data 1 Byte to LCD */
/****************************/
void lcd_write_byte(unsigned char val)
{  
      
  lcd_out_data4((val>>4)&0x0F);							// Strobe 4-Bit High-Nibble to LCD
 
  enable_lcd();											// Enable Pulse
  
  lcd_out_data4(val&0x0F);				  				// Strobe 4-Bit Low-Nibble to LCD
  enable_lcd();											// Enable Pulse  
  
  delay(100000);
 // while(busy_lcd());      								// Wait LCD Execute Complete  
}

/****************************/
/* Write Instruction to LCD */
/****************************/
void lcd_write_control(unsigned char val)
{ 

  lcd_rs_clr();											// RS = 0 = Instruction Select
  lcd_write_byte(val);									// Strobe Command Byte	    
}

/****************************/
/* Write Data(ASCII) to LCD */
/****************************/
void lcd_write_ascii(unsigned char c)
{  
  lcd_rs_set();											// RS = 1 = Data Select
  lcd_write_byte(c);		   							// Strobe 1 Byte to LCD    
}

/*******************************/
/* Initial 4-Bit LCD Interface */
/*******************************/
void lcd_init()
{
  unsigned int i;										// LCD Initial Delay Count 

  PINSEL1  = 0x00000000;								// GPIO1[31..26] = I/O Function
  lcd_dir_write();										// LCD Data Bus = Write
  for (i=0;i<1000;i++);								// Power-On Delay (15 mS)

  IOCLR0 = (LCD_IOALL);									// Reset (RS,RW,EN,4-Bit Data) Pin
  IOSET0 = (LCD_D5|LCD_D4);								// DDDD:EN,RW,RS,0:0000:0000:0000:0000:0000:0000 
  enable_lcd();											// Enable Pulse
  for (i=0;i<100;i++);								// Delay 4.1mS

  IOCLR0 = (LCD_IOALL);	  								// Reset (RS,RW,EN,4-Bit Data) Pin
  IOSET0 = (LCD_D5|LCD_D4);								// DDDD:EN,RW,RS,0:0000:0000:0000:0000:0000:0000 
  enable_lcd();											// Enable Pulse
  for (i=0;i<100;i++);									// delay 100uS

  IOCLR0 = (LCD_IOALL);	  								// Reset (RS,RW,EN,4-Bit Data) Pin
  IOSET0 = (LCD_D5|LCD_D4);								// DDDD:EN,RW,RS,0:0000:0000:0000:0000:0000:0000 
  enable_lcd();											// Enable Pulse
  delay(10000);
  //while(busy_lcd());      								// Wait LCD Execute Complete
 
  IOCLR0 = (LCD_IOALL);	  								// Reset (RS,RW,EN,4-Bit Data) Pin
  IOSET0 = (LCD_D5);									// DDDD:EN,RW,RS,0:0000:0000:0000:0000:0000:0000 
  enable_lcd();											// Enable Pulse
  delay(10000);
 // while(busy_lcd());      								// Wait LCD Execute Complete

      
  lcd_write_control(0x28);  							// Function Set (DL=0 4-Bit,N=1 2 Line,F=0 5X7)
  lcd_write_control(0x0C);  							// Display on/off Control (Entry Display,Cursor off,Cursor not Blink)
  lcd_write_control(0x06);  							// Entry Mode Set (I/D=1 Increment,S=0 Cursor Shift)
  lcd_write_control(0x01);  							// Clear Display  (Clear Display,Set DD RAM Address=0) 
  for (i=0;i<100000;i++);								// Wait Command Ready

}

/***************************/
/* Set LCD Position Cursor */
/***************************/
void goto_cursor(unsigned char i)
{
  i |= 0x80;											// Set DD-RAM Address Command
  lcd_write_control(i);  
}

/************************************/
/* Print Display Data(ASCII) to LCD */
/************************************/
void lcd_print(unsigned char *str)
{
  int i;

// for (i=0;i<h||str[i]!=0;i++) 
 for (i=0;i<16 && str[i]!=0;i++)  	// 16 Character Print
	  	
  {
     lcd_write_ascii(str[i]);							// Print Byte to LCD
  }
 
}
/***********************/
/* Enable Pulse to LCD */
/***********************/
void enable_lcd(void)	 								// Enable Pulse
{
  unsigned int i;										// Delay Count

  
  lcd_en_set();  										// Enable ON
  for (i=0;i<400000;i++);
  lcd_en_clr();  										// Enable OFF 
}

/***********************/
/* Delay Time Function */
/*    1-4294967296     */
/***********************/
void delay(unsigned long int count1)
{
  while(count1 > 0) {count1--;}							// Loop Decrease Counter	
}

void UART0_init(void)
{
	PINSEL0 = PINSEL0 | 0x00000005;	/* Enable UART0 Rx0 and Tx0 pins of UART0 */
	U0LCR = 0x83;	 /* DLAB = 1, 1 stop bit, 8-bit character length */
	U0DLM = 0x00;	/* For baud rate of 9600 with Pclk = 15MHz */
	U0DLL = 0x61;		/* We get these values of U0DLL and U0DLM from formula */
	U0LCR = 0x03; 	/* DLAB = 0 */
}
unsigned char UART0_RxChar(void) /*A function to receive a byte on UART0 */
{
	while((U0LSR & 0x01)==0);	/*Wait till RDR bit becomes 1 which tells that receiver contains valid data */
delay(1000);
		return U0RBR;
	
	
}
void UART0_TxChar(unsigned char ch) /*A function to send a byte on UART0 */
{
	U0THR = ch;
	while( (U0LSR & 0x40) == 0 );	/* Wait till THRE bit becomes 1 which tells that transmission is completed */
}


void uart_string(const char *s)
{
	while(*s)
	{
		UART0_TxChar(*s++);
		delay(1000000);
	}
}














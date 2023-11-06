/******************************************************************************************************
File Name	: LightningAndVisibility.c
Author		: Mhoss
Description : Header file for the Timer AVR driver
 *******************************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
#include "keypad.h"
#include "dc_motor.h"
#include "common_macros.h"
#include "timer.h"
#include "gpio.h"
#define F_CPU_16000000

#define PASSWORD_LENGTH 4

//default Password is 0000
static uint8 Password[PASSWORD_LENGTH]={0};

uint8 flash=0;
uint8 key=0;
uint8 i=0;
uint8 flagCorrectPass=0;
uint8 enteredPassword=0;
Timer_ConfigType timer1={0,4882,TIMER1_ID,TIMER_COMPARE_MODE,TIMER1_PRESCALAR_1024,TIMERx_COMPARE_NORMAL_NO_OCx};

void Main_Menu();
void Set_Password();
uint8 Enter_Password();
void TurnOnMotor();
void TurnOffMotor();
void controlPasswordMenu();
void motorLEDList();
void motorMainMenu();
void controlLEDList();
void flashLED();
void INT0_Init();


int main(void){

//	DDRA = 0xF0;
//	PORTA = 0x0F;
	GPIO_setupPortDirection(PORTA_ID, PORT_OUTPUT);
	GPIO_writePort(PORTA_ID, LOGIC_HIGH);

	LCD_init();
	INT0_Init();
	DcMotor_Init();
	sei();

	Main_Menu();
	while(1){

		if(flagCorrectPass==0){
			Main_Menu();
		}
////
////		flagCorrectPass=0;
////		LCD_clearScreen();
////		LCD_moveCursor(0, 0);
////		LCD_displayString("1)Control Menu");
////		LCD_moveCursor(1, 0);
////		LCD_displayString("2)Password Menu");
////		key=KEYPAD_getPressedKey();
////		_delay_ms(250);
//		controlPasswordMenu();
//
//		if(key==1){
////			LCD_clearScreen();
////			LCD_moveCursor(0, 0);
////			LCD_displayString("1)Control Motor");
////			LCD_moveCursor(1, 0);
////			LCD_displayString("2)Control LED");
////			LCD_moveCursor(2, 0);
////			LCD_displayString("3)Control Menu");
////			key=KEYPAD_getPressedKey();
////			_delay_ms(250);
//			motorLEDList();
//			if(key==1){
//				while(1){
////					LCD_clearScreen();
////					LCD_moveCursor(0, 0);
////					LCD_displayString("Turn on Motor");
////					LCD_moveCursor(1, 0);
////					LCD_displayString("Turn off Motor");
////					key=KEYPAD_getPressedKey();
////					_delay_ms(250);
//					motorMainMenu();
////					if(key==1){
////						LCD_clearScreen();
////						LCD_moveCursor(0, 0);
////						LCD_displayString("Motor is ON");
////						_delay_ms(500);
////						TurnOnMotor();
////					}else if(key==2){
////						LCD_clearScreen();
////						LCD_moveCursor(0, 0);
////						LCD_displayString("Motor is OFF");
////						_delay_ms(500);
////						TurnOffMotor();
////					}else if(key==3){
////						controlPasswordMenu();
////						break;
////					}
//				}
//			}else if(key==2){
//				while(1){
////					if(!(PINA&(1<<0))){
////						TOGGLE_BIT(PORTA,4);
////						_delay_ms(100);
////					}if(!(PINA&(1<<1))){
////						TOGGLE_BIT(PORTA,5);
////						_delay_ms(100);
////					}if(!(PINA&(1<<2))){
////						TOGGLE_BIT(PORTA,6);
////						_delay_ms(100);
////					}if(!(PINA&(1<<3))){
////						TOGGLE_BIT(PORTA,7);
////						_delay_ms(100);
////					}
////					_delay_ms(100);
//					controlLEDList();
//				}
//			}else if(key==3){
//				controlPasswordMenu();
//			}
////		}else if(key==2){
////			Main_Menu();
//		}

	}

}

void Main_Menu(){
	LCD_moveCursor(0, 0);
	LCD_displayString("1)Edit Password");
	LCD_moveCursor(1, 0);
	LCD_displayString("2)Enter Password");
	key=KEYPAD_getPressedKey();
	_delay_ms(250);
	if(key==1){
		Set_Password();
	}else if(key==2){
		Enter_Password();
	}else{
		Main_Menu();
	}
}

void Set_Password(){

	LCD_clearScreen();
	LCD_moveCursor(0, 0);

	while(i<PASSWORD_LENGTH){

		key=KEYPAD_getPressedKey();
		_delay_ms(250);
		LCD_intgerToString(key);
		Password[i]=key;
		i++;
	}
	i=0;
	Main_Menu();
}

uint8 Enter_Password(){

	uint8 enteredPassword[PASSWORD_LENGTH]={0};
	flagCorrectPass=0;

	LCD_clearScreen();
	LCD_moveCursor(0, 0);

	while(i<PASSWORD_LENGTH){
		enteredPassword[i]=KEYPAD_getPressedKey();
		_delay_ms(250);
		LCD_intgerToString(enteredPassword[i]);
		i++;
	}
	i=0;
	while(i<PASSWORD_LENGTH){
		if(Password[i]==enteredPassword[i]){
			i++;
		}else{
			LCD_clearScreen();
			LCD_moveCursor(0, 0);
			LCD_displayString("Incorrect Pass");
			_delay_ms(2000);
			flagCorrectPass=0;
			i=0;
			return 0;
		}
	}
	flagCorrectPass=1;
//	enteredPassword=1;
	i=0;
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("Correct Password");
	_delay_ms(1000);
	controlPasswordMenu();
	return 1;
}

void controlPasswordMenu(){

	flagCorrectPass=0;
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("1)Control Menu");
	LCD_moveCursor(1, 0);
	LCD_displayString("2)Password Menu");
	key=KEYPAD_getPressedKey();
	_delay_ms(250);
	if(key==1){
		motorLEDList();
//		control menu LED,MOTOR,DISPLAY DATA,BACK TO MAIN
	}else if(key==2){
		LCD_clearScreen();
		Main_Menu();
	}else{
		controlPasswordMenu();
	}
}

void motorLEDList(){
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("1)Control Motor");
	LCD_moveCursor(1, 0);
	LCD_displayString("2)Control LED");
	LCD_moveCursor(2, 0);
	LCD_displayString("3)Control Menu");
	LCD_moveCursor(3, 0);
	LCD_displayString("4)Display Status");
	key=KEYPAD_getPressedKey();
	_delay_ms(250);
	if(key==1){
		motorMainMenu();
	}else if(key==2){
		//led control Function
		controlLEDList();
	}else if(key==3){
		controlPasswordMenu();
	}else if(key==4){
		//display status function
	}else{
		motorLEDList();
	}
}

void motorMainMenu(){
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("1)Turn on Motor");
	LCD_moveCursor(1, 0);
	LCD_displayString("2)Turn off Motor");
	LCD_moveCursor(2, 0);
	LCD_displayString("3)Control Menu");
	key=KEYPAD_getPressedKey();
	_delay_ms(250);
	if(key==1){
		LCD_clearScreen();
		LCD_moveCursor(0, 0);
		LCD_displayString("Motor is ON");
		_delay_ms(500);
		TurnOnMotor();
	}else if(key==2){
		LCD_clearScreen();
		LCD_moveCursor(0, 0);
		LCD_displayString("Motor is OFF");
		_delay_ms(500);
		TurnOffMotor();
	}else if(key==3){
		controlPasswordMenu();
	}
}

void controlLEDList(){

	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("Press the Push");
	LCD_moveCursor(1, 0);
	LCD_displayString("button to goback");
	while(1){
	if(!(PINA&(1<<0))){
		TOGGLE_BIT(PORTA,4);
		//_delay_ms(100);
	}if(!(PINA&(1<<1))){
		TOGGLE_BIT(PORTA,5);
		//_delay_ms(100);
	}if(!(PINA&(1<<2))){
		TOGGLE_BIT(PORTA,6);
		//_delay_ms(100);
	}if(!(PINA&(1<<3))){
		TOGGLE_BIT(PORTA,7);
		//_delay_ms(100);
	}if(key==5){
		motorLEDList();
	}
	_delay_ms(100);
	}
}

void TurnOnMotor(){
	DcMotor_Rotate(CW,50);
}

void TurnOffMotor(){
	DcMotor_Rotate(STOP, 0);
}

void flashLED(){
	flash+=flash+1;
}

void INT0_Init(void)
{
	GPIO_setupPinDirection(3, 2, PIN_INPUT);
	GPIO_writePin(3, 2, LOGIC_HIGH);

	/* Trigger INT0 with the falling edge (ISC01 = 1 , ISC00 = 0) */
	SET_BIT(MCUCR,ISC01);
	SET_BIT(MCUCR,ISC00);

	SET_BIT(GICR,INT0);      /* Enable external interrupt pin INT0 */
}

/*******************************************************************************
 *                          INTERRUPT SERVICE ROUTINES                         *
 *******************************************************************************/

/* INT0 (ISR) that is responsible */
ISR(INT0_vect)
{
	motorLEDList();
	_delay_ms(30);       /* Just a 30ms delay due to Button-debouncing */
}


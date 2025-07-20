#ifndef PLS_H
#define PLS_H
#include "stm32f4xx.h"
#include<stdio.h>


#define GENERAL_SETBIT(REG,BIT_VAL, BIT_NUMBER) ((REG) |= ((BIT_VAL) << (BIT_NUMBER)))//ACTIVE LES BITS DANS UN REGISTRE

#define GENERAL_CLEARBIT(REG,BIT_VAL,BIT_NUMBER) ((REG) &=~((BIT_VAL)<<(BIT_NUMBER))) //EFFACE LES BITS DANS UN REGISTRE

#define GENERAL_TOGGLEBIT(REG, BIT_VAL, BIT_NUMBER) ((REG) ^= ((BIT_VAL) << (BIT_NUMBER)))//TOGGLE LES BITS DANS UN REGISTRE


#define REVERSE_BIT(BITVAL,NUMBER)  (((~(BITVAL)) & ((1U<<NUMBER)-1))) //INVERSE LES BITS ET MASQUE AVEC {1U<<NUMBER) - 1}(LE NOMBRE DE BITS À MASQUER) LA RAISON EST D'UTILISER GENERAL_SETBIT ET CLEAR_BIT AVEC 
// LE MÊME BITVAL


#define GENERAL_SETPIN(REG, BIT_VAL, PIN_NUMBER) (GENERAL_SETBIT(REG, BIT_VAL, 2*PIN_NUMBER))//ACTIVE LES PINS AU LIEU DES BITS, UTILISE SIMPLEMENT LE PRÉCÉDENT GENERAL_SETBIT

#define GENERAL_CLEARPIN(REG, BIT_VAL, PIN_NUMBER) (GENERAL_CLEARBIT(REG, BIT_VAL, 2*PIN_NUMBER))//EFFACE LES PINS AU LIEU DES BITS

#define READ_REGS(GPIO,REG,DATA) ((DATA=GPIO->REG))//LIT LES VALEURS DES REGISTRES





typedef enum  {
	PIN_0=0 ,
	PIN_1=1,
	PIN_2=2 ,
	PIN_3=3 ,
	PIN_4=4 ,
	PIN_5=5 ,
	PIN_6=6 ,
	PIN_7=7 ,
	PIN_8=8 ,
	PIN_9=9,
	PIN_10=10 ,
	PIN_11=11 ,
	PIN_12=12 ,
	PIN_13=13 ,
	PIN_14=14 ,
	PIN_15=15 ,

	} PIN_NUMBER;

	
			
	typedef enum{
		
			HIGH=0b1,
			LOW=0b0,
		
			b00=0b00,
		
			b01=0b01,
		
			b10=0b10,
		
		  b11=0b11,
		
	} BITVAL;//


	typedef enum{
		
		GPIO_A=0,
		GPIO_B=1,
		GPIO_C=2,
		GPIO_D=3,
		GPIO_E=4,
		GPIO_F=5,
		GPIO_G=6,
		GPIO_H=7,
		GPIO_I=8,
		
	} GPIO_SELECT; //Énumération pour sélectionner GPIO à utiliser dans les registres de l'horloge
	
		
			typedef enum {
    GPIO_MODER_INPUT       = 0b00,  // Mode entrée
    GPIO_MODER_OUTPUT      = 0b01,  // Mode sortie
    GPIO_MODER_AF          = 0b10,  // Mode fonction alternative
    GPIO_MODER_ANALOG      = 0b11 ,  // Mode analogique


    GPIO_OTYPER_PP        = 0b0,  // Sortie push-pull
    GPIO_OTYPER_OD        = 0b1 ,  // Sortie open-drain

    GPIO_OSPEEDR_LOW      = 0b00,  // Vitesse faible
    GPIO_OSPEEDR_MEDIUM   = 0b01,  // Vitesse moyenne
    GPIO_OSPEEDR_HIGH     = 0b10,  // Haute vitesse
    GPIO_OSPEEDR_VERYHIGH = 0b11 ,  // Très haute vitesse


    GPIO_NOPULL           = 0b00,  // Pas de résistance pull-up/pull-down
    GPIO_PULLUP           = 0b01,  // Résistance pull-up
    GPIO_PULLDOWN         = 0b10,  // Résistance pull-down

	} CONFIGURATION;//énumération qui détermine les bits de configuration des registres
	
		
		
		
		
void GPIO_MODER_CONFIGURATION(GPIO_TypeDef* GPIOx,CONFIGURATION CONF_Bit,PIN_NUMBER Pin );
void GPIO_OTYPER_CONFIGURATION(GPIO_TypeDef* GPIOx,CONFIGURATION CONF_Bit,PIN_NUMBER Pin );
void GPIO_OSPEEDR_CONFIGURATION(GPIO_TypeDef* GPIOx,CONFIGURATION CONF_Bit,PIN_NUMBER Pin );
void GPIO_PUPDR_CONFIGURATION(GPIO_TypeDef* GPIOx,CONFIGURATION CONF_Bit,PIN_NUMBER Pin );	
	
void GPIO_Write_Pin(GPIO_TypeDef* GPIOx,BITVAL Bit,PIN_NUMBER Pin );
	
void GPIO_Toggle_Pin(GPIO_TypeDef* GPIOx,PIN_NUMBER Pin);
		
BITVAL GPIO_Read_Pin(GPIO_TypeDef* GPIOx,PIN_NUMBER Pin );
	
void GPIO_CLOCK_EN(GPIO_SELECT GPIO);
void GPIO_RESET(GPIO_SELECT GPIO);
	
void delay(volatile unsigned int i);
#endif
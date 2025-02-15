#ifndef INC_DRIVER_SPI_H_
#define INC_DRIVER_SPI_H_

#include "nrf52.h"

/*
 * Configuration structure for SPIx peripheral
 */

typedef struct
{
	uint8_t CPHA;
	uint8_t CPOL;
	uint32_t Frequency;
}SPI_Config_t;

typedef struct
{
	GPIOP_RegDef_t* port;
	uint8_t pin;
}SPI_PSEL_t;

/*
 * Handle structure for USARTx peripheral
 */

typedef struct{
	SPI_Config_t SPI_Config;
	SPI_RegDef_t *pSPIx;
    SPI_PSEL_t MOSI;
    SPI_PSEL_t MISO;
    SPI_PSEL_t SCK;
}SPI_Handle_t;


/*
 *@SPI_CPHA
 *Possible options for SPI_CPHA
 */
#define SPI_CPHA_HIGH	1
#define SPI_CPHA_LOW	0


/*
 *@SPI_CPOL
 *Possible options for SPI_POL
 */
#define SPI_CPOL_HIGH	1
#define SPI_CPOL_LOW	0

/*
 *@SPI_FREQUENCY
 *Possible options for SPI_Frequency
 */
#define SPI_FREQUENCY_K125      0x02000000U
#define SPI_FREQUENCY_K250      0x04000000U
#define SPI_FREQUENCY_K500      0x08000000U
#define SPI_FREQUENCY_M1        0x10000000U
#define SPI_FREQUENCY_M2        0x20000000U
#define SPI_FREQUENCY_M4        0x40000000U
#define SPI_FREQUENCY_M8        0x80000000U

/*
 * SPI Registers 
 */

#define SPI_PSEL_PIN           0
#define SPI_PSEL_PORT          5
#define SPI_PSEL_CONNECT       31


/********************************************************************************************
 * 								APIs supported by this driver
 * 					for more information check the function definitions
 ********************************************************************************************/




/*
 *		Peripheral Control
 */

void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);



/*
 * 	Init and De-init
 */

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);


/*
 * 	Data Send and Receive
 */


void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);


#endif /* INC_DRIVER_SPI_H_ */

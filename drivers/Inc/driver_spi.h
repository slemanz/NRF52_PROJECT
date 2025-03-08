/*
 * ==========================================================================================
 *      File: driver_spi.h
 *      Author: William Sleman
 *
 *      Description:
 *      This header file defines structures and function prototypes for configuring 
 *      and managing the Serial Peripheral Interface (SPI). It supports setting up 
 *      SPI configuration parameters, handling communication through manager operations,
 *      and managing the data transmission and reception.
 *
 *      Note:
 *      For function definitions and detailed driver behavior, see the implementation file: 
 *      driver_spi.c.
 * ==========================================================================================
 */
#ifndef INC_DRIVER_SPI_H_
#define INC_DRIVER_SPI_H_

#include "nrf52.h"


/*
 ********************************************************************************************
 * @struct          - SPI_Config_t
 *
 * @brief           - Configuration structure for the SPI peripheral, holding 
 *                    settings such as clock phase (CPHA), clock polarity (CPOL), 
 *                    and communication frequency.
 *
 * @field           - CPHA: Specifies the clock phase setting, defined by possible 
 *                    options from @SPI_CPHA.
 *
 * @field           - CPOL: Specifies the clock polarity setting, defined by 
 *                    possible options from @SPI_CPOL.
 *
 * @field           - Frequency: The communication frequency for SPI, defined 
 *                    by possible values from @SPI_FREQUENCY.
 *
 * @Note            - none
 *
 ********************************************************************************************
 */

typedef struct
{
	uint8_t CPHA;
	uint8_t CPOL;
	uint32_t Frequency;
}SPI_Config_t;


/*
 ********************************************************************************************
 * @struct          - SPI_PSEL_t
 *
 * @brief           - Structure for configuring the pin selection for SPI,
 *                    including the port and pin number for each SPI signal (MOSI, MISO, SCK).
 *
 * @field           - port: Pointer to the GPIO port for the pin.
 *
 * @field           - pin: The pin number within the port.
 *
 * @Note            - none
 *
 ********************************************************************************************
 */

typedef struct
{
	GPIOP_RegDef_t* port;
	uint8_t pin;
}SPI_PSEL_t;


/*
 ********************************************************************************************
 * @struct          - SPI_Handle_t
 *
 * @brief           - Handle structure for the SPI peripheral, containing the 
 *                    configuration settings and register pointer for SPI operations.
 *
 * @field           - SPI_Config: Holds the configuration settings for the SPI, 
 *                    encapsulated in the SPI_Config_t structure.
 *
 * @field           - pSPIx: Pointer to the SPI peripheral base address.
 *
 * @field           - MOSI: Pin configuration for Master Out Slave In line.
 *
 * @field           - MISO: Pin configuration for Master In Slave Out line.
 *
 * @field           - SCK: Pin configuration for Serial Clock line.
 *
 * @Note            - none
 *
 ********************************************************************************************
 */

typedef struct{
	SPI_Config_t SPI_Config;
	SPI_RegDef_t *pSPIx;
    PSEL_t MOSI;
    PSEL_t MISO;
    PSEL_t SCK;
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
 *                              APIs supported by this driver
 *                  for more information check the function definitions
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

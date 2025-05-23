/*
 * ==========================================================================================
 *      File: driver_saadc.c
 *      Author: William Sleman
 *
 *      Description:
 *      This implementation file contains the definitions for the functions that manage
 *      the Successive Approximation Analog-to-Digital Converter (SAADC). It includes 
 *      initialization, calibration of the ADC, the reading of ADC values, and the selection
 *      of input pins for the ADC.
 *
 *      Note:
 *      For structure definitions and function prototypes, see the header file: 
 *      driver_saadc.h.
 * ==========================================================================================
 */
#include "driver_saadc.h"

volatile int16_t result_adc = 0;

/*
 ********************************************************************************************
 * @function        - saadc_init
 *
 * @brief           - Initializes the SAADC with the specified configurations from the 
 *                    SAADC_Handle_t structure. This includes configuring the gain, 
 *                    mode, reference voltage selection, and connecting the specified 
 *                    positive and negative channels.
 *
 * @param[in]       - pSAADCHandle: Pointer to a SAADC_Handle_t structure that contains 
 *                    the configuration settings for the SAADC.
 *
 * @Note            - After initialization, the calibrate function is called to ensure 
 *                    correct ADC operation.
 ********************************************************************************************
 */
void saadc_init(SAADC_Handle_t *pSAADCHandle)
{
    uint32_t temp = 0;

    temp =  (pSAADCHandle->GAIN << SAADC_CH_CONFIG_GAIN_BIT) |
            (pSAADCHandle->MODE << SAADC_CH_CONFIG_MODE_BIT) |
            (pSAADCHandle->REFSEL << SAADC_CH_CONFIG_REFSEL_BIT) |
            (pSAADCHandle->RESN << SAADC_CH_CONFIG_RESN_BIT) |
            (pSAADCHandle->RESP << SAADC_CH_CONFIG_RESP_BIT) |
            (pSAADCHandle->TACQ << SAADC_CH_CONFIG_TACQ_BIT);

    SAADC->CH[pSAADCHandle->CHANNEL].CONFIG = temp;
    SAADC->CH[pSAADCHandle->CHANNEL].PSELP  = pSAADCHandle->PSELP;
    SAADC->CH[pSAADCHandle->CHANNEL].PSELN  = pSAADCHandle->PSELN;

    SAADC->RESOLUTION = pSAADCHandle->RESOLUTION;

    SAADC->RESULT.MAXCNT = 1;
    SAADC->RESULT.PTR   = (uint32_t)&result_adc;

    SAADC->ENABLER = 1;
    saadc_calibrate();
}


/*
 ********************************************************************************************
 * @function        - saadc_calibrate
 *
 * @brief           - Calibrates the offset of the SAADC to ensure accurate readings.
 *
 * @Note            - This function waits for the calibration to complete and clears
 *                    the calibration done event.
 ********************************************************************************************
 */

 void saadc_calibrate(void)
 {
    SAADC->TASKS_CALIBRATEOFFSET = 1;
    while(SAADC->EVENTS_CALIBRATEDONE == 0);
    SAADC->EVENTS_CALIBRATEDONE = 0;
    while(SAADC->STATUS == (1 << 0));
 }


 /*
 ********************************************************************************************
 * @function        - saadc_read
 *
 * @brief           - Starts a conversion on the configured SAADC channel and waits for the 
 *                    result to be available. Returns the ADC result or 0 if an error is 
 *                    detected (negative result).
 *
 * @return          - uint16_t: The ADC reading or 0 if an error occurred.
 ********************************************************************************************
 */

uint16_t saadc_read(void)
{
   SAADC->TASKS_START = 1;
   while (SAADC->EVENTS_STARTED == 0);
   SAADC->EVENTS_STARTED = 0;

   while (SAADC->EVENTS_RESULTDONE == 0);
   SAADC->EVENTS_RESULTDONE = 0;

   // Do a SAADC sample, will put the result in the configured RAM buffer.
   SAADC->TASKS_SAMPLE = 1;
   while (SAADC->EVENTS_END == 0);
   SAADC->EVENTS_END = 0;

   if( result_adc & (1 << 15)) return 0;
   return result_adc;
}


/*
 ********************************************************************************************
 * @function        - saadc_selectInp
 *
 * @brief           - Selects the input pin for channel 0 of the SAADC. This function can 
 *                    only be used when channel 0 is active.
 *
 * @param[in]       - psel: The positive input selection based on @SAADC_PSEL options.
 *
 * @Note            - The SAADC must be disabled before changing the input selection.
 ********************************************************************************************
 */

 void saadc_selectInp(uint8_t psel)
 {
    SAADC->ENABLER = 0;
    SAADC->CH[0].PSELP  = psel;
    SAADC->ENABLER = 1;
 }
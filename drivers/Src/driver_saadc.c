#include "driver_saadc.h"

 void saadc_init(SAADC_Handle_t *pSAADCHandle)
 {
    uint32_t temp = 0;

    temp = ((pSAADCHandle->GAIN << SAADC_CH_CONFIG_GAIN_BIT) | (pSAADCHandle->MODE << SAADC_CH_CONFIG_MODE_BIT) |
            (pSAADCHandle->REFSEL << SAADC_CH_CONFIG_REFSEL_BIT) | (pSAADCHandle->RESN << SAADC_CH_CONFIG_RESN_BIT) |
            (pSAADCHandle->BURST << SAADC_CH_CONFIG_BURST_BIT) | (pSAADCHandle->RESP << SAADC_CH_CONFIG_RESP_BIT) |
            (pSAADCHandle->TACQ << SAADC_CH_CONFIG_TACQ_BIT));

    SAADC->CH[pSAADCHandle->CHANNEL].CONFIG = temp;
    SAADC->CH[pSAADCHandle->CHANNEL].PSELP  = pSAADCHandle->PSELP;
    SAADC->CH[pSAADCHandle->CHANNEL].PSELN  = pSAADCHandle->PSELN;
 }

 void saadc_setResolution(uint8_t res)
 {
    SAADC->RESOLUTION = res;
 }
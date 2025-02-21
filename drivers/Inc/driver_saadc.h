#ifndef DRIVER_SAADC_H_
#define DRIVER_SAADC_H_

#include "nrf52.h"

typedef struct
{
    uint8_t CHANNEL;
    uint8_t RESP;
    uint8_t RESN;
    uint8_t GAIN;
    uint8_t REFSEL;
    uint8_t TACQ;
    uint8_t MODE;
    uint8_t BURST;
    uint8_t PSELP;
    uint8_t PSELN;
    uint8_t RESOLUTION;
}SAADC_Handle_t;


/*
 *@SAADC_CHANNEL
 *Possible options for SAADC_CHANNEL
 */

#define SAADC_CHANNEL_0                 0
#define SAADC_CHANNEL_1                 1
#define SAADC_CHANNEL_2                 2
#define SAADC_CHANNEL_3                 3
#define SAADC_CHANNEL_4                 4
#define SAADC_CHANNEL_5                 5
#define SAADC_CHANNEL_6                 6
#define SAADC_CHANNEL_7                 7

/*
 *@SAADC_RES
 *Possible options for SAADC_RES
 */

 #define SAADC_RES_BYPASS               0
 #define SAADC_RES_PULLDOWN             1
 #define SAADC_RES_PULLUP               2
 #define SAADC_RES_VDD1_2               3

/*
 *@SAADC_GAIN
 *Possible options for SAADC_GAIN
 */

 #define SAADC_GAIN_1_6                 0
 #define SAADC_GAIN_1_5                 1
 #define SAADC_GAIN_1_4                 2
 #define SAADC_GAIN_1_3                 3
 #define SAADC_GAIN_1_2                 4
 #define SAADC_GAIN_1                   5
 #define SAADC_GAIN_2                   6
 #define SAADC_GAIN_4                   7

/*
 *@SAADC_REFSEL
 *Possible options for SAADC_REFSEL
 */

#define SAADC_REFSEL_INTERNAL           0
#define SAADC_REFSEL_VDD_1_4            1

/*
 *@SAADC_TACQ
 *Possible options for SAADC_TACQ
 */

#define SAADC_TACQ_3US                  0
#define SAADC_TACQ_5US                  1
#define SAADC_TACQ_10US                 2
#define SAADC_TACQ_15US                 3
#define SAADC_TACQ_20US                 4
#define SAADC_TACQ_40US                 5

/*
 *@SAADC_MODE
 *Possible options for SAADC_MODE
 */

#define SAADC_MODE_SE                   0
#define SAADC_MODE_DIFF                 1

/*
 *@SAADC_BURST
 *Possible options for SAADC_BURST
 */

#define SAADC_BURST_DIS                 0
#define SAADC_BURST_EN                  1

/*
 *@SAADC_PSEL
 *Possible options for SAADC_PSEL
 */

 #define SAADC_PSEL_NC                  0
 #define SAADC_PSEL_AIN0                1
 #define SAADC_PSEL_AIN1                2
 #define SAADC_PSEL_AIN2                3
 #define SAADC_PSEL_AIN3                4
 #define SAADC_PSEL_AIN4                5
 #define SAADC_PSEL_AIN5                6
 #define SAADC_PSEL_AIN6                7
 #define SAADC_PSEL_AIN7                8
 #define SAADC_PSEL_VDD                 9
 #define SAADC_PSEL_VDDHDIV5            0xD

/*
 *@SAADC_RESOLUTION
 *Possible options for SAADC_RESOLUTION
 */

#define SAADC_RESOLUTION_8BIT           0
#define SAADC_RESOLUTION_10BIT          1
#define SAADC_RESOLUTION_12BIT          2
#define SAADC_RESOLUTION_14BIT          3

/*
 *@SAADC_OVERSAMPLE
 *Possible options for SAAC_OVERSAMPLE
 */

 #define SAADC_OVERSAMPLE_BYPASS        0
 #define SAADC_OVERSAMPLE_2X            1
 #define SAADC_OVERSAMPLE_4X            2
 #define SAADC_OVERSAMPLE_8X            3
 #define SAADC_OVERSAMPLE_16X           4
 #define SAADC_OVERSAMPLE_32X           5
 #define SAADC_OVERSAMPLE_64X           6
 #define SAADC_OVERSAMPLE_128X          7
 #define SAADC_OVERSAMPLE_256X          8

/* **********************************
 * SAADC Register bits
 * **********************************/

#define SAADC_CH_CONFIG_RESP_BIT        0
#define SAADC_CH_CONFIG_RESN_BIT        4
#define SAADC_CH_CONFIG_GAIN_BIT        8
#define SAADC_CH_CONFIG_REFSEL_BIT      12
#define SAADC_CH_CONFIG_TACQ_BIT        16
#define SAADC_CH_CONFIG_MODE_BIT        20
#define SAADC_CH_CONFIG_BURST_BIT       24



 


/********************************************************************************************
 * 								APIs supported by this driver
 * 					for more information check the function definitions
 ********************************************************************************************/

 void saadc_init(SAADC_Handle_t *pSAADCHandle);
 void saadc_calibrate(void);
 void saadc_selectInp(uint8_t psel); // works only when channel 0 is been used
 uint16_t saadc_read(void);

#endif /* DRIVER_SAADC_H_ */
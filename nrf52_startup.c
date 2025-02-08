#include <stdint.h>

#define SRAM_START      0x20000000U
#define SRAM_SIZE       (256 * 1024) 
#define SRAM_END        ((SRAM_START) + (SRAM_SIZE))

#define STACK_START     (SRAM_END)

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;

extern uint32_t _sbss;
extern uint32_t _ebss;


/* Prototype of main*/
int main(void);

void __libc_init_array(void);



/* Functions prototypes of NRF52840 system exceptions and IRQ handlers */
void Reset_Handler(void);


void NMI_Handler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler              (void) __attribute__ ((weak, alias("Default_Handler"))); 
void MemManage_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID0_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void ID1_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void ID2_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void ID3_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void ID4_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void ID5_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void ID6_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void ID7_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void ID8_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void ID9_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void ID10_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID11_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID12_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID13_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID14_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID15_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID16_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID17_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID18_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID19_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID20_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID21_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID22_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID23_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID24_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID25_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID26_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID27_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID28_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID29_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID30_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID31_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID32_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID33_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID34_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID35_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID36_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID37_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID38_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID39_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID40_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID41_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID42_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID43_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID44_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID45_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID46_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void ID47_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));

uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
    STACK_START,
    (uint32_t)Reset_Handler,
    (uint32_t)NMI_Handler,
    (uint32_t)HardFault_Handler,
    (uint32_t)MemManage_Handler,
    (uint32_t)BusFault_Handler,
    (uint32_t)UsageFault_Handler,
    0,
    0,
    0,
    0,
    (uint32_t)SVC_Handler,
    (uint32_t)DebugMon_Handler,
    0,
    (uint32_t)PendSV_Handler,
    (uint32_t)SysTick_Handler,
    (uint32_t)ID0_IRQHandler,
    (uint32_t)ID1_IRQHandler,
    (uint32_t)ID2_IRQHandler,
    (uint32_t)ID3_IRQHandler,
    (uint32_t)ID4_IRQHandler,
    (uint32_t)ID5_IRQHandler,
    (uint32_t)ID6_IRQHandler,
    (uint32_t)ID7_IRQHandler,
    (uint32_t)ID8_IRQHandler,
    (uint32_t)ID9_IRQHandler,
    (uint32_t)ID10_IRQHandler,
    (uint32_t)ID11_IRQHandler,
    (uint32_t)ID12_IRQHandler,
    (uint32_t)ID13_IRQHandler,
    (uint32_t)ID14_IRQHandler,
    (uint32_t)ID15_IRQHandler,
    (uint32_t)ID16_IRQHandler,
    (uint32_t)ID17_IRQHandler,
    (uint32_t)ID18_IRQHandler,
    (uint32_t)ID19_IRQHandler,
    (uint32_t)ID20_IRQHandler,
    (uint32_t)ID21_IRQHandler,
    (uint32_t)ID22_IRQHandler,
    (uint32_t)ID23_IRQHandler,
    (uint32_t)ID24_IRQHandler,
    (uint32_t)ID25_IRQHandler,
    (uint32_t)ID26_IRQHandler,
    (uint32_t)ID27_IRQHandler,
    (uint32_t)ID28_IRQHandler,
    (uint32_t)ID29_IRQHandler,
    (uint32_t)ID30_IRQHandler,
    (uint32_t)ID31_IRQHandler,
    (uint32_t)ID32_IRQHandler,
    (uint32_t)ID33_IRQHandler,
    (uint32_t)ID34_IRQHandler,
    (uint32_t)ID35_IRQHandler,
    (uint32_t)ID36_IRQHandler,
    (uint32_t)ID37_IRQHandler,
    (uint32_t)ID38_IRQHandler,
    (uint32_t)ID39_IRQHandler,
    (uint32_t)ID40_IRQHandler,
    (uint32_t)ID41_IRQHandler,
    (uint32_t)ID42_IRQHandler,
    (uint32_t)ID43_IRQHandler,
    (uint32_t)ID44_IRQHandler,
    (uint32_t)ID45_IRQHandler,
    (uint32_t)ID46_IRQHandler,
    (uint32_t)ID47_IRQHandler,
};

void Default_Handler(void)
{
    while(1);
}

void Reset_Handler(void)
{
    // copy .data section to SRAM
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;

    uint8_t *pDst = (uint8_t*)&_sdata; //sram
    uint8_t *pSrc = (uint8_t*)&_la_data; //flash

    for(uint32_t i = 0; i < size; i++)
    {
        *pDst++ = *pSrc++;
    }

    // Init the .bss section to zero in SRAM
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint8_t*)&_sbss;

    for(uint32_t i = 0; i < size; i++)
    {
        *pDst++ = 0;
    }


    // call init function of std. library
    __libc_init_array();

    // call main()
    main();
}

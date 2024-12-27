#include "stm32f401xx.h"
#include "core/system.h"
#include "core/lcd.h"
#include "core/buttons.h"


// Function delay
void delay_cycles(uint32_t cycles)
{
    while (cycles-- > 0) {
        __asm("NOP"); // No operation for delay
    }
}

typedef enum state_t {
    State_Input,
    State_UpdateLcd,
    State_Start
} state_t;


int main(void)
 {
    system_setup();
    gpio_setup();
    buttons_init();
    lcd_init();
    lcd_display_clear();
    lcd_display_return_home();
    _printf1("Iniciando...");
    delay_cycles(4000000);

    uint64_t start_time = system_get_ticks();
    uint8_t buttonState = 0x00;
    uint8_t state = State_Input;
    uint8_t dir = 0;
    uint8_t motor = 0;
    int step = 900;
    int step_r = step/10;
    int step_p =  step % 10;



    lcd_display_clear();
    _printf1("Angulo: %d.%d", step_r, step_p);
    _printf2("PARADO - HOR.");
    lcd_display_return_home();

    while (1)
    {
        switch (state)
        {
        case State_Input:
            buttonState = buttons_read();
            if(buttonState & (1 << 3))
            {
                motor = 1;
                state = State_UpdateLcd;
                while(buttons_read() & (1 << 3)) __asm("NOP");
            }

            if(buttonState & (1 << 2))
            {
                dir ^= (1 << 0);
                state = State_UpdateLcd;
                while(buttons_read() & (1 << 2)) __asm("NOP");
            }

            if(buttonState & (1 << 1))
            {
                if(step <= 0)
                {
                    step = 0;
                }else
                {
                    step = step - 18;
                }
                state = State_UpdateLcd;
                while(buttons_read() & (1 << 1)) __asm("NOP");
            }

            if(buttonState & (1 << 0))
            {
                if(step >= 3600)
                {
                    step = 3600;
                }else
                {
                    step = step + 18;
                }
                state = State_UpdateLcd;
                while(buttons_read() & (1 << 0)) __asm("NOP");
            }

            break;

        case State_UpdateLcd:
            lcd_display_clear();
            step_r = step/10;
            step_p =  step % 10;
            _printf1("Angulo: %d.%d", step_r, step_p);
            if((dir == 0) && (motor == 0))
            {
                _printf2("PARADO - HOR.");
            }else if((dir == 1) && (motor == 0))
            {
                _printf2("PARADO - A-HOR.");
            }else if((dir == 0) && (motor == 1))
            {
                _printf2("GIRAND - HOR.");
            }else if((dir == 1) && (motor == 1))
            {
                _printf2("GIRAND - A-HOR.");
            }
            lcd_display_return_home();

            if(!dir)
            {
                GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_4, GPIO_PIN_SET);
            }else
            {
                GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_4, GPIO_PIN_RESET);
            }

            state = State_Input;
            if(motor == 1) state = State_Start;

            break;

        case State_Start:
            for(uint8_t i = 0; i < (step/18); i++)
            {
                GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_SET);
                delay_cycles(50000);
                GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_RESET);
                delay_cycles(50000);
            }
            motor = 0;
            state = State_UpdateLcd;
            break;
        
        default:
            break;
        }

        if((system_get_ticks() - start_time) >= 1000)
        {
            GPIO_ToggleOutputPin(LED_PORT, LED_PIN);
            start_time = system_get_ticks();
        }


    }
}
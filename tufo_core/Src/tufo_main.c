#include "main.h"

void tufo_main(void)
{
    while(1)
    {
        LL_GPIO_TogglePin(GPIOE, LL_GPIO_PIN_3);
        LL_mDelay(500);
    }
}
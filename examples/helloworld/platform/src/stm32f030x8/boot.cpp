///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#include "internal-platform.hpp"

#include "platform-library/stm32f0xx/boot.hpp"
#include "platform-library/stm32f0xx/hal/stm32f0xx_ll_bus.h"
#include "platform-library/stm32f0xx/hal/stm32f0xx_ll_cortex.h"
#include "platform-library/stm32f0xx/hal/stm32f0xx_ll_rcc.h"
#include "platform-library/stm32f0xx/hal/stm32f0xx_ll_system.h"
// #include "platform-library/stm32f0xx/hal/stm32f0xx_ll_tim.h"
#include "platform-library/stm32f0xx/hal/stm32f0xx_ll_utils.h"

namespace helloworld {
using stm32f0xx::GPIOPin;
using stm32f0xx::USARTDevID;
constexpr auto empty = stm32f0xx::empty;

// forward declarations
void boot_periph_clocks();
void boot_nvic();
void boot_system_clock();

stm32f0xx::SerialParams vcp_serial_params()
{
    stm32f0xx::SerialParams serial_params;
    serial_params.baud_rate  = 460800;
    serial_params.data_width = stm32f0xx::DataWidth::EIGHT;
    serial_params.stop_bits  = stm32f0xx::StopBits::ONE;
    serial_params.parity     = stm32f0xx::Parity::NONE;
    return serial_params;
}

bool boot(Platform &)
{
    InternalPlatform &platform = InternalPlatform::instance();

    // boot the system
    boot_periph_clocks();
    boot_nvic();
    boot_system_clock();
    boot(platform.clock);

    // boot the peripherals via the pinout
    boot(platform.debug, GPIOPin::PA0);
    boot(empty, GPIOPin::PA1);
    boot(platform.vcp,
         GPIOPin::PA2,
         GPIOPin::PA3,
         USARTDevID::USART_2,
         vcp_serial_params(),
         platform.clock);
    boot(empty, GPIOPin::PA4);
    boot(platform.led, GPIOPin::PA5);
    boot(empty, GPIOPin::PA6);
    // ...
    boot(empty, GPIOPin::PA15);
    boot(empty, GPIOPin::PB0);
    // ...
    boot(empty, GPIOPin::PB15);
    boot(empty, GPIOPin::PC0);
    // ...
    boot(platform.user_btn, GPIOPin::PC13);
    boot(empty, GPIOPin::PC14);
    // ...

    return true;
}

void boot_periph_clocks()
{
    // Enable peipheral clocks
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);

    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);

    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_USART1);

    // LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);
    // LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
    // LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM15);
}

void boot_nvic()
{  // System interrupt init
    // SVC_IRQn interrupt configuration
    NVIC_SetPriority(SVC_IRQn, 0);
    // PendSV_IRQn interrupt configuration
    NVIC_SetPriority(PendSV_IRQn, 0);
    // SysTick_IRQn interrupt configuration
    NVIC_SetPriority(SysTick_IRQn, 0);
    /* DMA1_Channel2_3_IRQn interrupt configuration */
    NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0);
    /* DMA1_Channel4_5_IRQn interrupt configuration */
    NVIC_SetPriority(DMA1_Channel4_5_IRQn, 0);

    NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
    NVIC_EnableIRQ(DMA1_Channel4_5_IRQn);
}

void boot_system_clock()
{
    // set up the clock
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
    while (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1)
    {
    }

    // set and wait till HSI is ready
    LL_RCC_HSI_Enable();
    while (LL_RCC_HSI_IsReady() != 1)
    {
    }

    LL_RCC_HSI_SetCalibTrimming(16);
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_12);

    // set and wait till PLL is ready
    LL_RCC_PLL_Enable();
    while (LL_RCC_PLL_IsReady() != 1)
    {
    }

    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

    // set and wait till System clock is ready
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
    {
    }

    // set system clock to 48 mhz
    LL_Init1msTick(48000000);
    LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
    LL_SetSystemCoreClock(48000000);

    // set source for uart 1
    LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1);
}

void teardown(Platform &) {}

}  // namespace helloworld

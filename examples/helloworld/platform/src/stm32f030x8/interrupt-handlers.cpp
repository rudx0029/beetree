///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#include "internal-platform.hpp"

using InternalPlatform = helloworld::InternalPlatform;

///
/// System tick timer interrupt handler.
///
extern "C" void SysTick_Handler(void) { InternalPlatform::instance().clock.on_interrupt(); }

///
/// Handler for DMA1 channel 4 and 5 interrupts.
///
extern "C" void DMA1_Channel2_3_IRQHandler(void)
{
    // InternalPlatform::instance().link.on_dma_interrupt();
}

///
/// Handler for DMA1 channel 4 and 5 interrupts.
///
extern "C" void DMA1_Channel4_5_IRQHandler(void)
{
    InternalPlatform::instance().vcp.on_dma_interrupt();
}

///
/// Handler for USART2 global interrupt.
///
extern "C" void USART2_IRQHandler(void) {}
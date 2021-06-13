cmake_minimum_required(VERSION 3.0)
function(make_stm32f1xx_lib lib_name src inc defs libs)

  set(THIS_DIR ${CMAKE_SOURCE_DIR}/platforms/modules/platform-library/stm32f1xx)
  set(INCLUDE
    ${inc}
    "${THIS_DIR}/hal"
    "${THIS_DIR}/hal/Legacy"
    "${THIS_DIR}/system"
    "${THIS_DIR}/cmsis"
    )
  set(SOURCE
    ${src}
    "${THIS_DIR}/system/system_stm32f1xx.c"
    "${THIS_DIR}/hal/stm32f1xx_ll_utils.c"
    "${THIS_DIR}/hal/stm32f1xx_ll_dma.c"
    "${THIS_DIR}/hal/stm32f1xx_ll_gpio.c"
    "${THIS_DIR}/hal/stm32f1xx_ll_usart.c"
    "${THIS_DIR}/hal/stm32f1xx_ll_rcc.c"
    "${THIS_DIR}/hal/stm32f1xx_ll_tim.c"
    "${THIS_DIR}/hal/stm32f1xx_ll_exti.c"
    "${THIS_DIR}/helpers.cpp"
    "${THIS_DIR}/boot/boot-discrete-io.cpp"
    "${THIS_DIR}/boot/boot-system-clock.cpp"
    "${THIS_DIR}/boot/boot-serial-device-uart-dma.cpp"
    "${THIS_DIR}/boot/boot-pwm.cpp"
    "${THIS_DIR}/boot/boot-exti.cpp"
    "${THIS_DIR}/serial-device-uart-dma.cpp"
    "${THIS_DIR}/discrete-output.cpp"
    "${THIS_DIR}/discrete-input.cpp"
    "${THIS_DIR}/system-clock.cpp"
    "${THIS_DIR}/pwm.cpp"
    "${THIS_DIR}/counter.cpp"
    )
set(DEFS ${defs})
set(LIBS platform-library ${libs})
  
add_library(${lib_name} STATIC ${SOURCE})
target_link_libraries(${lib_name}  ${LIBS}) # link to the common code library
target_include_directories(${lib_name} PUBLIC ${INCLUDE})
target_compile_definitions(${lib_name} PUBLIC ${DEFS})

endfunction()


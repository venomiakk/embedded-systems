cmake_minimum_required(VERSION 3.12)

set(PROGRAM_NAME picocar)
set(PICO_BOARD pico_w)

include(pico_sdk_import.cmake)


project(picocar C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

pico_sdk_init()

# Wykonywanie raz dziala a raz nie

message("Running makefsdata python script")
execute_process(COMMAND
    python3 makefsdata.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

message("Running cppcheck for misra")
execute_process(COMMAND
    cppcheck --addon=misra --output-file=misc/misra-report.txt --suppress=*:lwipopts.h main.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

add_executable(picocar
    main.c
    cgi.c
    cgi.h
    ssi.c
    ssi.h
    servo.c
    servo.h
    motor.c
    motor.h
    lightsensor.c
    lightsensor.h
    speaker.c
    speaker.h
    diodes.c
    diodes.h
    distancesensor.c
    distancesensor.h
    accelerometer.c
    accelerometer.h
)

target_include_directories(${PROGRAM_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(picocar
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
    pico_stdlib
    pico_cyw43_arch_none # we need Wifi to access the GPIO, but we don't need anything else
    hardware_flash
    hardware_irq
    hardware_adc
    hardware_pwm
    hardware_i2c
    hardware_spi
    hardware_dma
    hardware_exception
    )

# enable usb output, disable uart output
pico_enable_stdio_usb(${PROGRAM_NAME} 0)
pico_enable_stdio_uart(${PROGRAM_NAME} 1)

pico_add_extra_outputs(picocar)

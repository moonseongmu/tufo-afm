project('tufo_afm', 'c', default_options: ['c_std=c23'])

src=[]

c_args=['-mcpu=cortex-m7',
'-mfpu=fpv5-d16',
'-mfloat-abi=hard',
'--target=arm-none-eabi',
'-Wall',
'-Wextra']

c_link_args=['-mcpu=cortex-m7',
'-mfpu=fpv5-d16',
'-mfloat-abi=hard',
'--target=arm-none-eabi',
'-T../STM32H723xG_flash.ld',
'-Wl,--gc-sections',
'-Wl,--print-memory-usage']

#app src and inc
src+=['tufo_core/Src/tufo_main.c',
'tufo_core/Src/dds.c',
'tufo_core/Src/lockin.c',
'tufo_core/Src/pid.c',
'tufo_core/Src/freq_sweep.c']

inc=include_directories('tufo_core/Inc',
'interface/Inc',
)

#CMSIS Inc
cmsis_inc=include_directories('CMSIS/Core/Include')


#ST src and inc
st_inc=include_directories('Core/Inc',
'Drivers/STM32H7xx_HAL_Driver/Inc',
'Drivers/CMSIS/Device/ST/STM32H7xx/Include'
)

src+=['Core/Src/main.c',
'Core/Src/gpio.c',
'Core/Src/stm32h7xx_it.c',
'Core/Src/sysmem.c',
'Core/Src/syscalls.c',
'startup_stm32h723xx.s']

src+=['Core/Src/system_stm32h7xx.c',
'Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_dma.c',
'Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_exti.c',
'Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_gpio.c',
'Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_rcc.c',
'Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_utils.c',
'Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usart.c',
'Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_pwr.c']

add_project_arguments('-DUSE_FULL_LL_DRIVER',
'-DHSE_VALUE=25000000',
'-DHSE_STARTUP_TIMEOUT=100',
'-DLSE_STARTUP_TIMEOUT=5000',
'-DLSE_VALUE=32768',
'-DEXTERNAL_CLOCK_VALUE=12288000',
'-DHSI_VALUE=64000000',
'-DLSI_VALUE=32000',
'-DVDD_VALUE=3300',
'-DUSE_PWR_LDO_SUPPLY',
'-DSTM32H723xx',
language: 'c')


#FreeRTOS src and inc
src+=['external/FreeRTOS/tasks.c',
'external/FreeRTOS/queue.c',
'external/FreeRTOS/list.c',
'external/FreeRTOS/timers.c',
'external/FreeRTOS/stream_buffer.c',
'external/FreeRTOS/event_groups.c',
'external/FreeRTOS/portable/GCC/ARM_CM4F/port.c',
'external/FreeRTOS/portable/MemMang/heap_4.c']

freertos_inc=include_directories('external/FreeRTOS/include', 
'external/FreeRTOS/portable/GCC/ARM_CM4F')


#CMSIS_DSP src and inc
src+=['external/cmsis_dsp/Source/BasicMathFunctions/BasicMathFunctions.c',
'external/cmsis_dsp/Source/BayesFunctions/BayesFunctions.c',
'external/cmsis_dsp/Source/CommonTables/CommonTables.c',
'external/cmsis_dsp/Source/ComplexMathFunctions/ComplexMathFunctions.c',
'external/cmsis_dsp/Source/ControllerFunctions/ControllerFunctions.c',
'external/cmsis_dsp/Source/DistanceFunctions/DistanceFunctions.c',
'external/cmsis_dsp/Source/FastMathFunctions/FastMathFunctions.c',
'external/cmsis_dsp/Source/FilteringFunctions/FilteringFunctions.c',
'external/cmsis_dsp/Source/InterpolationFunctions/InterpolationFunctions.c',
'external/cmsis_dsp/Source/MatrixFunctions/MatrixFunctions.c',
'external/cmsis_dsp/Source/QuaternionMathFunctions/QUaternionMathFunctions.c',
'external/cmsis_dsp/Source/StatisticsFunctions/StatisticsFunctions.c',
'external/cmsis_dsp/Source/SupportFunctions/SupportFunctions.c',
'external/cmsis_dsp/Source/SVMFunctions/SVMFunctions.c',
'external/cmsis_dsp/Source/TransformFunctions/TransformFunctions.c',
'external/cmsis_dsp/Source/WindowFunctions/WindowFunctions.c']

dsp_inc=include_directories('external/cmsis_dsp/Include',
'external/cmsis_dsp/PrivateInclude')

#build executable
executable(meson.project_name(),
src,
include_directories: [inc, cmsis_inc, dsp_inc, st_inc, freertos_inc],
name_suffix: 'elf',
c_args: c_args,
link_args: c_link_args
)

elf_file='@BUILD_ROOT@/' + meson.project_name() + '.elf'
pyocd_config = '--config=' + '@SOURCE_ROOT@' + '/pyocd.yaml'
run_target('flash', command: ['pyocd', 'flash', elf_file, pyocd_config])
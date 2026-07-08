all source files and headers in folder tufo_core whould onyl refernceinterface.h
interface.h defines functions that should be implemented as platofrm specific code

allocate double buffers for sine wave(dac output),cosine wave and adc input for tuning fork of size BLOCK_SIZE
main loop waits for command to begin tuning fork oscillations in lock in mode -> fill sine and cos buffer 1 ()-> start timer to clock in adc data and clock out dac data from buffer 1, simultaneously fill sin and cos buffer 2 -> once data finished transfering out, swap buffers and repeat
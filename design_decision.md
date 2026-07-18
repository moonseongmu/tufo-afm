all source files and headers in folder tufo_core whould onyl refernceinterface.h
interface.h defines functions that should be implemented as platofrm specific code
to port to different microcontroller, or different reviison of board, just implement the functions defined in interface.h

```
allocate double buffers for sine wave,cosine wave(dac output) and adc input for tuning fork of size BLOCK_SIZE
main loop waits for command to begin tuning fork oscillations 
if in pll mode 
-> fill sine and cos buffer 1 
-> start timer to clock in adc data and clock out dac data from buffer 1
    ->simultaneously, inphasebuffer = adcbuffer2 x cosbuffer2 and quadraturebuffer =  adcbuffer2 x sinbuffer2 
    ->low pass filter both inphase and quadrature buffers
    ->calculate amplitude and phase
    TODO ->pid loop to find new tuning word 
    ->fill new sin and cos buffer 2 
-> once data finished transfering out, swap buffers and repeat

if frequency sweep mode
-> fill sine and cos buffer 1 
-> start timer to clock in adc data and clock out dac data from buffer 1
    ->simultaneously, inphasebuffer = adcbuffer2 x cosbuffer2 and quadraturebuffer =  adcbuffer2 x sinbuffer2 
    ->low pass filter both inphase and quadrature buffers
    ->calculate amplitude and phase
    ->check if amplitude stable
        -> if yes, update new tuning word according to frequency step 
    ->fill new sin and cos buffer 2 
-> once data finished transfering out, swap buffers and repeat
```
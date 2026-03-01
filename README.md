First attempt at using CUDA and cuFFT to process ambient electric fields.
The program reads raw voltages from the air and runs a Fast Fourier Transform to separate them into individual frequencies.
By measuring the amplitude of each frequency, I built a filter that locks onto a specific Hz and magnitude to trigger a full-duplex command back to an ESP32 to light an LED.
Lacking specialized radio hardware, I used a bare jumper wire as the antenna and my own body as a capacitive 'satellite dish' to funnel the room's 50Hz AC power grid hum.

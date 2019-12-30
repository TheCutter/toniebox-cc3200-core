#include "driverlib/i2s.h"
#include "inc/hw_mcasp.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "i2s.h"

#define UL_BASE I2S_BASE //0x4401C000
#define UL_DATALINE I2S_DATA_LINE_0 // TODO!
#define UL_DATALINE_SHIFTED ((UL_DATALINE-1) << 2) //TODO!

void i2s_begin() { // Enable TX only, for compatibility
    I2SConfigSetExpClk(I2S_BASE, 512000, 16*16000*2, I2S_SLOT_SIZE_16|I2S_PORT_CPU);
    I2SSerializerConfig(UL_BASE, UL_DATALINE, I2S_SER_MODE_TX, I2S_INACT_LOW_LEVEL);

    if( HWREG(UL_BASE + MCASP_O_ACLKXCTL) & 0x20) { // FSYNC and Bit clock are output only in master mode
        HWREG(UL_BASE + MCASP_O_PDIR) |= 0x14000000; // Set FSYNC anc BitClk as output
    }
    i2s_rxtx_begin(false, true);
}

bool i2s_rxtx_begin(bool enableRx, bool enableTx) {// Allow TX and/or RX, returns false on OOM error
    if (enableRx)  {
        I2SGBLEnable(UL_BASE, MCASP_GBL_RHCLK); // Remove Rx HCLK reset
        I2SGBLEnable(UL_BASE, MCASP_GBL_RCLK); // Remove Rx XCLK reset
        I2SGBLEnable(UL_BASE, MCASP_GBL_RSER); // Enable Rx SERDES(s)
        I2SGBLEnable(UL_BASE, MCASP_GBL_RSM); // Enable Rx state machine
        I2SGBLEnable(UL_BASE, MCASP_GBL_RFSYNC); // Enable FSync generator
    }
    
    I2SGBLEnable(UL_BASE, MCASP_GBL_XHCLK); // Remove Tx HCLK reset
    I2SGBLEnable(UL_BASE, MCASP_GBL_XCLK); // Remove Tx XCLK reset
    if (enableTx) {
        I2SGBLEnable(UL_BASE, MCASP_GBL_XSER); // Enable Tx SERDES(s)
        I2SGBLEnable(UL_BASE, MCASP_GBL_XSM); // Enable Tx state machine
    }

    I2SGBLEnable(UL_BASE, MCASP_GBL_XFSYNC); // Enable FSync generator
}

void i2s_end() {
   I2SDisable(UL_BASE);
}

void i2s_set_rate(uint32_t rate);//Sample Rate in Hz (ex 44100, 48000)
void i2s_set_dividers(uint8_t div1, uint8_t div2);//Direct control over output rate
float i2s_get_real_rate();//The actual Sample Rate on output

void _i2s_write_sample_raw(uint32_t sample) {
    HWREG(UL_BASE + MCASP_O_TXBUF0 + UL_DATALINE_SHIFTED) = sample;
}
bool i2s_write_sample(uint32_t sample) {//32bit sample with channels being upper and lower 16 bits (blocking when DMA is full)
    while(i2s_is_full()) {}

    _i2s_write_sample_raw(sample);
    return true;
}

bool i2s_write_sample_nb(uint32_t sample) {//same as above but does not block when DMA is full and returns false instead
    if (i2s_is_full())
        return false;

    _i2s_write_sample_raw(sample);
    return true;
}

bool i2s_write_lr(int16_t left, int16_t right) { //combines both channels and calls i2s_write_sample with the result
    int sample = right & 0xFFFF;
    sample = sample << 16;
    sample |= left & 0xFFFF;
    return i2s_write_sample(sample);
}

bool i2s_read_sample(int16_t *left, int16_t *right, bool blocking) { // RX data returned in both 16-bit outputs.
    if (blocking) {
        while (i2s_rx_is_empty()) { }
    } else {
        if (i2s_rx_is_empty())
            return false;
    }
    uint32_t *sample;
    *sample = HWREG(UL_BASE + MCASP_O_RXBUF0 + UL_DATALINE_SHIFTED);
    if (left) {
        *left  = *sample & 0xffff;
    }
    if (right) {
        *right = *sample >> 16;
    }
}

bool i2s_is_full() { //returns true if DMA is full and can not take more bytes (overflow)
    return !(HWREG(UL_BASE + MCASP_O_TXSTAT) & MCASP_TXSTAT_XDATA);
}

bool i2s_is_empty() {//returns true if DMA is empty (underflow)
    return !i2s_is_full(); //TODO
}

bool i2s_rx_is_full() { 
    return !i2s_rx_is_empty(); //TODO
}

bool i2s_rx_is_empty() {
    return !(HWREG(UL_BASE + MCASP_O_RXSTAT) & MCASP_RXSTAT_RDATA);
}

uint16_t i2s_available() {// returns the number of samples than can be written before blocking
    return HWREG(UL_BASE + MCASP_0_WFIFOSTS); //TODO returns number of 32-bit words in transmit FIFO
}

uint16_t i2s_rx_available() {// returns the number of samples than can be read before blocking
    return HWREG(UL_BASE + MCASP_0_RFIFOSTS); //TODO returns number of 32-bit words in the receive FIFO
}

void i2s_set_callback(void (*callback) (void));
void i2s_rx_set_callback(void (*callback) (void));

// writes a buffer of frames into the DMA memory, returns the amount of frames written
// A frame is just a int16_t for mono, for stereo a frame is two int16_t, one for each channel.
uint16_t i2s_write_buffer_mono(int16_t *frames, uint16_t frame_count);
uint16_t i2s_write_buffer_mono_nb(int16_t *frames, uint16_t frame_count);
uint16_t i2s_write_buffer(int16_t *frames, uint16_t frame_count);
uint16_t i2s_write_buffer_nb(int16_t *frames, uint16_t frame_count); 
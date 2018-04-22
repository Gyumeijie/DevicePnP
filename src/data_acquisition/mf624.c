#include <stdio.h>
#include "mf624.h"

static mf624_state_t mf624_state;

void DIO_write(mf624_state_t* mfst, int16_t val)
{
    mf624_write16(val, MFST2REG(mfst, 2, DOUT_reg));
}

uint16_t DIO_read(mf624_state_t* mfst) 
{ 
    return mf624_read16(MFST2REG(mfst, 2, DIN_reg)) & 0xFF; 
}

void DAC_enable(mf624_state_t* mfst)
{
    // set DACEN and LDAC bits in GPIO register influences all DACs
    mf624_write32((mf624_read32(MFST2REG(mfst, 0, GPIOC_reg))
        | GPIOC_DACEN_mask)   // enable output
        & (~GPIOC_LDAC_mask), // enable conversion
        MFST2REG(mfst, 0, GPIOC_reg));
}

int DAC_write(mf624_state_t* mfst, dac_channel_t channel, int val)
{
    if (channel > sizeof(dac_channel2reg)/sizeof(*dac_channel2reg))
        return -1;

    mf624_write16(val, MFST2REG(mfst, 2, dac_channel2reg[channel]));

    return 0;
}

int ADC_enable(mf624_state_t* mfst, adc_channel_t channel)
{
    mfst->ADC_enabled = 0;

    if (channel > sizeof(adc_channel2reg)/sizeof(*adc_channel2reg))
        return -1;

    mfst->ADC_enabled = (1 << channel);
    mfst->ADC_enabled &= 0xFF;
    mf624_write16(mfst->ADC_enabled, MFST2REG(mfst, 2, ADCTRL_reg));

    return 0;
}

/* This function blocks until conversion is finished */
double ADC_read(mf624_state_t* mfst, adc_channel_t channel)
{
    // activate trigger to start conversion
    mf624_read16(MFST2REG(mfst, 2, ADSTART_reg));

    // check if conversion has finished
    volatile int i;
    while((mf624_read32(MFST2REG(mfst, 0, GPIOC_reg)) & GPIOC_EOLC_mask)) {
        for (i = 0; i < 1000; i++);  // small wait
    }

    ADC_enable(mfst, channel);
    int result = mf624_read16(MFST2REG(mfst, 2, ADDATA0_reg));

    return 10.0 * ((int16_t) (result << 2)) / (double) 0x8000;
}

int mmap_regions(mf624_state_t* mfst)
{
    (&mfst->bar0)->addr = 0x80004000;
    (&mfst->bar2)->addr = 0x80004020;
    (&mfst->bar4)->addr = 0x800040a0;
}

void mf624_init(void)
{
    mmap_regions(&mf624_state);
}


mf624_state_t* get_mf624_state(void)
{
    return &mf624_state;
}


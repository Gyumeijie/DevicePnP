/*
 * Application using MF624 UIO driver
 *
 * Copyright (C) 2011 Rostislav Lisovy <lisovy@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef MF624_H
#define MF624_H

#include <stdint.h> // for uint**_t 

#define BUFF_SMALL      	32
#define BUFF_MID        	256
#define min(a, b)       	((a) > (b) ? (b) : (a))

/* Hardware specific */

// BAR0 
#define GPIOC_reg		0x54

// BAR2
#define ADCTRL_reg		0x00
#define ADDATA0_reg		0x00
#define ADDATA1_reg		0x02
#define ADDATA2_reg		0x04
#define ADDATA3_reg		0x06
#define ADDATA4_reg		0x08
#define ADDATA5_reg		0x0a
#define ADDATA6_reg		0x0c
#define ADDATA7_reg		0x0e
#define ADSTART_reg		0x20

#define DOUT_reg        	0x10
#define DIN_reg 	       	0x10
#define DA0_reg			0x20
#define DA1_reg			0x22
#define DA2_reg			0x24
#define DA3_reg			0x26
#define DA4_reg			0x28
#define DA5_reg			0x2A
#define DA6_reg			0x2C
#define DA7_reg			0x2E

#define GPIOC_DACEN_mask	(1 << 26)
#define GPIOC_LDAC_mask		(1 << 23)
#define GPIOC_EOLC_mask		(1 << 17)


typedef enum {DA0, DA1, DA2, DA3, DA4, DA5, DA6, DA7} dac_channel_t;
typedef enum {AD0, AD1, AD2, AD3, AD4, AD5, AD6, AD7} adc_channel_t;

static uint32_t dac_channel2reg[] = {
	[DA0] = DA0_reg,
	[DA1] = DA1_reg,
	[DA2] = DA2_reg,
	[DA3] = DA3_reg,
	[DA4] = DA4_reg,
	[DA5] = DA5_reg,
	[DA6] = DA6_reg,
	[DA7] = DA7_reg,
};

static uint32_t adc_channel2reg[] = {
	[AD0] = ADDATA0_reg,
	[AD1] = ADDATA1_reg,
	[AD2] = ADDATA2_reg,
	[AD3] = ADDATA3_reg,
	[AD4] = ADDATA4_reg,
	[AD5] = ADDATA5_reg,
	[AD6] = ADDATA6_reg,
	[AD7] = ADDATA7_reg,
};

typedef struct bar_mapping_t {
	uintptr_t addr;
} bar_mapping_t;


typedef struct mf624_state_t {
	bar_mapping_t bar0;
	bar_mapping_t bar2;
	bar_mapping_t bar4;
	int status;
	int ADC_enabled; // specify which ADC is to be enabled
} mf624_state_t;

#define MFST2REG(mfst, bar_num, reg_offs) \
	((void *)(mfst->bar##bar_num.addr + (reg_offs)))


static inline int16_t mf624_read16(void *ptr)
{
    return *(volatile uint16_t*)ptr;
}

static inline int32_t mf624_read32(void *ptr)
{
    return *(volatile uint32_t*) ptr;
}

static inline void mf624_write16(uint16_t val, void *ptr)
{
    *(volatile uint16_t*) ptr = val;
}

static inline void mf624_write32(uint32_t val, void *ptr)
{
    *(volatile uint32_t*) ptr = val;
}


void DIO_write(mf624_state_t* mfst, int16_t val);

uint16_t DIO_read(mf624_state_t* mfst);

void DAC_enable(mf624_state_t* mfst);

int ADC_enable(mf624_state_t* mfst, adc_channel_t channel);

int DAC_write(mf624_state_t* mfst, dac_channel_t channel, int val);

// this function blocks until conversion is finished 
double ADC_read(mf624_state_t* mfst, adc_channel_t channel);

int mmap_regions(mf624_state_t* mfst);

void mf624_init(void);

mf624_state_t *get_mf624_state(void);

#endif

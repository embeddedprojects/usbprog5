/*
 * modified AVR1612 appnote for PDI programming
 * modifications by hunz@mailbox.org
 * see license conditions for original appnote below
 * modified parts may be redistributed under the
 * same conditions as the original code from Atmel
 */

/**
 * \file
 *
 * \brief Low level PDI driver
 *
 * Copyright (C) 2009 Atmel Corporation. All rights reserved.
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 * Atmel AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
#ifndef MEGA_PDI_H_INCLUDED
#define MEGA_PDI_H_INCLUDED

#include <usart.h>
#include <status_codes.h>

#include "config.h"

#define PDI_BAUD_RATE 1000000UL               //!< PDI Baud rate.

/**
 * \brief Initial the PDI port.
 */
#define pdi_pin_init() do {                               \
				PDI_DDR |= (1 << PDI_DATA_PIN);							\
				PDI_PORT &= ~(1 << PDI_DATA_PIN);						\
				PDI_DDR |= (1 << PDI_RESET_PIN);							\
				PDI_PORT |= (1 << PDI_RESET_PIN);						\
} while (0)

/**
 * \brief Set the PDI DATA tx pin low.
 */
#define pdi_data_tx_low() do {            \
		PDI_PORT &= ~(1 << PDI_DATA_PIN);		\
} while (0)

/**
 * \brief Set the PDI DATA tx pin high.
 */
#define pdi_data_tx_high() do {        \
		PDI_PORT |= (1 << PDI_DATA_PIN);	\
} while (0)

/**
 * \brief Set the PDI DATA tx as input.
 */
#define pdi_data_tx_input() do {    \
		PDI_PORT = (1 << PDI_DATA_PIN); \
		PDI_DDR &= ~(1 << PDI_DATA_PIN); \
} while (0)

/**
 * \brief Set the PDI RESET pin low.
 */
#define pdi_reset_low() do {            \
				PDI_PORT &= ~(1 << PDI_RESET_PIN); \
} while (0)

/**
 * \brief Set the PDI RESET pin high.
 */
#define pdi_reset_high() do {         \
				PDI_PORT |= (1 << PDI_RESET_PIN); \
} while (0)

/**
  * \brief Configure USART for PDI application.
  *
  *  The USRT must be configured the following way:
  *  - Double speed
  *  - data change on falling TX
  *  - Character size is 8 bits
  *  - Even parity
  *  - Two stop bits
  *  For more information, please refer to "Program and Debug Interface" section of
  *  XMEGA A MANUAL
  */
static inline void pdi_configure(void)
{
	/* Sample data falling clock edge, 8 bit data, even
	 * parity and 2 stop bits */
	usart_format_set(USART_CHSIZE_8BIT_gc, USART_PMODE_EVEN_gc, true);
	usart_set_polarity_bit(true);
}


/**
 * \brief USART baud rate set.
 *
 * This function is used to set the PDI baud rate on synchronous mode.
 *
 *  \param  baud_rate the PDI baud rate.
 */
static inline void pdi_set_baud_rate(uint32_t baud_rate)
{
	usart_synchronous_set_baudrate(baud_rate, F_CPU);
}

/**
 * \brief Enable PDI RX.
 */
static inline void pdi_enable_rx(void)
{
	usart_rx_enable();
}

/**
 * \brief Enable PDI TX.
 *
 *  This function is used to enable PDI TX.
 */
static inline void pdi_enable_tx(void)
{
	usart_tx_enable();
}

/**
 * \brief Set mode to be synchronuous.
 */
static inline void pdi_enable_clk( void )
{
	usart_set_mode(USART_CMODE_SYNCHRONOUS_gc);
}

/**
 * \brief The clock is disabled by entering MSPI mode.
 */
static inline void pdi_disable_clk( void )
{
	usart_set_mode(USART_CMODE_ASYNCHRONOUS_gc);
}

/**
 * \brief Disable the USRT transmitter.
 */
static inline void pdi_disable_tx( void )
{
	usart_tx_disable();
}

/**
 * \brief Disable the USRT receiver.
 */
static inline void pdi_disable_rx( void )
{
	usart_rx_disable();
}

void pdi_init(uint8_t div);
void pdi_deinit(void);
enum status_code pdi_write(const volatile uint8_t *data, uint16_t length);
uint16_t pdi_read(uint8_t *data, uint16_t length, uint32_t retries);
enum status_code pdi_get_byte(uint8_t *ret, uint32_t retries);

#endif

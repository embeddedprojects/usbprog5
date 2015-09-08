/**
 * \file uart
 *
 * \brief AT90USB1287 UART driver
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

#ifndef UART_H_
#define UART_H_

#include "config.h"

#define USART_CMODE_gm 0xC0

typedef enum USART_CHSIZE_enum
{
    USART_CHSIZE_5BIT_gc = (0x00<<1),  /* Character size: 5 bit */
    USART_CHSIZE_6BIT_gc = (0x01<<1),  /* Character size: 6 bit */
    USART_CHSIZE_7BIT_gc = (0x02<<1),  /* Character size: 7 bit */
    USART_CHSIZE_8BIT_gc = (0x03<<1),  /* Character size: 8 bit */
} USART_CHSIZE_t;

/* Parity Mode */
typedef enum USART_PMODE_enum
{
    USART_PMODE_DISABLED_gc = (0x00<<4),  /* No Parity */
    USART_PMODE_EVEN_gc 	= (0x02<<4),  /* Even Parity */
    USART_PMODE_ODD_gc 		= (0x03<<4),  /* Odd Parity */
} USART_PMODE_t;

/* Communication Mode */
typedef enum USART_CMODE_enum
{
    USART_CMODE_ASYNCHRONOUS_gc = (0x00<<6),  /* Asynchronous Mode */
    USART_CMODE_SYNCHRONOUS_gc = (0x01<<6),  /* Synchronous Mode */
    USART_CMODE_MSPI_gc = (0x03<<6),  /* Master SPI Mode */
} USART_CMODE_t;

/**
 *  \brief Enable USART transmitter.
 *
 *  \param _usart Pointer to the USART module.
 */
static inline void usart_tx_enable(void)
{
	UCSR0B |= (1 << TXEN0);
}

/** \brief Disable USART transmitter.
 *
 *  \param _usart Pointer to the USART module.
 */
static inline void usart_tx_disable(void)
{
	UCSR0B &= ~(1 << TXEN0);
}

/**
 *  \brief Enable USART receiver.
 *
 *  \param _usart    Pointer to the USART module
 */
static inline void usart_rx_enable(void)
{
	UCSR0B |= (1 << RXEN0);
}


/**
 *  \brief Disable USART receiver.
 *
 *  \param _usart Pointer to the USART module.
 */
static inline void usart_rx_disable(void)
{
	UCSR0B &= ~(1 << RXEN0);
}

/**
 *  \brief Checks if the RX complete interrupt flag is set.
 *
 *   Checks if the RX complete interrupt flag is set.
 *
 *  \param _usart     The USART module.
 */
static inline bool usart_rx_is_complete(void)
{
	return UCSR0A & (1 << RXC0);
}

/**
 *  \brief Check if data register empty flag is set.
 *
 *  \param _usart      The USART module.
 */
static inline bool usart_data_register_is_empty(void)
{
	return UCSR0A & (1 << UDRE0);
}

/**
 *  \brief  Configure the USART frame format.
 *
 *  Sets the frame format, Frame Size, parity mode and number of stop bits.
 *
 *  \param _usart        Pointer to the USART module
 *  \param _charSize     The character size. Use USART_CHSIZE_t type.
 *  \param _parityMode   The parity Mode. Use USART_PMODE_t type.
 *  \param _twoStopBits  Enable two stop bit mode. Use bool type.
 */
static inline void usart_format_set(USART_CHSIZE_t _charSize, USART_PMODE_t _parityMode, bool _twoStopBits)
{
	UCSR0C = (uint8_t) _charSize | _parityMode |                      \
			(_twoStopBits ? (1 << USBS0) : 0);
}

/**
 *  \brief Set the mode the USART run in.
 *
 * Set the mode the USART run in. The default mode is asynchronous mode.
 *
 *  \param  _usart       Pointer to the USART module register section.
 *  \param  _usartmode   Selects the USART mode. Use  USART_CMODE_t type.
 *
 *  USART modes:
 *  - 0x0        : Asynchronous mode.
 *  - 0x1        : Synchronous mode.
 *  - 0x3        : Master SPI mode.
 */
static inline void usart_set_mode(USART_CMODE_t _usartmode)
{
	UCSR0C = (UCSR0C & (~USART_CMODE_gm)) | _usartmode;
}

/**
 * \brief Set the baud rate when using synchronous mode
 *
 * \retval true always assume that it went ok
 */
static inline bool usart_synchronous_set_baudrate(uint32_t baud, uint32_t cpu_hz)
{
	uint16_t brreg = (cpu_hz / baud / 2) - 1;
	UBRR0H = (brreg >> 8) & 0xFF;
	UBRR0L = brreg & 0xFF;
	return true;
}

/**
 * \brief Function for setting the polarity of the clock signal
 *
 * This function is missing in the ASF 2.0 driver.
 */
static inline void usart_set_polarity_bit(bool set)
{
	if(set)
	{
		UCSR0C |= (1 << UCPOL0);
	}else{
		UCSR0C &= ~(1 << UCPOL0);
	}
}

/**
 *  \brief  Read a data to the USART data register.
 *
 *  \param usart     The USART module.
 *
 *  \return The received data
 */
static inline uint8_t usart_get(void)
{
	return UDR0;
}

/**
 *  \brief Write a data to the USART data register.
 *
 *  \param usart     The USART module.
 *  \param txdata    The data to be transmited.
 */
static inline void usart_put(uint8_t txdata)
{
	UDR0 = txdata;
}
#endif /* UART_H_ */

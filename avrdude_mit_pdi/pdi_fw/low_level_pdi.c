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
#include <low_level_pdi.h>

#include <util/delay.h>

/**
 * \brief Initialize PDI.
 *
 * Initialize the peripeherals necessary to communicate with the ATxmega
 *  PDI.
 */
void pdi_init( uint8_t div )
{
	div = (div <= 4) ? div : 4;
	/* Enable USRT. */
	pdi_set_baud_rate(PDI_BAUD_RATE>>div);
	pdi_configure();

	/* Enter PDI mode. */
	pdi_pin_init();
	_delay_us(100);

	pdi_data_tx_high();
	_delay_us(1);

	/* Enable the PDI_CLK and let it run for at leat 16 cycles. */
	pdi_enable_rx();
	pdi_enable_clk();
	div = (1<<div)+1;
	for(;div;div--)
		_delay_us(16);
}

/**
 * \brief Write bulk bytes with PDI.
 *
 *  Send bytes over the PDI channel.
 *
 * \param data Pointer to memory where data to be sent is stored.
 * \param length Number of bytes to be sent.
 *
 * \retval STATUS_OK The transmission was successful.
 * \retval ERR_BAD_DATA One of the bytes sent was corrupted during transmission.
 */
enum status_code pdi_write( const volatile uint8_t *data, uint16_t length )
{
	uint16_t i;
	uint8_t dummy_read = 0;

	/* Empty any old data in the RX register. */
	while (usart_rx_is_complete()) {
		dummy_read = usart_get();
	}

	pdi_enable_tx();

	for (i = 0; i < length; i++) {
		while (!usart_data_register_is_empty());
		usart_put(data[i]);

		while (!usart_rx_is_complete());
		dummy_read = usart_get();

		/* Check that the transmission was successful. */
		if (dummy_read != data[i]) {
			// Set TX to tri-state
			pdi_disable_tx();
			pdi_data_tx_input();
			pdi_data_tx_low();

			return ERR_IO_ERROR;
		}
	}

	/* Set TX to tri-state */
	pdi_disable_tx();
	pdi_data_tx_input();
	pdi_data_tx_low();

	return STATUS_OK;
}

/**
 * \brief Read bulk bytes from PDI.
 *
 * \param data Pointer to memory where data to be stored.
 * \param length Number of bytes to be read.
 * \param retries the retry count.
 *
 * \retval non-zero the length of data.
 * \retval zero read fail.
 */
uint16_t pdi_read( uint8_t *data, uint16_t length, uint32_t retries )
{
	uint32_t count;
	uint16_t bytes_read = 0;
	uint16_t i;

	for (i = 0; i < length; i++) {
		count = retries;
		while (count != 0) {
			if (usart_rx_is_complete()) {
				*(data + i) = usart_get();
				bytes_read++;
				break;
			}
			--count;
		}
		/* Read fail error */
		if (count == 0) {
			return 0;
		}
	}

	return bytes_read;
}

/**
 * \brief Read a byte from PDI.
 *
 * \param ret Pointer to buffer memory where data to be stored.
 * \param retries the retry count.
 *
 * \retval STATUS_OK read successfully.
 * \retval ERR_TIMEOUT read fail.
 */
enum status_code pdi_get_byte( uint8_t *ret, uint32_t retries )
{
	while (retries != 0) {
		if (usart_rx_is_complete()) {
			*ret = usart_get();
			return STATUS_OK;
		}
		--retries;
	}

	return ERR_IO_ERROR;
}

/**
 * \brief This function disables the PDI port.
 */
void pdi_deinit( void )
{
	pdi_disable_clk();
	pdi_disable_rx();
	pdi_disable_tx();
	pdi_data_tx_input();
	pdi_data_tx_low();
	_delay_us(300);
	pdi_reset_high();
}

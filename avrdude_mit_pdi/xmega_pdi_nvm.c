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
 * \brief XMEGA PDI NVM command driver
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
#include <xmega_pdi_nvm.h>

uint8_t cmd_buffer[20];
enum status_code retval;
uint8_t initialized = 0;

/* Private prototypes */
static enum status_code xnvm_read_pdi_status(uint8_t *status);
static enum status_code xnvm_wait_for_nvmen(uint32_t retries);
static enum status_code xnvm_ctrl_read_reg(uint16_t reg, uint8_t *value);
static enum status_code xnvm_ctrl_write_reg(uint16_t reg, uint8_t value);
enum status_code xnvm_st_ptr(uint32_t address);
enum status_code xnvm_ctrl_cmd_write(uint8_t cmd_id);
static enum status_code xnvm_ctrl_read_status(uint8_t *value);
enum status_code xnvm_st_ptr(uint32_t address);
enum status_code xnvm_st_star_ptr_postinc(uint8_t value);
static enum status_code xnvm_write_repeat(uint32_t count);
enum status_code xnvm_ctrl_wait_nvmbusy(uint32_t retries);
static enum status_code xnvm_ctrl_cmdex_write(void);
/*********************/

/**
 * \brief Initiliazation function for the PDI interface
 *
 * This function initializes the PDI interface agains
 * the connected target device.
 *
 * \retval STATUS_OK init ok
 * \retval ERR_TIMEOUT the init timed out
 */
enum status_code xnvm_init (uint8_t div)
{
	if(initialized == 0){

		pdi_init(div);

		/* Put the device in reset mode */
		xnvm_put_dev_in_reset();

		/* Create the key command */
		cmd_buffer[0] = XNVM_PDI_KEY_INSTR;
		cmd_buffer[1] = NVM_KEY_BYTE0;
		cmd_buffer[2] = NVM_KEY_BYTE1;
		cmd_buffer[3] = NVM_KEY_BYTE2;
		cmd_buffer[4] = NVM_KEY_BYTE3;
		cmd_buffer[5] = NVM_KEY_BYTE4;
		cmd_buffer[6] = NVM_KEY_BYTE5;
		cmd_buffer[7] = NVM_KEY_BYTE6;
		cmd_buffer[8] = NVM_KEY_BYTE7;

		pdi_write(cmd_buffer, 9);

		retval = xnvm_ctrl_wait_nvmbusy(WAIT_RETRIES_NUM);

		initialized = 1;
	}

	return retval;
}

/**
 * \brief Function for putting the device into reset
 *
 * \retval STATUS_OK if all went well
 * \retval ERR_IO_ERROR if the pdi write failed
 */
enum status_code xnvm_put_dev_in_reset (void)
{
	/* Reset the device */
	cmd_buffer[0] = XNVM_PDI_STCS_INSTR | XOCD_RESET_REGISTER_ADDRESS;
	cmd_buffer[1] = XOCD_RESET_SIGNATURE;
	if(pdi_write(cmd_buffer, 2)){
		return ERR_IO_ERROR;
	}
	return STATUS_OK;
}

/**
 *  \internal
 *  \brief Wait until the NVM module has completed initialization
 *
 *  \param  retries the retry count.
 *  \retval STATUS_OK the NVMEN was set successfully.
 *  \retval ERR_BAD_DATA One of the bytes sent was corrupted during transmission.
 *  \retval ERR_TIMEOUT Time out.
 */
static enum status_code xnvm_wait_for_nvmen(uint32_t retries)
{
	uint8_t pdi_status;

	while (retries != 0) {
		if (xnvm_read_pdi_status(&pdi_status) != STATUS_OK) {
				return ERR_BAD_DATA;
		}
		if ((pdi_status & XNVM_NVMEN) != 0) {
				return STATUS_OK;
		}
		--retries;
	}
	return ERR_TIMEOUT;

}

/**
 *  \internal
 *  \brief Read the PDI Controller's STATUS register
 *
 *  \param  status the status buffer pointer.
 *  \retval STATUS_OK read successfully.
 *  \retval ERR_BAD_DATA One of the bytes sent was corrupted during transmission.
 *  \retval ERR_TIMEOUT Time out.
 */
static enum status_code xnvm_read_pdi_status(uint8_t *status)
{
	enum status_code ret = STATUS_OK;

	cmd_buffer[0] = XNVM_PDI_LDCS_INSTR;
	cmd_buffer[1] = 0x00;
	if (STATUS_OK != pdi_write(cmd_buffer, 2)) {
			ret = ERR_BAD_DATA;
	}
	if (pdi_get_byte(status, WAIT_RETRIES_NUM) != STATUS_OK) {
			ret = ERR_TIMEOUT;
	}

	return ret;
}

/**
 *  \brief Read the IO space register with NVM controller
 *
 *  \param  address the register address in the IO space.
 *  \param  value the value buffer pointer.
 *  \retval STATUS_OK read successfully.
 *  \retval ERR_BAD_DATA One of the bytes sent was corrupted during transmission.
 *  \retval ERR_TIMEOUT Time out.
 */
enum status_code xnvm_ioread_byte(uint16_t address, uint8_t *value)
{
	enum status_code ret = STATUS_OK;
	uint32_t register_address;

	cmd_buffer[0] = XNVM_PDI_LDS_INSTR | XNVM_PDI_LONG_ADDRESS_MASK |
			XNVM_PDI_BYTE_DATA_MASK;

	register_address = XNVM_DATA_BASE + address;

	mem_move((uint8_t*)&register_address, (cmd_buffer + 1), 4);

	ret = pdi_write(cmd_buffer, 5);
	ret = pdi_get_byte(value, WAIT_RETRIES_NUM);

	return ret;
}

/**
 *  \brief Write the IO space register with NVM controller
 *
 *  \param  address the register address in the IO space.
 *  \param  value the value which should be write into the address.
 *  \retval STATUS_OK write successfully.
 *  \retval ERR_BAD_DATA One of the bytes sent was corrupted during transmission.
 *  \retval ERR_TIMEOUT Time out.
 */
enum status_code xnvm_iowrite_byte(uint16_t address, uint8_t value)
{

	uint32_t register_address = XNVM_DATA_BASE + address;

	cmd_buffer[0] = XNVM_PDI_STS_INSTR | XNVM_PDI_LONG_ADDRESS_MASK |
			XNVM_PDI_BYTE_DATA_MASK;

	mem_move((uint8_t*)&register_address, (cmd_buffer + 1), 4);
	cmd_buffer[5] = value;

	return (pdi_write(cmd_buffer, 6));
}

/**
 *  \internal
 *  \brief Read the NVM Controller's status register
 *
 *  \param  value the NVM Controller's status buffer pointer.
 *  \retval STATUS_OK read successfully.
 *  \retval ERR_TIMEOUT Time out.
 */
static enum status_code xnvm_ctrl_read_status(uint8_t *value)
{
	return xnvm_ctrl_read_reg(XNVM_CONTROLLER_STATUS_REG_OFFSET, value);
}

/**
 *  \internal
 *  \brief Read the NVM Controller's register
 *
 *  \param  reg the offset of the NVM Controller register.
 *  \param  value the pointer of the value buffer.
 *  \retval STATUS_OK read succussfully.
 *  \retval ERR_TIMEOUT Time out.
 */
static enum status_code xnvm_ctrl_read_reg(uint16_t reg, uint8_t *value)
{
	uint16_t address;

	address = XNVM_CONTROLLER_BASE + reg;
	return xnvm_ioread_byte(address, value);
}

/**
 *  \internal
 *  \brief Write the NVM Controller's register
 *
 *  \param  reg the offset of the NVM Controller register.
 *  \param  value the value which should be write into the register.
 *  \retval STATUS_OK write succussfully.
 *  \retval ERR_BAD_DATA One of the bytes sent was corrupted during transmission.
 *  \retval ERR_TIMEOUT Time out.
 */
static enum status_code xnvm_ctrl_write_reg(uint16_t reg, uint8_t value)
{
	uint16_t address;

	address = XNVM_CONTROLLER_BASE + reg;
	return xnvm_iowrite_byte(address, value);
}

/**
 * \internal
 * \brief Write the NVM CTRLA register CMDEX
 *
 * \retval STATUS_OK write successful.
 * \retval STATUS_OK write successfully.
 * \retval ERR_BAD_DATA One of the bytes sent was corrupted during transmission.
 * \retval ERR_TIMEOUT Time out.
 */
static enum status_code xnvm_ctrl_cmdex_write(void)
{
	return xnvm_ctrl_write_reg(XNVM_CONTROLLER_CTRLA_REG_OFFSET, XNVM_CTRLA_CMDEX);
}

/**
 *  \internal
 *  \brief Write NVM command register
 *
 *  \param  cmd_id the command code which should be write into the NVM command register.
 *  \retval STATUS_OK write successfully.
 *  \retval ERR_BAD_DATA One of the bytes sent was corrupted during transmission.
 *  \retval ERR_TIMEOUT Time out.
 */
enum status_code xnvm_ctrl_cmd_write(uint8_t cmd_id)
{
	return xnvm_ctrl_write_reg(XNVM_CONTROLLER_CMD_REG_OFFSET, cmd_id);
}

/**
 *  \brief Erase the chip
 *
 *  \retval STATUS_OK erase chip succussfully.
 *  \retval ERR_TIMEOUT Time out.
 */
enum status_code xnvm_chip_erase(void)
{
	/* Write the chip erase command to the NVM command reg */
	xnvm_ctrl_cmd_write(XNVM_CMD_CHIP_ERASE);
	/* Write the CMDEX to execute command */
	xnvm_ctrl_cmdex_write();
	return xnvm_wait_for_nvmen(WAIT_RETRIES_NUM);
}

enum status_code xnvm_load_buffer(volatile uint8_t *buf, uint16_t len)
{
	if (len > 1) {
			xnvm_write_repeat(len);
	} else {
			return xnvm_st_star_ptr_postinc(*buf);
	}

	cmd_buffer[0] = XNVM_PDI_ST_INSTR | XNVM_PDI_LD_PTR_STAR_INC_MASK |
			XNVM_PDI_BYTE_DATA_MASK;
	pdi_write(cmd_buffer, 1);

	return pdi_write(buf, len);
}

enum status_code xnvm_erase_buffer(int eeprom, uint32_t retries)
{
	enum status_code ret = xnvm_st_ptr(0);
	if(ret != STATUS_OK)
		return ret;
	ret = xnvm_ctrl_cmd_write(eeprom ? XNVM_CMD_ERASE_EEPROM_PAGE_BUFFER : XNVM_CMD_ERASE_FLASH_PAGE_BUFFER);
	if(ret != STATUS_OK)
		return ret;
	ret = xnvm_ctrl_cmdex_write();
	if(ret != STATUS_OK)
		return ret;

	return xnvm_ctrl_wait_nvmbusy(retries);
}

/**
 *  \internal
 *  \brief Write the repeating number with PDI port
 *
 *  \param  count the repeating number.
 *  \retval STATUS_OK write succussfully.
 *  \retval ERR_BAD_DATA One of the bytes sent was corrupted during transmission.
 */
static enum status_code xnvm_write_repeat(uint32_t count)
{
	uint8_t cmd_len;

	--count;

	if (count < (1 << 8)) {
		cmd_buffer[0] = XNVM_PDI_REPEAT_INSTR | XNVM_PDI_BYTE_DATA_MASK;
		cmd_buffer[1] = count;
		cmd_len = 2;
	} else if (count < ((uint32_t)(1) << 16)) {
		cmd_buffer[0] = XNVM_PDI_REPEAT_INSTR | XNVM_PDI_WORD_DATA_MASK;
		mem_move((uint8_t*)&count, (cmd_buffer + 1), 2);
		cmd_len = 3;
	} else if (count < ((uint32_t)(1) << 24)) {
		cmd_buffer[0] = XNVM_PDI_REPEAT_INSTR | XNVM_PDI_3BYTES_DATA_MASK;
		mem_move((uint8_t*)&count, (cmd_buffer + 1), 3);
		cmd_len = 4;
	} else {
		cmd_buffer[0] = XNVM_PDI_REPEAT_INSTR | XNVM_PDI_LONG_DATA_MASK;
		mem_move((uint8_t*)&count, (cmd_buffer + 1), 4);
		cmd_len = 5;
	}

	return pdi_write(cmd_buffer, cmd_len);
}

/**
 *  \internal
 *  \brief Write a value to a address with *(ptr++) instruction through the PDI Controller.
 *
 *  \param  value the value should be write into the *ptr.
 *  \retval STATUS_OK write succussfully.
 *  \retval ERR_BAD_DATA One of the bytes sent was corrupted during transmission.
 */
enum status_code xnvm_st_star_ptr_postinc(uint8_t value)
{
	cmd_buffer[0] = XNVM_PDI_ST_INSTR | XNVM_PDI_LD_PTR_STAR_INC_MASK |
			XNVM_PDI_BYTE_DATA_MASK;
	cmd_buffer[1] = value;

	return pdi_write(cmd_buffer, 2);
}

/**
 *  \internal
 *  \brief Write a address in PDI Controller's pointer.
 *
 *  \param  address the address which should be written into the ptr.
 *  \retval STATUS_OK write successfully.
 *  \retval ERR_BAD_DATA One of the bytes sent was corrupted during transmission.
 */
enum status_code xnvm_st_ptr(uint32_t address)
{
	cmd_buffer[0] = XNVM_PDI_ST_INSTR | XNVM_PDI_LD_PTR_ADDRESS_MASK |
			XNVM_PDI_LONG_DATA_MASK;

	mem_move((uint8_t*)&address, (cmd_buffer + 1), 4);

	return pdi_write(cmd_buffer, 5);
}

/**
 *  \brief Read the memory (include flash, eeprom, user signature, fuse bits)with NVM controller.
 *
 *  \param  address the address of the memory.
 *  \param  data the pointer which points to the data buffer.
 *  \param  length the data length.
 *  \retval non-zero the read byte length.
 *  \retval zero read fail.
 */
uint16_t xnvm_read_memory(uint32_t address, uint8_t *data, uint16_t length)
{
	xnvm_ctrl_cmd_write(XNVM_CMD_READ_NVM_PDI);
	xnvm_st_ptr(address);

	if (length > 1) {
			xnvm_write_repeat(length);
	}

	cmd_buffer[0] = XNVM_PDI_LD_INSTR | XNVM_PDI_LD_PTR_STAR_INC_MASK |
			XNVM_PDI_BYTE_DATA_MASK;
	pdi_write(cmd_buffer, 1);

	return pdi_read(data, length, WAIT_RETRIES_NUM);
}

/**
 *  \internal
 *  \brief Erase the user signature with NVM controller.
 *
 *  \retval STATUS_OK erase succussfully.
 *  \retval ERR_TIMEOUT time out.
 */
enum status_code xnvm_erase_user_sign(void)
{
	enum status_code ret = xnvm_ctrl_cmd_write(XNVM_CMD_ERASE_USER_SIGN);
	if(ret != STATUS_OK)
		return ret;

	/* Dummy write for starting the erase command */
	ret = xnvm_st_ptr(XNVM_SIGNATURE_BASE);
	if(ret != STATUS_OK)
		return ret;
	
	ret = xnvm_st_star_ptr_postinc(DUMMY_BYTE);
	if(ret != STATUS_OK)
		return ret;

	return xnvm_ctrl_wait_nvmbusy(WAIT_RETRIES_NUM);
}

/**
 *  \internal
 *  \brief Erase and program the user signature with NVM controller.
 *
 *  \param  address the address of the user signature.
 *  \param  dat_buf the pointer which points to the data buffer.
 *  \param  length the data length.
 *  \retval STATUS_OK program succussfully.
 *  \retval ERR_TIMEOUT time out.
 */
enum status_code xnvm_erase_program_user_sign(void)
{
	enum status_code ret = xnvm_erase_user_sign();
	if(ret != STATUS_OK)
		return ret;
	
	ret = xnvm_ctrl_cmd_write(XNVM_CMD_WRITE_USER_SIGN);
	if(ret != STATUS_OK)
		return ret;
		
	/* Dummy write for starting the write command. */
	ret = xnvm_st_ptr(XNVM_SIGNATURE_BASE);
	if(ret != STATUS_OK)
		return ret;
		
	ret = xnvm_st_star_ptr_postinc(DUMMY_BYTE);
	if(ret != STATUS_OK)
		return ret;

	return xnvm_ctrl_wait_nvmbusy(WAIT_RETRIES_NUM);
}

/**
 *  \brief Write the fuse bit with NVM controller
 *
 *  \param  address the fuse bit address.
 *  \param  value which should be write into the fuse bit.
 *  \param  retries the time out delay number.
 *  \retval STATUS_OK write succussfully.
 *  \retval ERR_TIMEOUT time out.
 */
enum status_code xnvm_write_fuse_bit(uint32_t address, uint8_t value, uint32_t retries)
{

	xnvm_ctrl_cmd_write(XNVM_CMD_WRITE_FUSE);

	cmd_buffer[0] = XNVM_PDI_STS_INSTR | XNVM_PDI_LONG_ADDRESS_MASK |
			XNVM_PDI_BYTE_DATA_MASK;

	mem_move((uint8_t*)&address, (cmd_buffer + 1), 4);
	cmd_buffer[5] = value;

	pdi_write(cmd_buffer, 6);

	return xnvm_ctrl_wait_nvmbusy(retries);
}

/**
 *  \internal
 *  \brief Wait until the NVM Controller is ready.
 *
 *  \param  retries the retry count.
 *  \retval STATUS_OK BUSY bit was set.
 *  \retval ERR_TIMEOUT Time out.
 */
enum status_code xnvm_ctrl_wait_nvmbusy(uint32_t retries)
{
	uint8_t status;

	while (retries != 0) {
			xnvm_ctrl_read_status(&status);

			/* Check if the NVMBUSY bit is clear in the NVM_STATUS register. */
			if ((status & XNVM_NVM_BUSY) == 0) {
					return STATUS_OK;
			}
			--retries;
	}
	return ERR_TIMEOUT;
}

/**
 * \brief Function for closing the PDI communication to the device.
 *
 * \retval always STATUS_OK;
 */
enum status_code xnvm_deinit(void)
{
	pdi_deinit();
	initialized = 0;
	return STATUS_OK;
}

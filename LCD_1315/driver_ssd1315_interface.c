/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @file      driver_ssd1315_interface.c
 * @brief     driver ssd1315 interface source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-11-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/11/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_ssd1315_interface.h"
#include "ti_msp_dl_config.h"

/**
 * @brief  interface iic bus init
 * @return status code
 *         - 0 success
 *         - 1 iic init failed
 * @note   SysConfig generates complete I2C init (power, GPIO, clock,
 *         controller mode at 100kHz) in SYSCFG_DL_I2C_LCD_init().
 */
uint8_t ssd1315_interface_iic_init(void)
{
    SYSCFG_DL_I2C_LCD_init();
    return 0;
}

/**
 * @brief  interface iic bus deinit
 * @return status code
 *         - 0 success
 *         - 1 iic deinit failed
 * @note   none
 */
uint8_t ssd1315_interface_iic_deinit(void)
{
    DL_I2C_disableController(I2C_LCD_INST);
    return 0;
}

/**
 * @brief     interface iic bus write
 * @param[in] addr iic device write address (8-bit, e.g. 0x78)
 * @param[in] reg control byte (0x00=command, 0x40=data)
 * @param[in] *buf pointer to a data buffer
 * @param[in] len length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t ssd1315_interface_iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint16_t totalLen = 1 + len;
    uint32_t status;

    /* Wait for I2C to be idle before starting new transaction */
    while (!(DL_I2C_getControllerStatus(I2C_LCD_INST) &
             DL_I2C_CONTROLLER_STATUS_IDLE));

    /* Fill TX FIFO: send control byte (reg) first, then data */
    DL_I2C_fillControllerTXFIFO(I2C_LCD_INST, &reg, 1);
    if (len > 0) {
        uint16_t written = DL_I2C_fillControllerTXFIFO(I2C_LCD_INST, buf, len);
        buf += written;
        len -= written;
    }

    /* Start I2C transfer (addr is 8-bit e.g. 0x78, convert to 7-bit 0x3C) */
    DL_I2C_startControllerTransfer(I2C_LCD_INST, addr >> 1,
        DL_I2C_CONTROLLER_DIRECTION_TX, totalLen);

    /* If data exceeds FIFO size (8 bytes), refill during transmission */
    while (len > 0) {
        while (DL_I2C_getControllerTXFIFOCounter(I2C_LCD_INST) >=
               DL_I2C_RX_FIFO_COUNT_MAXIMUM);
        DL_I2C_transmitControllerData(I2C_LCD_INST, *buf);
        buf++;
        len--;
    }

    /* Wait for transfer to complete */
    while (DL_I2C_getControllerStatus(I2C_LCD_INST) &
           DL_I2C_CONTROLLER_STATUS_BUSY);

    /* Check for errors (NACK, arbitration lost, etc.) */
    status = DL_I2C_getControllerStatus(I2C_LCD_INST);
    if (status & DL_I2C_CONTROLLER_STATUS_ERROR) {
        return 1;
    }

    return 0;
}

/**
 * @brief  interface spi bus init
 * @return status code
 *         - 0 success
 *         - 1 spi init failed
 * @note   none
 */
uint8_t ssd1315_interface_spi_init(void)
{
    return 0;
}

/**
 * @brief  interface spi bus deinit
 * @return status code
 *         - 0 success
 *         - 1 spi deinit failed
 * @note   none
 */
uint8_t ssd1315_interface_spi_deinit(void)
{
    return 0;
}

/**
 * @brief     interface spi bus write
 * @param[in] *buf pointer to a data buffer
 * @param[in] len length of data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t ssd1315_interface_spi_write_cmd(uint8_t *buf, uint16_t len)
{
    return 0;
}

/**
 * @brief     interface delay ms
 * @param[in] ms time
 * @note      none
 */
void ssd1315_interface_delay_ms(uint32_t ms)
{
    delay_cycles((CPUCLK_FREQ / 1000UL) * ms);
}

/**
 * @brief     interface print format data
 * @param[in] fmt format data
 * @note      none
 */
void ssd1315_interface_debug_print(const char *const fmt, ...)
{

}

/**
 * @brief  interface command && data gpio init
 * @return status code
 *         - 0 success
 *         - 1 gpio init failed
 * @note   none
 */
uint8_t ssd1315_interface_spi_cmd_data_gpio_init(void)
{
    return 0;
}

/**
 * @brief  interface command && data gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 gpio deinit failed
 * @note   none
 */
uint8_t ssd1315_interface_spi_cmd_data_gpio_deinit(void)
{
    return 0;
}

/**
 * @brief     interface command && data gpio write
 * @param[in] value written value
 * @return    status code
 *            - 0 success
 *            - 1 gpio write failed
 * @note      none
 */
uint8_t ssd1315_interface_spi_cmd_data_gpio_write(uint8_t value)
{
    return 0;
}

/**
 * @brief  interface reset gpio init
 * @return status code
 *         - 0 success
 *         - 1 gpio init failed
 * @note   none
 */
uint8_t ssd1315_interface_reset_gpio_init(void)
{
    return 0;
}

/**
 * @brief  interface reset gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 gpio deinit failed
 * @note   none
 */
uint8_t ssd1315_interface_reset_gpio_deinit(void)
{
    return 0;
}

/**
 * @brief     interface reset gpio write
 * @param[in] value written value
 * @return    status code
 *            - 0 success
 *            - 1 gpio write failed
 * @note      none
 */
uint8_t ssd1315_interface_reset_gpio_write(uint8_t value)
{
    return 0;
}
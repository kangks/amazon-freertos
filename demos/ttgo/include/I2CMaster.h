#ifndef _I2CMASTER_H_
#define _I2CMASTER_H_

#include <stdint.h>
#include "sdkconfig.h"
#include "driver/i2c.h"

#define I2C_MASTER_SCL_IO    GPIO_NUM_22    /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO    GPIO_NUM_21    /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM       I2C_NUM_1      /*!< I2C port number for master dev */
#define I2C_MASTER_TX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_MASTER_FREQ_HZ    400000     /*!< I2C master clock frequency */

#define WRITE_BIT  I2C_MASTER_WRITE /*!< I2C master write */
#define READ_BIT   I2C_MASTER_READ  /*!< I2C master read */
#define ACK_CHECK_EN   0x1     /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS  0x0     /*!< I2C master will not check ack from slave */
#define ACK_VAL    0x0         /*!< I2C ack value */
#define NACK_VAL   0x1         /*!< I2C nack value */


class I2CMaster
{
    public:
        I2CMaster(i2c_port_t i2cnum = I2C_NUM_1, gpio_num_t sda = I2C_MASTER_SDA_IO, gpio_num_t scl = I2C_MASTER_SCL_IO,
        uint32_t freq = I2C_MASTER_FREQ_HZ)
            :i2c_port(i2cnum),
            m_sda(sda),
            m_scl(scl),
            m_freq(freq)
        {}
        ~I2CMaster() {}

        void init();
        esp_err_t write(uint8_t addr, uint8_t * bytes, size_t length, bool ack);
        esp_err_t read(uint8_t addr, uint8_t * bytes, size_t length, bool ack);

        esp_err_t write_reg(uint8_t addr, uint8_t reg, uint8_t * bytes, size_t length, bool ack);

    private:
        i2c_cmd_handle_t beginTransaction();
        esp_err_t        endTransaction(i2c_cmd_handle_t cmd);

        i2c_port_t i2c_port;
        gpio_num_t m_sda;
        gpio_num_t m_scl;
        uint32_t m_freq;
};

#endif

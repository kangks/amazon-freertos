#include "I2CMaster.h"
#include <esp_log.h>

static const char * TAG = "I2C";

void I2CMaster::init()
{
	i2c_config_t conf;
    // Initialize I2C, enable pull-up resistors
	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = m_sda;
	conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf.scl_io_num = m_scl;
	conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = m_freq;
    esp_err_t errRc = ::i2c_param_config(i2c_port, &conf);
    if (errRc != ESP_OK)
    {
        ESP_LOGE(TAG, "Error in i2c_param_config (%d)\n", errRc);
    }

	errRc = ::i2c_driver_install(i2c_port, conf.mode,
			I2C_MASTER_RX_BUF_DISABLE,
			I2C_MASTER_TX_BUF_DISABLE, 0);

    if (errRc != ESP_OK)
    {
        ESP_LOGE(TAG, "Error in i2c_driver_install (%d)\n", errRc);
    }

    ESP_LOGD(TAG, "I2C (%d) driver installed!\n", i2c_port);
}

esp_err_t I2CMaster::write(uint8_t addr, uint8_t * bytes, size_t length, bool ack)
{
    // start transaction
    i2c_cmd_handle_t cmd = beginTransaction();

    // First write the address
    esp_err_t errRc = ::i2c_master_write_byte(cmd, addr << 1 | I2C_MASTER_WRITE, !ack);
    if (errRc != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed writing I2C address!\n");
        return errRc;
    }

    // Write the rest of the data
    errRc = ::i2c_master_write(cmd, bytes, length, !ack);
    if (errRc != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%d) on i2c_master_write()\n", errRc);
        return errRc;
    }

    // end the transaction
    endTransaction(cmd);
    return ESP_OK;
}

esp_err_t I2CMaster::write_reg(uint8_t addr, uint8_t reg, uint8_t * bytes, size_t length, bool ack)
{
    // start transaction
    i2c_cmd_handle_t cmd = beginTransaction();

    // First write the address
    esp_err_t errRc = ::i2c_master_write_byte(cmd, addr << 1 | I2C_MASTER_WRITE, !ack);
    if (errRc != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed writing I2C address!\n");
        return errRc;
    }
    // Write to a command register
    errRc = ::i2c_master_write_byte(cmd, reg, !ack);
    if (errRc != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed writing I2C address!\n");
        return errRc;
    }
    

    // Write the rest of the data
    errRc = ::i2c_master_write(cmd, bytes, length, !ack);
    if (errRc != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%d) on i2c_master_write()\n", errRc);
        return errRc;
    }

    // end the transaction
    endTransaction(cmd);
    return ESP_OK;
}


esp_err_t I2CMaster::read(uint8_t addr, uint8_t * bytes, size_t length, bool ack)
{
    // start transaction
    i2c_cmd_handle_t cmd = beginTransaction();

    esp_err_t errRc;
    // Write the address
    errRc = ::i2c_master_write_byte(cmd, addr << 1 | I2C_MASTER_READ, !ack);
    if (errRc != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed writing I2C address!\n");
        return errRc;
    }
    // Read the rest of the data
    // In reading multiple bytes from a slave, we only require acknowledgement on
    // the last byte
    if (length > 1)
    {
        errRc = ::i2c_master_read(cmd, bytes, length - 1, I2C_MASTER_NACK);
        if (errRc != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed reading %d from I2C\n", length - 1);
            return errRc;
        }
    }
    
    errRc = ::i2c_master_read(cmd, bytes + length, length, ack ? I2C_MASTER_ACK : I2C_MASTER_NACK);
    if (errRc != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%d) on i2c_master_read()\n", errRc);
        return errRc;
    }

    // end transaction
    endTransaction(cmd);

    return ESP_OK;
}

i2c_cmd_handle_t I2CMaster::beginTransaction()
{
    ESP_LOGD(TAG, "Starting I2C transaction...\n");
    i2c_cmd_handle_t cmd = ::i2c_cmd_link_create();
    esp_err_t errRc = ::i2c_master_start(cmd);
    if (errRc != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%d) on i2c_master_start()\n", errRc);
        return 0;
    }

    return cmd;
}

esp_err_t I2CMaster::endTransaction(i2c_cmd_handle_t cmd)
{
    ESP_LOGD(TAG, "Ending I2C transaction...\n");
    esp_err_t errRc = ::i2c_master_stop(cmd);
    if (errRc != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%d) on i2c_master_stop()\n", errRc);
        return errRc;
    }

    // Now process the transaction ..
    errRc = ::i2c_master_cmd_begin(i2c_port, cmd, 1000/portTICK_PERIOD_MS);
    if (errRc != ESP_OK)
    {
        ESP_LOGE(TAG, "Error (%d) on i2c_master_begin()\n", errRc);
        return errRc;
    }

    // Delete the completed i2c transaction
    ::i2c_cmd_link_delete(cmd);

    return ESP_OK;
}


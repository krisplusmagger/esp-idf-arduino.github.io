/* i2c - Simple example

   Simple I2C example that shows how to initialize I2C
   as well as reading and writing from and to registers for a sensor connected over I2C.


   See README.md file to get detailed usage of this example.

   This example code is in the Public Domain (or CC0 licensed, at your option.)
   更改cpu频率（shift the frequency of cpu)  idf.py menuconfig
  
*/
#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"

static const char *TAG = "i2c-simple-example";

#define I2C_MASTER_SCL_IO           CONFIG_I2C_MASTER_SCL      /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           CONFIG_I2C_MASTER_SDA      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

#define PCF8591_ADDR 0x48  //slave address of the PCF8591chip
#define PCF8591_AOUT_0 0x40  //ain0输入和aout模拟输出
#define PCF8591_AIN0 0x00
#define PCF8591_AIN1 0x01
#define PCF8591_AIN2 0x02
#define PCF8591_AIN3 0x03

/** 
 * @brief read bytes from a PCF8591 registers
 * reg_addr  是 write_buffer
 */

static esp_err_t pcf8951_read(uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_master_read_from_device(I2C_MASTER_NUM,PCF8591_ADDR, data, len, I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
}

/**
 * @brief Write a byte to a pcf8591 sensor register
 * reg-addr是控制寄存器的命令，让他做ad 转换， data是ad转换的数据
 */
static esp_err_t pcg8591_register_write_byte(uint8_t reg_addr, uint8_t *data)
{
    int ret;
    uint8_t write_buf[2] = {reg_addr,data[0]};
    ret = i2c_master_write_to_device(I2C_MASTER_NUM, PCF8591_ADDR, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
    return ret;

}

/**
 * @brief i2c master initialization
 */
static esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}


void app_main(void)
{
    uint8_t data[2];
    uint8_t read[2];
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");
    data[0] = 0 ;
    ESP_ERROR_CHECK(pcg8591_register_write_byte(PCF8591_AOUT_0,data));
    while(1){
    
    ESP_ERROR_CHECK(pcf8951_read(PCF8591_AIN0, read, 1));
    ESP_LOGI(TAG, "data = %d", read[0]);
    
    }
 
}

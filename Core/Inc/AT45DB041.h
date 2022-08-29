/**
 * @file AT45DB041.h
 * @author your name (you@domain.com)
 * @brief  Driver for AT45DB041E memory flash extern (SPI) LOW LEVEL
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
 *
 */


#include <stdio.h>



// Private functions 


typedef enum {
    STATUS_ERROR = 0,
    STATUS_OK
} status_t;

typedef enum {
    LEVEL_LOW =0,
    LEVEL_HIGH
} level_t;







 uint8_t get_status(void);

 uint8_t is_ready(void);



/**
 * @brief Write in buffer 1, SRAM....volatile
 * 
 * @param data 
 * @param len 
 * @param pos 
 * @return ** uint8_t 
 */
 uint8_t write_buffer1(uint8_t* data,uint16_t len, uint16_t pos);



/**
 * @brief Read en buffer 1, en SRAM ...volatile
 * 
 * @param data 
 * @param len 
 * @param pos 
 * @return ** uint8_t 
 */
uint8_t read_buffer1(uint8_t* data,uint16_t len, uint16_t pos);


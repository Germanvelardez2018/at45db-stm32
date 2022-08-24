/**
 * @file AT45DB041.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */




#include "AT45DB041.h"






#define      CMD_READSTATUS        (0x57)


// READ FUNCTIONS
#define      CMD_READBUFF1              (0x54)
#define      CMD_READBUFF2              (0x56)
#define      CMD_READPAGE               (0x52)      


//WRITE FUNCTIONS

#define    CMD_WRITEBUFF1                (0x84)
#define    CMD_WRITEBUFF2                (0x87)
#define    CMD_WRITEPAGEWBUFF1           (0X82)
#define    CMD_WRITEPAGEWBUFF2           (0X85)



// STATE

#define CMD_RESUMEN                       (0xAB)
#define CMD_LOWPOWER                      (0x9B)  // INTO LOW POWER



// MASK

#define AT45DB_STATUS_COMP                (1 << 6) /* COMP */
#define AT45DB_STATUS_READY               (1 << 7) /* RDY/BUSY */

#define PRIVATE    static






// You need define this function with your HAL function.


PRIVATE status_t spi_init(){
        return STATUS_OK;
}


PRIVATE status_t gpio_init(){
        return STATUS_OK;
}


PRIVATE  status_t  gpio_write(level_t value){
        return STATUS_OK;
}


PRIVATE  level_t   gpio_read (){
        return LEVEL_LOW;
}


PRIVATE  status_t  spi_write(uint8_t* buffer, size_t len ){
            return STATUS_OK;
}

PRIVATE  status_t  spi_read(uint8_t* buffer, size_t len){
        return STATUS_OK;
}






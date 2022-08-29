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
#include "main.h"

extern hspi2;





// READ FUNCTIONS
#define      CMD_READBUFF1                   (0xD4)
#define      CMD_READBUFF2                   (0x56)
#define      CMD_READPAGE                    (0x52)      


//WRITE FUNCTIONS
#define    CMD_WRITEBUFF1                    (0x84)
#define    CMD_WRITEBUFF2                    (0x87)
#define    CMD_PAGETOBUFF1                   (0x53)
#define    CMD_PAGETOBUFF2                   (0x55)

#define    CMD_PAGEERASEBUFF1                 (0x83)  // Write tn page through buffer1
#define    CMD_PAGEERASEBUFF2                 (0X86)  // Write to page through buffer 2

#define    CMD_PAGEBUFF1                      (0X88)
#define    CMD_PAGEBUFF1                      (0X89)

#define    CMD_PAGEBUFF1POS                    (0x02) // ! Permite seleecionar la posicion inicial

// COMPARE FUNCTIONS
#define    CMD_CMPBUFF1                      (0x60)
#define    CMD_CMPBUFF2                      (0x61)

// STATE
#define    CMD_GETSTATUS                    (0xD7)   //! status register 2 bytes
#define    CMD_RESUMEN                      (0xAB)
#define    CMD_LOWPOWER                     (0xB9)  
#define    CMD_READID                       (0x9F)
// ID_DEVICE

#define DEVICE_ID_0                          0x1F    //id byte  1
#define DEVICE_ID_1                          0x24    //id byte  2
#define DEVICE_ID_2                          0x00    //id byte  3
#define EDI                                  0x01    // id byte 4



// CONFIG SIZE FROM 265 TO 255 BYTE PER PAGE
#define CMD_RESIZE                       (0x3D, 0x2A, 0x80, 0xA6)
#define CMD_READSTATUS                   (0x57)

// ERASE MEMORY

#define CMD_ERASEPAGE                   (0X81)
#define CMD_ERASEBLOCK                  (0x50)
#define CMD_ERASESECTOR                 (0x7C)
#define SEC_ERASECHIP                   (0xC7, 0x94, 0x80, 0x9A)


// MASK

#define AT45DB_STATUS_COMP                (1 << 6) /* COMP */
#define AT45DB_STATUS_READY               (1 << 7) /* RDY/BUSY */



#define AT45DB_STATUS_PGSIZE                (1 << 0) /* PAGE SIZE */
#define AT45DB_STATUS_PROTECT               (1 << 1) /* PROTECT */
#define AT45DB_STATUS_COMP                  (1 << 6) /* COMP */
#define AT45DB_STATUS_READY                 (1 << 7) /* RDY/BUSY */



#define PRIVATE    static






// You need define this function with your HAL function.


PRIVATE void delay(uint32_t time){
        HAL_Delay(time);
}


PRIVATE status_t spi_init(){
        return STATUS_OK;
}


PRIVATE status_t gpio_init(){
        return STATUS_OK;
}


PRIVATE  status_t  gpio_write(level_t value){
        
        if(value){
        HAL_GPIO_WritePin(SPI_CS_GPIO_Port,SPI_CS_Pin,1);
        }
        else{
        HAL_GPIO_WritePin(SPI_CS_GPIO_Port,SPI_CS_Pin,0);
        }
        return STATUS_OK;
}


PRIVATE  level_t   gpio_read (){
        return LEVEL_LOW;
}


PRIVATE  status_t  spi_write(uint8_t* buffer, size_t len ){
            HAL_SPI_Transmit(&hspi2,buffer,len,1000);

            return STATUS_OK;
}

PRIVATE  status_t  spi_read(uint8_t* buffer, size_t len){
        HAL_SPI_Receive(&hspi2,buffer,len,1000);

        return STATUS_OK;
}







// PRIVATE FUNCTION API


PRIVATE uint8_t  at45db_get_status(){
        uint8_t first_byte_status[2] = {0};
        uint8_t cmd = CMD_GETSTATUS;
        gpio_write(0);
        spi_write(&cmd,1); // Leo los 2 bytes de registro de status
        spi_read(&first_byte_status,2); // Leo los 2 bytes de registro de status
        gpio_write(1);
        return first_byte_status[0];

}


PRIVATE uint8_t at45db_is_ready(){
        uint8_t ret= 0; // Device bussy
        ret = at45db_get_status() ;
        return (ret & AT45DB_STATUS_READY);
}



PRIVATE uint8_t  at45db_check_id(){
        uint8_t ret = 0;
        uint8_t data[4]={0};
        uint8_t cmd = CMD_READID;
        gpio_write(0);
        spi_write(&cmd,1);
        spi_read(&data,4);
        gpio_write(1);
        if(data[0] == DEVICE_ID_0   
        || data[1] == DEVICE_ID_1        
        || data[2] == DEVICE_ID_2        
        || data[3] == EDI) {
                ret = 1; // id checked. OK
        }
        return ret;
}








 uint8_t get_status(){
        uint8_t res = at45db_status();
        return res;
}

uint8_t is_ready(){
        uint8_t ret = at45db_is_ready();
        uint32_t timeout = 500;
        while(!(ret = at45db_is_ready) || (timeout != 0) ){
                timeout --;
                delay(1);
        }
                ret = at45db_check_id();
        return ret;
}


uint8_t write_buffer1(uint8_t* data,uint16_t len, uint16_t pos){
        uint8_t ret=0;
        uint32_t address =  pos ;   // position into the buffer
        uint8_t cmd[4] ={0};
        cmd[0] = CMD_WRITEBUFF1;
        cmd[1] = (address >> 24) & 0xFF;
        cmd[2] = (address >> 16) & 0xFF;
        cmd[3] = (address >> 8)  & 0xFF;
        gpio_write(0);
        spi_write(&cmd,4);
        spi_write(data,len);

        gpio_write(1);


        return ret;

}




uint8_t read_buffer1(uint8_t* data,uint16_t len, uint16_t pos){
        uint8_t ret=0;
        uint32_t address =  pos ;   // position into the buffer
        uint8_t cmd[4] ={0};
        cmd[0] = CMD_READBUFF1;
        cmd[1] = (address >> 24) & 0xFF;
        cmd[2] = (address >> 16) & 0xFF;
        cmd[3] = (address >> 8)  & 0xFF;
        gpio_write(0);
        spi_write(&cmd,4);
        spi_read(data,len);

        gpio_write(1);


        return ret;

}


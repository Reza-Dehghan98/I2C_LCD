/*In the Name of God*/
/**
 * @file LCD.h
 * @author Reza Dehghan (rezzadehghan98@gmail.com)
 * @brief this Library use for LCD I2C
 * @version 0.1
 * @date 2023-09-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _LCD_H
#define _LCD_H

#ifdef __cplusplus 
    extern "C" {
#endif


#include "stdint.h"

#define LCD_CHECK_ENABLE 1


typedef int8_t LCD_LenType;
typedef uint32 LCD_Timestamp;



typedef struct {
    void*    I2c;
    uint32_t I2C_SlaveAddress;
} LCD_Config;

typedef struct {
    LCD_LenType Row;
    LCD_LenType Col;
} LCD_Cursor;


typedef enum {
    LCD_Disable = 0,
    LCD_Enable  = 1,
} LCD_Status;

typedef enum {
    LCD_lock   = 1,
    LCD_UnLock = 0,
} LCD_LockStatus;




typedef enum {
    LCD_Ok               = 0,
    LCD_Error            = 1,
    LCD_Busy             = 2,
    LCD_TimeOutError     = 3, 
    LCD_HeaderValueError = 4,
    LCD_Null             = 5,
    LCD_NullConfig       = 6,
} LCD_Result;


struct _LCD;
typedef struct _LCD LCD;

struct _LCD{
    struct _LCD*        Previous;
    const LCD_Config*   config;
    void*               Arg;
    LCD_Cursor          Cursor;
    uint8_t             Locked    :1;
    uint8_t             Enabled   :1;
    uint8_t             Configured:1;
    uint8_t             Reserved  :5;
};

typedef LCD_Result (*LCD_transmitFn) (LCD* lcd, uint8_t* data, uint8_t len);
typedef void       (*LCD_delayMsFn)  (LCD_Timestamp time);

typedef struct {
    LCD_transmitFn      LCDTransmit;
    LCD_delayMsFn       LCDDelay;
} LCD_Driver;

#define LCD_NULL_DRIVER (LCD_Driver*)0
#define LCD_NULL        (LCD*)0
#define LCD_NULL_CONFIG (LCD_Config*)0 



void       LCD_driverInit(LCD_Driver* driver);
/*
LCD_Result LCD_add       (LCD* lcd, LCD_Config* config);
LCD_Result LCD_remove    (LCD* lcd);
*/
LCD_Result LCD_init      (LCD* lcd, LCD_Config* config);
LCD_Result LCD_sendCmd   (LCD* lcd, char cmd);
LCD_Result LCD_sendData  (LCD* lcd, char data);
void       LCD_setCursor (LCD* lcd, LCD_LenType row, LCD_LenType col);
void       LCD_clear     (void);
void       LCD_setEnable (LCD* lcd, LCD_Status status);
void       LCD_setConfig (LCD* lcd, LCD_Config* config);
void       LCD_setLock   (LCD* lcd, LCD_LockStatus lockStatus);
uint8_t    LCD_isEnabled (LCD* lcd);
uint8_t    LCD_isLocked  (LCD* lcd);


void       LCD_setArg    (LCD* lcd, void* arg);
void*      LCD_getArg    (LCD* lcd);







#ifdef __cplusplus
    }
#endif

#endif 
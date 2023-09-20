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

/**
 * @brief  if 1 u must set enable before use LCD Function
 * 
 */
#define LCD_CHECK_ENABLE      0

/**
 * @brief if Set u must Check Lock state before use LCD Function
 * 
 */
#define LCD_CHECK_LOCK_STATUS 0

/**
 * @brief if 1 user can use Argument Function
 * 
 */
#define LCD_USER_ARGUMENT     0


/**
 * @brief LCD LenType Typedef 
 * 
 */
typedef int8_t LCD_LenType;

/**
 * @brief LCD Timestamp Typedef
 * 
 */
typedef uint32_t LCD_Timestamp;


/**
 * @brief LCD Config Struct
 * 
 */
typedef struct {
    void*    I2c;
    uint32_t I2C_SlaveAddress;
} LCD_Config;

/**
 * @brief Cursor of LCD
 * 
 */
typedef struct {
    LCD_LenType Row;
    LCD_LenType Col;
} LCD_Cursor;


/**
 * @brief LCD Enable Status 
 * 
 */
typedef enum {
    LCD_Disable = 0,
    LCD_Enable  = 1,
} LCD_Status;


/**
 * @brief LCD LOCK Status
 * 
 */
typedef enum {
    LCD_UnLock = 0,
    LCD_lock   = 1,
} LCD_LockStatus;



/**
 * @brief LCD result 
 * 
 */
typedef enum {
    LCD_Ok               = 0,
    LCD_Error            = 1,
    LCD_Busy             = 2,
    LCD_TimeOutError     = 3, 
    LCD_HeaderValueError = 4,
    LCD_Null             = 5,
    LCD_NullConfig       = 6,
    LCD_Lock             = 7,
    LCD_NotEnable        = 8,
} LCD_Result;

/**
 * @brief PreDefined LCD Struct
 * 
 */
struct _LCD;
typedef struct _LCD LCD;


/**
 * @brief Main LCD Struct
 * 
 */
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

/**
 * @brief LCD Driver Struct
 * 
 */
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
LCD_Result LCD_init         (LCD* lcd, LCD_Config* config);
LCD_Result LCD_sendCmd      (LCD* lcd, char cmd);
LCD_Result LCD_sendData     (LCD* lcd, char data);
LCD_Result LCD_setCursor    (LCD* lcd, LCD_LenType row, LCD_LenType col);
LCD_Result LCD_clear        (void);
LCD_Result LCD_showStringAt (LCD* lcd, char* str, LCD_LenType row, LCD_LenType col);
LCD_Result LCD_showString   (LCD* lcd, char* str);
void       LCD_setConfig    (LCD* lcd, LCD_Config* config);
uint8_t    LCD_isConfigured (LCD* lcd);

#if LCD_CHECK_ENABLE
void       LCD_setEnable    (LCD* lcd, LCD_Status status);
uint8_t    LCD_isEnabled    (LCD* lcd);
#endif

#if LCD_CHECK_LOCK_STATUS
void       LCD_setLock      (LCD* lcd, LCD_LockStatus lockStatus);
uint8_t    LCD_isLocked     (LCD* lcd);
#endif

#if LCD_USER_ARGUMENT
void       LCD_setArg     (LCD* lcd, void* arg);
void*      LCD_getArg     (LCD* lcd);
#endif






#ifdef __cplusplus
    }
#endif

#endif 
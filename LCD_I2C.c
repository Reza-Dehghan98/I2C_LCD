#include "LCD_I2C.h"

/**Private user Variable*/
 const LCD_Driver* lcdDriver;
 static LCD* lastLcd;


/**
 * @brief this function use for add user Driver struct
 * 
 * @param driver Address of user Driver Struct 
 */
void LCD_driverInit(LCD_Driver* driver) {
    lcdDriver = driver;
}




/**
 * @brief this Function use for inital Lcd
 * 
 * @param lcd Address of user LCD struct
 * @param config Address of user Config Struct
 * @return LCD_Result 
 */
LCD_Result LCD_init (LCD* lcd, LCD_Config* config) {
#if LCD_CHECK_ENABLE
    if(lcd->Enabled) {
#endif   

#if LCD_CHECK_LOCK
        if (lcd->Locked != LCD_lock) {
#endif   
            if (config != LCD_NULL_CONFIG) {
                lcd->config = config;
                lcd->Configured = 1;
            }
            else {
                return LCD_NullConfig;
            }

            LCD_Result result = 0;
            // 4 bit initialisation
            //HAL_Delay(50);  // wait for >40ms
            lcdDriver->LCDDelay(50);
            result = LCD_sendCmd (0x30);
            //HAL_Delay(5);  // wait for >4.1ms
            lcdDriver->LCDDelay(5);
            result = LCD_sendCmd (0x30);
            //HAL_Delay(1);  // wait for >100us
            lcdDriver->LCDDelay(1);
            result = LCD_sendCmd (0x30);
            //HAL_Delay(10);
            lcdDriver->LCDDelay(10);
            result = LCD_sendCmd (0x20);  // 4bit mode
            //HAL_Delay(10);
            lcdDriver->LCDDelay(10);

        // display initialisation
            result = LCD_sendCmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
            //HAL_Delay(1);
            lcdDriver->LCDDelay(1);
            result = LCD_sendCmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
            //HAL_Delay(1);
            lcdDriver->LCDDelay(1);
            result = LCD_sendCmd (0x01);  // clear display
            //HAL_Delay(1);
            lcdDriver->LCDDelay(1);
            //HAL_Delay(1);
            lcdDriver->LCDDelay(1);
            result = LCD_sendCmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
            //HAL_Delay(1);
            lcdDriver->LCDDelay(1);
            result = LCD_sendCmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
#if LCD_CHECK_LOCK 
        }
    return LCD_Lock;
#endif

#if LCD_CHECK_ENABLE
    }
    return LCD_NotEnable;
#endif
}



/**
 * @brief this Function help u to send Command For LCD with I2C Protocol
 * 
 * @param lcd Address of user LCD Struct  
 * @param cmd command character u want to Send to LCD
 * @return LCD_Result 
 */
LCD_Result LCD_sendCmd (LCD* lcd, char cmd) {
#if LCD_CHECK_ENABLE
    if(lcd->Enabled) {
#endif   

#if LCD_CHECK_LOCK
        if (lcd->Locked != LCD_lock) {
#endif   
            LCD_Result result;
            char data_u, data_l;
            uint8_t data_t[4];
            data_u    = (cmd&0xf0);
            data_l    = ((cmd<<4)&0xf0);
            data_t[0] = data_u|0x0C;  //en=1, rs=0
            data_t[1] = data_u|0x08;  //en=0, rs=0
            data_t[2] = data_l|0x0C;  //en=1, rs=0
            data_t[3] = data_l|0x08;  //en=0, rs=0
            //HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
            result = lcdDriver->LCDTransmit(lcd, data_t, sizeof(data_t));
            return result;
#if LCD_CHECK_LOCK 
        }
        return LCD_Lock;
#endif

#if LCD_CHECK_ENABLE
    }
    return LCD_NotEnable;
#endif

}


/**
 * @brief  ths function use for send data with i2c protocol to the lcd
 * 
 * @param lcd Address of user LCD struct
 * @param data a character u want to show on LCD
 * @return LCD_Result 
 */
LCD_Result LCD_sendData (LCD* lcd, char data) {
#if LCD_CHECK_ENABLE
    if(lcd->Enabled) {
#endif   

#if LCD_CHECK_LOCK
        if (lcd->Locked != LCD_lock) {
#endif   
            LCD_Result result;
            char data_u, data_l;
            uint8_t data_t[4];
            data_u    = (data&0xf0);
            data_l    = ((data<<4)&0xf0);
            data_t[0] = data_u|0x0D;  //en=1, rs=0
            data_t[1] = data_u|0x09;  //en=0, rs=0
            data_t[2] = data_l|0x0D;  //en=1, rs=0
            data_t[3] = data_l|0x09;  //en=0, rs=0
            //HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
            result = lcdDriver->LCDTransmit(lcd, data_t, sizeof(data_t));
            return result;


#if LCD_CHECK_LOCK 
        }
        return LCD_Lock;
#endif

#if LCD_CHECK_ENABLE
    }
    return LCD_NotEnable;
#endif

}


/**
 * @brief this function help u to set cursor (xPos and yPos) on LCD
 * 
 * @param lcd Address of user LCD struct
 * @param row row of Lcd u want to show Data on that
 * @param col column of LCD u want to show Data on That 
 * @return LCD_Result 
 */
LCD_Result LCD_setCursor (LCD* lcd, LCD_LenType row, LCD_LenType col) {
    /*switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }*/

#if LCD_CHECK_ENABLE
    if(lcd->Enabled) {
#endif   

#if LCD_CHECK_LOCK
        if (lcd->Locked != LCD_lock) {
#endif       

    LCD_Result result;
    lcd->Cursor.Col = col;
    lcd->Cursor.Row = row;
    col = (row == 0) ? (lcd->Cursor.Col | 0x80) : (lcd->Cursor.Col | 0xC0);
    result = LCD_sendCmd(col);
    return result;

#if LCD_CHECK_LOCK 
        }
    return LCD_Lock;
#endif

#if LCD_CHECK_ENABLE
    }
    return LCD_NotEnable;
#endif
}



/**
 * @brief this Function use for clear LCD
 * 
 * @return LCD_Result 
 */
LCD_Result LCD_clear(void) {
#if LCD_CHECK_ENABLE
    if(lcd->Enabled) {
#endif   

#if LCD_CHECK_LOCK
        if (lcd->Locked != LCD_lock) {
#endif       

            LCD_Result result;        
            result = LCD_sendCmd(0x80);
            if (result != LCD_Ok) {
                return result;
            }
            for (int i=0; i<70; i++) {
                result = LCD_sendData (' ');
                if (result != LCD_Ok) {
                    return result;
                }
            }
    return LCD_Ok;
#if LCD_CHECK_LOCK 
        }
        return LCD_Lock;
#endif

#if LCD_CHECK_ENABLE
    }
    return LCD_NotEnable;
#endif
}



/**
 * @brief this Function help u to show string on LCD
 * 
 * @param lcd Address of user LCD struct  
 * @param str Address of Str u want to show on LCD 
 * @return LCD_Result 
 */
LCD_Result LCD_showString(LCD* lcd, char* str) {
#if LCD_CHECK_ENABLE
    if(lcd->Enabled) {
#endif   

#if LCD_CHECK_LOCK
        if (lcd->Locked != LCD_lock) {
#endif       
            while (*str != NULL) {
                result = lcd_send_data(*str++);
            }
            return result;

#if LCD_CHECK_LOCK 
        }
        return LCD_Lock;
#endif

#if LCD_CHECK_ENABLE
    }
    return LCD_NotEnable;
#endif
}


/**
 * @brief with this Function u can Show String on special column and row of LCD
 * 
 * @param lcd Address of user LCD struct 
 * @param str Address of str u want to show on LCD
 * @param row row of LCD u want to show data on that
 * @param col column of LCD u want to show Data on that
 * @return LCD_Result 
 */
LCD_Result LCD_showStringAt(LCD* lcd, char* str, LCD_LenType row, LCD_LenType col) {
#if LCD_CHECK_ENABLE
    if(lcd->Enabled) {
#endif   

#if LCD_CHECK_LOCK
        if (lcd->Locked != LCD_lock) {
#endif      
            LCD_setCursor(lcd, row, col);

            while (*str != NULL) {
                lcd_send_data(*str++);
            }

#if LCD_CHECK_LOCK 
        }
        return LCD_Lock;
#endif

#if LCD_CHECK_ENABLE
    }
    return LCD_NotEnable;
#endif
}


/**
 * @brief with this Function u can get Configured status of lLCD
 * 
 * @param lcd Address of user LCD struct
 * @return uint8_t  1->configured , 0->Not Configured 
 */
uint8_t LCD_isConfigured (LCD* lcd) {
    return lcd->Configured;
}



/**
 * @brief set user config in LCD struct
 * 
 * @param lcd Address of user LCD struct
 * @param config Address of user Config Struct
 */
void LCD_setConfig (LCD* lcd, const LCD_Config* config) {
    lcd->config = config;
}



#if LCD_CHECK_ENABLE
/**
 * @brief with this Function user can Enable or Disable LCD 
 * 
 * @param lcd Address of user LCD struct
 * @param status LCD_Disable = 0, LCD_Enable  = 1,
 */
void LCD_setEnable (LCD* lcd, LCD_Status status) {
    lcd->Enabled = status;
}

/**
 * @brief get Enable Status of Lcd  
 * 
 * @param lcd Address of user LCD struct
 * @return uint8_t 1->Enabled , 0->Disabled
 */
uint8_t LCD_isEnabled (LCD* lcd) {
    return lcd->Enabled;
}
#endif


#if LCD_CHECK_LOCK_STATUS

/**
 * @brief with this Function user can lock LCD
 * 
 * @param lcd Address of user LCD struct
 * @param lockStatus  LCD_lock = 1, LCD_UnLock = 0,
 */
void LCD_setLock (LCD* lcd, LCD_LockStatus lockStatus) {
    lcd->Locked = lockStatus;
}

/**
 * @brief get lock status of LCD 
 * 
 * @param lcd Address of user LCD struct
 * @return uint8_t  1->locked , 0->UnLocked
 */
uint8_t LCD_isLocked  (LCD* lcd) {
    return lcd->Locked;
}
#endif





#if LCD_USER_ARGUMENT
/**
 * @brief set user Argument
 * 
 * @param lcd Address of user LCD struct
 * @param arg Address of user Argument 
 */
void LCD_setArg (LCD* lcd, void* arg) {
    lcd->Arg = arg;
}


/**
 * @brief get user Argument
 * 
 * @param lcd Address of user LCD struct
 * @return void* user Argument
 */
void* LCD_getArg(LCD* lcd) {
    return  lcd->Arg;
}
#endif





/*
LCD_Result LCD_add(LCD* lcd, LCD_Config* config) {
    // check for null
    if (LCD_NULL == lcd) {
        return LCD_NULL;
    }
    LCD_setConfig(lcd, config);

    // add LCD to linked list
    lcd->Previous   = __lcd();
    lastLcd         = lcd;
    lcd->Configured = 1;
    lcd->Enabled    = 1;
    return LCD_Ok;
}
*/



/*
LCD_Result LCD_remove (LCD* remove) {
    LCD* pLCD  = __lcd();
    if (remove == pLCD) {
        lastLcd = remove->Previous;
        remove->Previous   = LCD_NULL;
        remove->Configured = 0;
        remove->Enabled    = 0;
        return LCD_Ok;
    }
    while (LCD_NULL != pLCD) {
        if (remove == pLCD->Previous) {
            pLCD->Previous     = remove->Previous;
            remove->Previous   = LCD_NULL;
            remove->Configured = 0;
            remove->Enabled    = 0;
            return LCD_Ok;
        }
        //pLCD = pLCD->Previous;
        __next(pLCD);
    }
    return LCD_Error;
}
*/


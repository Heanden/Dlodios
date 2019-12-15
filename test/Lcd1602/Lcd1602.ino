/*
 * @Author: your name
 * @Date: 2019-12-13 20:59:10
 * @LastEditTime: 2019-12-15 15:54:50
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \EIESd:\allitem\Dlodios\test\Lcd1602\Lcd1602.ino
 */
/*
 * LCD1602 IIC驱动
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); //配置LCD地址及行列

void setup()
{
  lcd.init();      //初始化LCD
  lcd.backlight(); //打开背光
}

void loop()
{
  lcd.setCursor(0, 0); //设置显示位置
  lcd.print("Gavin");  //显示字符数据
  delay(500);
  lcd.clear();
}

/*
 * wifi_power.c
 *
 * Power control for WIFI module.
 * 
 * Yongle Lai @ Rockchip
 *
 * There are Power supply and Power Up/Down controls for WIFI typically.
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/jiffies.h>

#include "wifi_power.h"

/*
 * rtw_channel_plan : The initialization parameter of wifi channel,
 * 					  Allow number is "0" "2" and "5".
 *					  0 => 11 ( channel 1 ~ 11 is SCAN_ACTIVE )
 *					  2 => 13 ( channel 1 ~ 13 is SCAN_ACTIVE )
 *					  5 => 14 ( channel 1 ~ 14 is SCAN_ACTIVE )
 *					  default number is "2".
 */
char init_channel_plan = 2;

#if (WIFI_GPIO_POWER_CONTROL == 1)

/*
 * GPIO to control LDO/DCDC.
 *
 * 用于控制WIFI的电源，通常是3.3V和1.8V，可能1.2V也在其中。
 *
 * 如果是扩展IO，请参考下面的例子:
 *   POWER_USE_EXT_GPIO, 0, 0, 0, PCA9554_Pin1, GPIO_HIGH
 */
struct wifi_power power_gpio = 
{
	//POWER_NOT_USE_GPIO, 0, 0, 0, 0, 0 

	// RBOX
	//POWER_USE_GPIO, POWER_GPIO_IOMUX, 
	//GPIO5D6_SDMMC1PWREN_NAME, GPIO5H_GPIO5D6, RK29_PIN5_PD6, GPIO_HIGH 

#define GPIO_WIFI_POWER       RK29_PIN5_PD6

	// YIFANG M803
//		POWER_USE_GPIO, 0, 
//		0, 0, GPIO_WIFI_POWER, GPIO_HIGH
		POWER_USE_GPIO, POWER_GPIO_IOMUX, 
		GPIO5D6_SDMMC1PWREN_NAME, GPIO5H_GPIO5D6, GPIO_WIFI_POWER, GPIO_HIGH 
	
	//SDK
	//	POWER_NOT_USE_GPIO, 0, 0, 0, 0, 0 
};

/*
 * GPIO to control WIFI PowerDOWN/RESET.
 *
 * 控制WIFI的PowerDown脚。有些模组PowerDown脚是和Reset脚短接在一起。
 */
struct wifi_power power_save_gpio = 
{
	POWER_NOT_USE_GPIO, 0, 0, 0, 0, 0 
};

/*
 * GPIO to reset WIFI. Keep this as NULL normally.
 *
 * 控制WIFI的Reset脚，通常WiFi模组没有用到这个引脚。
 */
struct wifi_power power_reset_gpio = 
{
	POWER_NOT_USE_GPIO, 0, 0, 0, 0, 0
};

/*
 * 在WIFI被上电前，会调用这个函数。
 */
void wifi_turn_on_callback(void)
{
}

/*
 * 在WIFI被下电后，会调用这个函数。
 */
void wifi_turn_off_callback(void)
{
}

/*
 * If external GPIO chip such as PCA9554 is being used, please
 * implement the following 2 function.
 *
 * id:   is GPIO identifier, such as GPIOPortF_Pin0, or external 
 *       name defined in struct wifi_power.
 * sens: the value should be set to GPIO, usually is GPIO_HIGH or GPIO_LOW.
 *
 * 如果有用扩展GPIO来控制WIFI，请实现下面的函数:
 * 函数的功能是：控制指定的IO口id，使其状态切换为要求的sens状态。
 * id  : 是IO的标识号，以整数的形式标识。
 * sens: 是要求的IO状态，为高或低。
 */
void wifi_extgpio_operation(u8 id, u8 sens)
{
	//pca955x_gpio_direction_output(id, sens);
}

/*
 * 在系统中如果要调用WIFI的IO控制，将WIFI下电，可以调用如下接口：
 *   void rockchip_wifi_shutdown(void);
 * 但注意需要在宏WIFI_GPIO_POWER_CONTROL的控制下。
 */

#endif /* WIFI_GPIO_POWER_CONTROL */


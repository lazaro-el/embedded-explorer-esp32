/**
 * 
 * This is starting point for this event.
 * 
 * 
 * 
 * 
 */


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include <max7219.h>

/***************************************************
 *
 *          MACROS 
 * 
 * ************************************************/

#define TAG "EXPLORER"

#define ONBOARD_LED GPIO_NUM_2

/* Task configuration*/
#define TASK_STACK_SIZE 2048
#define TASK_PRIO_HIGH  (configMAX_PRIORITIES - 1)
#define TASK_PRIO_LOW   (configMAX_PRIORITIES - 5)
#define TASK_PRIO_SYS   (configMAX_PRIORITIES - 10)
#define TASK_PERIOD_10MS    10
#define TASK_PERIOD_20MS    20
#define TASK_PERIOD_ALIVE   500

/* SPI configuration for MAX7219 */

/* SPI in use*/
#define HOST SPI3_HOST 

/* PIN Configuration */
#define SPI_CONFIG_MOSI_PIN         GPIO_NUM_19
#define SPI_CONFIG_CLK_PIN          GPIO_NUM_18
#define SPI_CONFIG_CS_PIN           GPIO_NUM_15

/* Number of 8x8 displays in array*/
#define CONFIG_EXAMPLE_CASCADE_SIZE     3


/***************************************************
 *
 *          Device configuration  
 * 
 * ************************************************/
/** 
 *  Max7219 device configuration
 * 
 */
max7219_t dev =
{
    .cascade_size = CONFIG_EXAMPLE_CASCADE_SIZE,
    .digits = 0,
    .mirrored = true
};


/***************************************************
 *
 *          Function prototypes 
 * 
 * ************************************************/

/**
 *    Function declarations
 */
static void system_init(void);
static void task_10ms_high_prio(void *pvParameters);
static void task_20ms_low_prio(void *pvParameters);

static void aliveness_task(void *pvParameters);


/**
 * 
 * Initialization of system LED
 * 
 */
void led_init(void)
{
    ESP_LOGI(TAG, "LED initialization");
    /* Configuration of the system aliveness LED*/
    gpio_reset_pin(ONBOARD_LED);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(ONBOARD_LED, GPIO_MODE_OUTPUT);
}

/**
 * 
 * Initialization of SPI communication for MAX7219 LED matrix
 * 
 */
void spi_max7219_init(void)
{
    // Configure SPI bus
    spi_bus_config_t cfg =
    {
        .mosi_io_num = SPI_CONFIG_MOSI_PIN,
        .miso_io_num = -1,
        .sclk_io_num = SPI_CONFIG_CLK_PIN,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 0,
        .flags = 0
    };
    ESP_ERROR_CHECK(spi_bus_initialize(HOST, &cfg, 1));
    ESP_ERROR_CHECK(max7219_init_desc(&dev, HOST, MAX7219_MAX_CLOCK_SPEED_HZ, SPI_CONFIG_CS_PIN));
    ESP_ERROR_CHECK(max7219_init(&dev));

    ESP_ERROR_CHECK(max7219_set_brightness(&dev,10));
}


/***************************************************
 *
 *          RUNNABLES 
 * 
 * ************************************************/

/*
*    Initialization, called at system start
*    Place here all system initialisation
*/
static void system_init(void)
{
    /* Initialize all LED */
    led_init();
    /* Initialization of matrix display */
    spi_max7219_init();

}

/**
 *   Runnable for system allivenes blinking
 */
void aliveness_led()
{
    static uint8_t sys_led_state = 0x00;

    gpio_set_level(ONBOARD_LED, sys_led_state);
    /* Toggle LED state for the next call*/
    sys_led_state = !sys_led_state;

}

/***************************************************
 *
 *          TASKS 
 * 
 * ************************************************/

/*
* High priority task called every 10ms
*/
static void task_10ms_high_prio(void *pvParameters)
{
    TickType_t task_called_time = xTaskGetTickCount();

        static const uint64_t symbols[] =
    {
        0x383838fe7c381000
    };
     

    while(1)
    {
        /* Call your runnables here*/
        
        /* Set next call in 10ms */
        vTaskDelayUntil(&task_called_time, pdMS_TO_TICKS(TASK_PERIOD_10MS));
    }

}

/*
* Low priority task called every 10ms
*/
static void task_20ms_low_prio(void *pvParameters)
{
    TickType_t task_called_time = xTaskGetTickCount();

    while(1)
    {
        /* Call your runnables here*/

        /* Set next call in 20ms */
        vTaskDelayUntil(&task_called_time, pdMS_TO_TICKS(TASK_PERIOD_20MS));
    }

}

/*
* Task used for showing alivenes of the system
*/
static void aliveness_task(void *pvParameters)
{
    TickType_t task_called_time = xTaskGetTickCount();

    while(1)
    {
        /* Call your runnables here*/
        aliveness_led();

        /* Set next call in 500ms */
        vTaskDelayUntil(&task_called_time, pdMS_TO_TICKS(TASK_PERIOD_ALIVE));
    }
    
}


/***************************************************
 *
 *                  MAIN 
 * 
 * ************************************************/

/*
* Main function used for initialization of the system and task creation
*/
void app_main(void)
{
    /* Start with initialization */

    ESP_LOGI(TAG,"System is booting up \n");
    system_init();

    ESP_LOGI(TAG,"System should be initialized \n");

    /* Create all tasks*/
    xTaskCreate(task_10ms_high_prio,"high_prio_10ms",TASK_STACK_SIZE,NULL,TASK_PRIO_HIGH,NULL);
    xTaskCreate(task_20ms_low_prio,"low_prio_20ms",TASK_STACK_SIZE,NULL,TASK_PRIO_LOW,NULL);
    xTaskCreate(aliveness_task,"aliveness",TASK_STACK_SIZE,NULL,TASK_PRIO_SYS,NULL);

    ESP_LOGI(TAG,"Tasks are created, system started \n");

}

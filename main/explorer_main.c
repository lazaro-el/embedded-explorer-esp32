/*

    This is starting point for this event.
    It's 

*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"

#define TAG "APP"

/* Task configuration*/
#define TASK_STACK_SIZE 2048
#define TASK_PRIO_HIGH (configMAX_PRIORITIES - 1)
#define TASK_PRIO_LOW (configMAX_PRIORITIES - 3)
#define TASK_PERIOD_10MS 10
#define TASK_PERIOD_20MS 20

/*
    Function declarations
*/
static void system_init(void);
static void task_10ms_high_prio(void *pvParameters);
static void task_20ms_low_prio(void *pvParameters);


/*
    Initialization, called at system start

    Place here all system initialisation
*/
static void system_init(void)
{

}


static void task_10ms_high_prio(void *pvParameters)
{
    TickType_t task_called_time = xTaskGetTickCount();

    while(1)
    {
        /* Call your runnables here*/

        /* Set next call in 10ms */
        vTaskDelayUntil(&task_called_time, pdMS_TO_TICKS(TASK_PERIOD_10MS));
    }

}

static void task_20ms_low_prio(void *pvParameters)
{
    TickType_t task_called_time = xTaskGetTickCount();

    while(1)
    {
        /* Call your runnables here*/

        /* Set next call in 10ms */
        vTaskDelayUntil(&task_called_time, pdMS_TO_TICKS(TASK_PERIOD_20MS));
    }

}


void app_main(void)
{
    /* Start with initialization */

    printf("System is booting up \n");
    system_init();
    printf("System should be initialized \n");

    /* Create high prio 10ms task*/
    xTaskCreate(task_10ms_high_prio,"high_prio_10ms",TASK_STACK_SIZE,NULL,TASK_PRIO_HIGH,NULL);

    xTaskCreate(task_20ms_low_prio,"low_prio_20ms",TASK_STACK_SIZE,NULL,TASK_PRIO_LOW,NULL);

    printf("Tasks are created, system started \n");

}

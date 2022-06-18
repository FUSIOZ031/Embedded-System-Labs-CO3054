#include "driver/gpio.h"
#include "esp_spi_flash.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "sdkconfig.h"
#include <stdio.h>

char task1Param[12] = "task1Param";
char task2Param[12] = "task2Param";
char task3Param[12] = "task3Param";

void task1(void * parameter)
{
    printf((char *)parameter);
    // loop forever //
    volatile uint32_t ul;
    while (1)
    {
        for( ul = 0; ul < 50; ul++ )
        {
            printf("task1 is running\n");
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
        printf("task1 is ending\n");
    }
    vTaskDelete(NULL);
}

void task2(void * parameter)
{
    printf((char *)parameter);
    volatile uint32_t ul;
    while (1)
    {
        for( ul = 0; ul < 50; ul++ )
        {
            printf("task2 is running\n");
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
        printf("task2 is ending\n");
    }
    vTaskDelete(NULL);
}

void task3(void * parameter)
{
    printf((char *)parameter);
    volatile uint32_t ul;
    while (1)
    {
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    for( ul = 0; ul < 50; ul++ )
    {
        printf("task3 is running\n");
    }
    printf("task3 is ending\n");
    }
    vTaskDelete(NULL);
    }

void app_main()
{
    xTaskCreate(task1, "task1", 10000, (void *)task1Param, 1, NULL);
    xTaskCreate(task2, "task2", 10000, (void *)task2Param, 1, NULL);
    xTaskCreate(task3, "task3", 10000, (void *)task3Param, 5, NULL);
} 

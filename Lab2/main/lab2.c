#include "driver/gpio.h"
#include "esp_spi_flash.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <stdio.h>

void worker1_task (void *pvParameters)
{
    for (;;)
    {
        printf ("1752545\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void worker2_task (void *pvParameters)
{
    while (1)
    {
        if (gpio_get_level(17)==1)
        {
            printf ("ESP32\n");
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
void app_main (void)
{
    gpio_pad_select_gpio(17);
    gpio_set_direction(17, GPIO_MODE_INPUT);
    xTaskCreate(worker1_task, "T1", 2048, NULL, 1, NULL);
    xTaskCreate(worker2_task, "T2", 2048, NULL, 2, NULL);
}
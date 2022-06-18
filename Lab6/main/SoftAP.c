#include <stdio.h>
#include <time.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_log.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include <tcpip_adapter.h>
#include <lwip/sockets.h>

esp_err_t eventHandler ( void *ctx, system_event_t *event ){
    if (event->event_id == SYSTEM_EVENT_AP_START){
        printf("We become Access Point!\n");
    }
    if(event->event_id == SYSTEM_EVENT_AP_STACONNECTED){
        printf("Station connect\n");
    }
    return ESP_OK ;
}
int app_main(void){
    nvs_flash_init();
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(eventHandler, NULL));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    wifi_config_t apConfig = {
        .ap = {
            .ssid = "Nguyen Trong Tin",
            .ssid_len = 0,
            .password = "",
            .channel = 0,
            .authmode = WIFI_AUTH_OPEN,
            .ssid_hidden = 0,
            .max_connection = 4,
            .beacon_interval = 100
        }
    };
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &apConfig ));
    ESP_ERROR_CHECK(esp_wifi_start());  
    return 0;
}

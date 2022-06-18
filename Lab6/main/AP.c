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
// The IP address that we want our device to have .
#define DEVICE_IP " 192.168.1.99 "
// The Gateway address where we wish to send packets .
// This will commonly be our access point .
#define DEVICE_GW " 192.168.1.1 "
// The netmask specification .
#define DEVICE_NETMASK " 255.255.255.0 "
// The identity of the access point to which we wish to connect .
#define AP_TARGET_SSID "Nguyen Tin"
// The password we need to supply to the access point for authorization .
#define AP_TARGET_PASSWORD "tin1752545"


esp_err_t eventHandler ( void *ctx, system_event_t *event ){
    // if(event->event_id == SYSTEM_EVENT_STA_GOT_IP){
    //     printf("Our IP address is "IPSTR"\n", IP2STR(&event->event_info.got_ip.ip_info.ip));
    //     printf ("We have now connected to a station and can do things ...\n");
    // }
    if (event->event_id == SYSTEM_EVENT_STA_START){
        ESP_ERROR_CHECK(esp_wifi_connect());
    }
    return ESP_OK ;
}
int app_main(void){



    nvs_flash_init();
    tcpip_adapter_init();
    tcpip_adapter_dhcpc_stop(TCPIP_ADAPTER_IF_STA);
    tcpip_adapter_ip_info_t ipInfo;
    inet_pton(AF_INET, DEVICE_IP, &ipInfo.ip);
    inet_pton(AF_INET, DEVICE_GW, &ipInfo.gw);
    inet_pton(AF_INET, DEVICE_NETMASK, &ipInfo.netmask);
    tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_STA, &ipInfo);
    ESP_ERROR_CHECK(esp_event_loop_init(eventHandler, NULL));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    esp_wifi_set_storage(WIFI_STORAGE_RAM);
    esp_wifi_set_mode(WIFI_MODE_STA);
    wifi_config_t sta_config = {
        .sta = {
            .ssid = AP_TARGET_SSID,
            .password = AP_TARGET_PASSWORD,
            .bssid_set = 0
        }
    };
    esp_wifi_set_config(WIFI_IF_STA, &sta_config );
    esp_wifi_start();  
    return 0;
}

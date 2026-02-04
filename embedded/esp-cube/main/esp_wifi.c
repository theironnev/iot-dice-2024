#include <stdio.h> //for basic printf commands
#include <string.h> //for handling strings
#include "freertos/FreeRTOS.h" //for delay,mutexs,semphrs rtos operations
#include "esp_system.h" //esp_init funtions esp_err_t 
#include "esp_wifi.h" //esp_wifi_init functions and wifi operations
#include "esp_log.h" //for showing logs
#include "esp_event.h" //for wifi event
#include "nvs_flash.h" //non volatile storage
#include "lwip/err.h" //light weight ip packets error handling
#include "lwip/sys.h" //system applications for light weight ip apps
const char *ssid = "iotroam"
const char *pass = "oEdKTbxi21"

static const char *TAG = "main";

static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id,void *event_data){

 switch (event_id)
 {
 case WIFI_EVENT_STA_START:
    ESP_LOGI(TAG, "WIFI CONNECTING....\n");
    break;
 case  WIFI_EVENT_STA_CONNECTED:
    ESP_LOGI(TAG, "WiFi CONNECTED\n");
    break;
 case WIFI_EVENT_STA_DISCONNECTED:
    ESP_LOGI(TAG, "WiFi lost connection\n");
    if(retry_num<5){
        esp_wifi_connect();
        retry_num++;
        ESP_LOGI(TAG,"Retrying to Connect...\n");
        }
    break;
 case IP_EVENT_STA_GOT_IP:
    ESP_LOGI("Wifi got IP...\n\n");
    break;

 
 default:
    break;
 }   
if(event_id == WIFI_EVENT_STA_START)
{
  printf("WIFI CONNECTING....\n");
}
else if (event_id == WIFI_EVENT_STA_CONNECTED)
{
  printf("WiFi CONNECTED\n");
}
else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
{
  printf("WiFi lost connection\n");
  if(retry_num<5){esp_wifi_connect();retry_num++;printf("Retrying to Connect...\n");}
}
else if (event_id == IP_EVENT_STA_GOT_IP)
{
  printf("Wifi got IP...\n\n");
}
}
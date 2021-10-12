/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include <stdint.h>
#include "esp_netif.h"

void scann()
{

	wifi_scan_config_t scan_config = {
			.ssid = 0,
			.bssid = 0,
			.channel = 0,
			.show_hidden = true
	};

	printf("start scanning\n");
	esp_wifi_scan_start(&scan_config, true);
	printf("scanning completed\n");

	uint16_t ap_num = 10 ;
	wifi_ap_record_t ap_records[20];

	esp_wifi_scan_get_ap_records(&ap_num, ap_records);
	printf("found %d access point\n", ap_num);
	for( int i = 0; i < ap_num; i++ )
	{
		printf(" %32s  | %7d  |  %4d \n", ap_records[i].ssid, ap_records[i].primary, ap_records[i].rssi);
	}
}
void app_main(void)
{
 nvs_flash_init();
//tcpip_adapter_init();
 esp_netif_init();
 wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
 esp_wifi_init(&wifi_config);
 esp_wifi_start();
 while(1)
 {
	 scann();
	 vTaskDelay(3000/portTICK_RATE_MS);
 }

}

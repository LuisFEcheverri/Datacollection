#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/portmacro.h"
#include "uart.h"
#define DEMO_AP_SSID "ECHEVERRI"
#define DEMO_AP_PASSWORD "Lucas2325"
extern int main(void);
static void main_task(void *pvParameters)
{
    (void)pvParameters;
    main();
    for (;;);
}

void user_init(void)
{
    uart_init_new();
    UART_SetBaudrate(UART0, 115200);
    UART_SetPrintPort(UART0);
   printf("setting MODE\r\n");
   wifi_set_opmode(STATIONAP_MODE);
   struct station_config * config = (struct station_config *)zalloc(sizeof(struct station_config));
   sprintf((char *)config->ssid, DEMO_AP_SSID);
   sprintf((char *)config->password, DEMO_AP_PASSWORD);
   printf("Config wifi MODE\r\n");
   wifi_station_set_config(config);
   free(config);
   wifi_station_connect();
    portBASE_TYPE  error = xTaskCreate(main_task,(const signed char *)"main_task", 512, NULL, 2, NULL );
    if (error < 0) {
        printf("Error creating main_task! Error code: %ld\r\n", error);
    }
}

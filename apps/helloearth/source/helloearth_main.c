/* Hello Earth example.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "tp_app.h"

void helloearth_task(void *pvParameter)
{
    for(;;) {
      printf("Hello Earth!\n");
      TpApp_mainFunction();
      for (int i = 10; i >= 0; i--) {
          printf("Restarting in %d seconds...\n", i);
          vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
      printf("Re-running now.\n");
    }
}

void app_main()
{
    nvs_flash_init();
    TpApp_init();
    xTaskCreate(&helloearth_task, "helloearth_task", 8192, NULL, 5, NULL);
}

/* Hello Mars example.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "tp_app.h"

void hellomars_task(void *pvParameter)
{
    for(;;) {
      printf("Hello Mars!\n");
      TpApp_mainFunction();
      for (int i = 5; i >= 0; i--) {
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
    xTaskCreate(&hellomars_task, "hellomars_task", 8192, NULL, 5, NULL);
}

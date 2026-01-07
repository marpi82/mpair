/**
 * @file main.c
 * @brief Main entry point for mpair ESP32-C6 firmware
 *
 * ESP32-C6 based air quality monitoring station with integrated
 * Matter/Thread support, Ethernet/PoE, and sensor management.
 *
 * @copyright 2026 mpair contributors
 * @license GPL-3.0
 */

#include <stdio.h>

#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "mpair";

void app_main(void)
{
    ESP_LOGI(TAG, "mpair ESP32-C6 firmware starting...");
    ESP_LOGI(TAG, "ESP-IDF version: %s", esp_get_idf_version());

    // TODO: Initialize sensors
    // TODO: Initialize networking (Ethernet/WiFi)
    // TODO: Initialize Matter/Thread
    // TODO: Initialize web server
    // TODO: Initialize HECA system

    while (1) {
        ESP_LOGI(TAG, "System running...");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

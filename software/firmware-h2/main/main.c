/**
 * @file main.c
 * @brief mpair ESP32-H2 Matter/Thread Gateway Firmware
 * 
 * Thread Border Router and Matter device handler.
 * Communicates with ESP32-S3 via UART to bridge sensor data to Matter/Thread network.
 * 
 * @copyright 2026 mpair contributors
 * @license GPL-3.0
 */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"

static const char *TAG = "mpair-h2";

/**
 * @brief Main application entry point
 */
void app_main(void)
{
    ESP_LOGI(TAG, "mpair ESP32-H2 firmware starting...");
    ESP_LOGI(TAG, "Version: 0.1.0-alpha");
    
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    
    ESP_LOGI(TAG, "NVS initialized");
    
    // TODO: Initialize components
    // - Thread network stack
    // - Matter device type (Air Quality Sensor)
    // - UART communication with ESP32-S3
    // - Thread Border Router functionality (optional)
    // - Matter commissioning
    
    ESP_LOGI(TAG, "Initialization complete. Running main loop...");
    
    // Main loop
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        ESP_LOGI(TAG, "System running...");
    }
}

/**
 * @file ultrasonic_sensor_interface.c
 * @brief Interface for HC-SR04 Ultrasonic Sensor with ESP32 using ESP-IDF
 *
 * This file contains the implementation for interfacing the HC-SR04
 * ultrasonic sensor with an ESP32 microcontroller using the ESP-IDF framework.
 * It includes initialization of GPIO pins, sending trigger pulses, 
 * measuring echo pulses, and calculating distances.
 */

#include "freertos/FreeRTOS.h"  // FreeRTOS includes
#include "freertos/task.h"      // FreeRTOS task includes
#include "driver/gpio.h"        // GPIO driver includes
#include "esp_log.h"            // ESP32 logging includes

#define TRIG_PIN GPIO_NUM_4     // Define GPIO pin for the trigger
#define ECHO_PIN GPIO_NUM_5     // Define GPIO pin for the echo

static const char *TAG = "Ultrasonic";  // Tag for logging

/**
 * @brief Initialize the ultrasonic sensor GPIOs
 */
void init_ultrasonic() {
    // Configure TRIG_PIN and ECHO_PIN as GPIOs
    gpio_pad_select_gpio(TRIG_PIN);
    gpio_pad_select_gpio(ECHO_PIN);

    // Set TRIG_PIN as output and ECHO_PIN as input
    gpio_set_direction(TRIG_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(ECHO_PIN, GPIO_MODE_INPUT);

    // Initialize TRIG_PIN to low
    gpio_set_level(TRIG_PIN, 0);
}

/**
 * @brief Measure the pulse duration on the ECHO_PIN
 *
 * @return uint32_t Pulse duration in microseconds
 */
uint32_t get_pulse_duration() {
    uint32_t start_time = 0;
    uint32_t end_time = 0;

    // Send a 10us pulse to TRIG_PIN to initiate measurement
    gpio_set_level(TRIG_PIN, 1);
    ets_delay_us(10); // 10us delay
    gpio_set_level(TRIG_PIN, 0);

    // Wait for the ECHO_PIN to go high
    while (gpio_get_level(ECHO_PIN) == 0) {
        start_time = esp_timer_get_time();
    }
    // Measure the time ECHO_PIN stays high
    while (gpio_get_level(ECHO_PIN) == 1) {
        end_time = esp_timer_get_time();
    }

    // Return the duration of the echo pulse
    return end_time - start_time;
}

/**
 * @brief Calculate the distance based on the pulse duration
 *
 * @return float Distance in centimeters
 */
float get_distance() {
    // Get the pulse duration
    uint32_t duration = get_pulse_duration();
    // Calculate the distance in cm (speed of sound is 34300 cm/s)
    float distance = (duration / 2.0) * 0.0343;
    return distance;
}

/**
 * @brief Task to continuously measure distance and log the result
 *
 * @param pvParameter Task parameters (not used)
 */
void ultrasonic_task(void *pvParameter) {
    init_ultrasonic();  // Initialize the sensor
    while (1) {
        // Measure distance
        float distance = get_distance();
        // Log the distance
        ESP_LOGI(TAG, "Distance: %.2f cm", distance);
        // Delay for 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
 * @brief Main application entry point
 */
void app_main() {
    // Create and start the ultrasonic measurement task
    xTaskCreate(&ultrasonic_task, "ultrasonic_task", 2048, NULL, 5, NULL);
}

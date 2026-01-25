#include "esp_log.h"

extern "C" {
    void app_main() {
        static const char *TAG = "example"; 
        ESP_LOGD(TAG, "Debug message: Application started");
        ESP_LOGI(TAG, "Info message: Application running");
        ESP_LOGW(TAG, "Warning message: Check your configuration");
        ESP_LOGE(TAG, "Error message: An error occurred");
        //general logging examples
        //default log level is INFO
        //but can be changed via menuconfig
        //has been changed to "VERBOSE" for this example
        //so as to show all log levels
    }
}



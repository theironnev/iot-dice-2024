idf_component_register(SRCS "esp_wifi.c" "dice_mpu9250.c" "esp_AP.c" "main.c" "piezo_tone.c" 
                    INCLUDE_DIRS "."
                    REQUIRES ahrs mpu9250 esp_wifi nvs_flash mqtt esp_http_server)

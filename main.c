#include "headerFile.h"

int main() {
    CURL *curl;
    CURLcode res;
    char data[MAX_RESPONSE_SIZE] = {0};
    struct WeatherData weather_average = {0};

    int measurements_count = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        for (int i = 0; i < 1; ++i) { // Retrieve data three times a day
            int retry_count = 3; // Retry fetching data three times before giving up
            while (retry_count > 0) {
                FILE *raw_file = fopen("raw_data.txt", "wb");
                if (raw_file) {
                    curl_easy_setopt(curl, CURLOPT_URL, API_URL);
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, raw_file);

                    res = curl_easy_perform(curl);
                    if (res != CURLE_OK) {
                        fprintf(stderr, "Failed to fetch data: %s\n", curl_easy_strerror(res));
                        retry_count--; // Decrement retry count on failure
                        fclose(raw_file);
                        remove("raw_data.txt"); // Remove the file as it might contain partial data
                    } else {
                        fclose(raw_file);
                        FILE *raw_data_file = fopen("raw_data.txt", "r");
                        if (raw_data_file) {
                            fseek(raw_data_file, 0L, SEEK_END);
                            long raw_data_size = ftell(raw_data_file);
                            fseek(raw_data_file, 0L, SEEK_SET);
                            char *raw_json_data = malloc(raw_data_size + 1);
                            if (raw_json_data) {
                                fread(raw_json_data, 1, raw_data_size, raw_data_file);
                                raw_json_data[raw_data_size] = '\0';

                                FILE *processed_file = fopen("processed_data.txt", "a");
                                if (processed_file) {
                                    struct WeatherData weather = {0};
                                    print_weather_info(raw_json_data, processed_file, &weather);
                                    measurements_count++;

                                    // Calculating average
                                    weather_average.temperature += weather.temperature;
                                    weather_average.pressure += weather.pressure;
                                    weather_average.humidity += weather.humidity;
                                    weather_average.visibility += weather.visibility;
                                    weather_average.wind_speed += weather.wind_speed;
                                    weather_average.longitude += weather.longitude;
                                    weather_average.latitude += weather.latitude;
                                    weather_average.timezone += weather.timezone;
                                   
                                    measurements_count++;

                                    fclose(processed_file);
                                } else {
                                    printf("Failed to open processed_data.txt for writing!\n");
                                }

                                free(raw_json_data);
                            }
                            fclose(raw_data_file);
                        } else {
                            printf("Failed to open raw_data.txt for reading!\n");
                        }
                        break; // Break out of the retry loop on successful fetch
                    }
                } else {
                    printf("Failed to open file for writing raw data!\n");
                    retry_count--; // Decrement retry count on failure to open file
                }
            }
            if (retry_count == 0) {
                printf("Failed to fetch data after multiple attempts. Exiting...\n");
                break; // Break the main loop if failed to fetch data after retries
            }
        }

        curl_easy_cleanup(curl);
    } else {
        printf("Curl initialization failed!\n");
    }

    curl_global_cleanup();
    

    if (measurements_count > 0) {
        // Calculate average
        weather_average.temperature /= measurements_count;
        weather_average.pressure /= measurements_count;
        weather_average.humidity /= measurements_count;
        weather_average.visibility /= measurements_count;
        weather_average.wind_speed /= measurements_count;
        weather_average.longitude /= measurements_count;
        weather_average.latitude /= measurements_count;
        weather_average.timezone /= measurements_count;

        // Printing average data
        printf("------------------------\n");
        printf("Average Temperature: %.2f°C\n", weather_average.temperature);
        printf("Average Pressure: %.2f hPa\n", weather_average.pressure);
        printf("Average Humidity: %.2f%%\n", weather_average.humidity);
        printf("Average Visibility: %.2f meters\n", weather_average.visibility);
        printf("Average Wind Speed: %.2f m/s\n", weather_average.wind_speed);
        printf("Average Longitude: %.2f\n", weather_average.longitude);
        printf("Average Latitude: %.2f\n", weather_average.latitude);
        printf("Average Timezone: %d\n", weather_average.timezone);
       
        generate_report(&weather_average, measurements_count);
        send_email();
       
    } else {
        printf("No measurements were recorded!\n");
    }
    
    // Attempt to read from the report file AFTER generating and sending it
    FILE *f = fopen("report_data.txt", "r");
    if (!f) {
        printf("Failed to open report_data.txt for reading!\n");
        return 1;
    }

    char read_data[2048];

    if (fscanf(f, "%s", read_data) == 1) {
        const char *body = read_data;
        // Use 'body' as needed in your code
    } else {
        printf("Failed to read data from report_data.txt!\n");
    }

    fclose(f);
}

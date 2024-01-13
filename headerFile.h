#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define API_URL "http://api.openweathermap.org/data/2.5/weather?lat=24.860&lon=66.99051&appid=76d631002a4b7041374264eefcf396ca"
#define MAX_RESPONSE_SIZE 4096

// Constants for weather parameter ranges
#define MAX_TEMPERATURE 100.0
#define MIN_TEMPERATURE -100.0
#define MAX_PRESSURE 1100.0
#define MIN_PRESSURE 800.0
#define MAX_HUMIDITY 100.0
#define MIN_HUMIDITY 0.0
#define MAX_VISIBILITY 10000.0 // in meters
#define MIN_VISIBILITY 0.0
#define MAX_WIND_SPEED 50.0 // in m/s
#define MIN_WIND_SPEED 0.0

struct WeatherData {
    double temperature;
    double pressure;
    double humidity;
    double visibility;
    double wind_speed;
    double longitude;
    double latitude;
    char country[3];
    int timezone;
};

void print_weather_info(const char *json_data, FILE *processed_file, struct WeatherData *weather) {
    const char *temperature = strstr(json_data, "\"temp\":");
    if (temperature) {
        temperature = strchr(temperature, ':') + 1;
        weather->temperature = atof(temperature);
    }

    const char *pressure = strstr(json_data, "\"pressure\":");
    if (pressure) {
        pressure = strchr(pressure, ':') + 1;
        weather->pressure = atof(pressure);
    }

    const char *humidity = strstr(json_data, "\"humidity\":");
    if (humidity) {
        humidity = strchr(humidity, ':') + 1;
        weather->humidity = atof(humidity);
    }

    const char *visibility = strstr(json_data, "\"visibility\":");
    if (visibility) {
        visibility = strchr(visibility, ':') + 1;
        weather->visibility = atof(visibility);
    }

    const char *wind_speed = strstr(json_data, "\"speed\":");
    if (wind_speed) {
        wind_speed = strchr(wind_speed, ':') + 1;
        weather->wind_speed = atof(wind_speed);
    }

    const char *longitude = strstr(json_data, "\"lon\":");
    if (longitude) {
        longitude = strchr(longitude, ':') + 1;
        weather->longitude = atof(longitude);
    }

    const char *latitude = strstr(json_data, "\"lat\":");
    if (latitude) {
        latitude = strchr(latitude, ':') + 1;
        weather->latitude = atof(latitude);
    }

    const char *country = strstr(json_data, "\"country\":");
    if (country) {
        country = strchr(country, ':') + 2; // Move past ":"
        int i = 0;
        while (*country != '"') {
            weather->country[i++] = *country;
            country++;
        }
        weather->country[i] = '\0';
    }

    const char *timezone = strstr(json_data, "\"timezone\":");
    if (timezone) {
        timezone = strchr(timezone, ':') + 1;
        weather->timezone = atoi(timezone);
    }

    // Writing data to the processed file
    fprintf(processed_file, "-------------------------\n");
    fprintf(processed_file, "    WEATHER INFORMATION   \n");
    fprintf(processed_file, "-------------------------\n");
    fprintf(processed_file, "Temperature: %.2f°C\n", weather->temperature);
    fprintf(processed_file, "Pressure: %.2f hPa\n", weather->pressure);
    fprintf(processed_file, "Humidity: %.2f%%\n", weather->humidity);
    fprintf(processed_file, "Visibility: %.2f meters\n", weather->visibility);
    fprintf(processed_file, "Wind Speed: %.2f m/s\n", weather->wind_speed);
    fprintf(processed_file, "Longitude: %.2f\n", weather->longitude);
    fprintf(processed_file, "Latitude: %.2f\n", weather->latitude);
    fprintf(processed_file, "Country: %s\n", weather->country);
    fprintf(processed_file, "Timezone: %d\n", weather->timezone);
    fprintf(processed_file, "-------------------------\n\n");
     // Additional appealing representation without detailed descriptions
    fprintf(processed_file, "--------------------------------\n");
    fprintf(processed_file, "       ADDITIONAL INFO           \n");
    fprintf(processed_file, "--------------------------------\n");
    fprintf(processed_file, "Weather Summary: Sunny ☀\n\n");

    fprintf(processed_file, "Temperature Trend: 🌡⬆\n");
    fprintf(processed_file, "Wind Speed Trend: 🌬⬇\n");
    fprintf(processed_file, "Humidity Trend: 💧⬇\n");
    fprintf(processed_file, "Pressure Trend: ⬇\n\n");
    fprintf(processed_file, "--------------------------------\n");
}

size_t write_callback(void *ptr, size_t size, size_t nmemb, FILE *file) {
    return fwrite(ptr, size, nmemb, file);
 }  
void generate_report(const struct WeatherData *weather_average,int measurements_count) {
    FILE *report_file = fopen("report_data.txt", "w");
    if (report_file) {
        fprintf(report_file, "----------------------------------------\n");
        fprintf(report_file, "           PROFESSIONAL WEATHER REPORT\n");
        fprintf(report_file, "----------------------------------------\n\n");
       
       
        // Professional weather report opening statement
        fprintf(report_file, "Welcome to our detailed weather report! We bring you a comprehensive analysis of today's weather conditions in the area. Our analysis includes various aspects such as temperature, humidity, pressure, visibility, and wind speed to provide you with a complete understanding of today's forecast.\n\n");
       
        // Overview of weather conditions
        fprintf(report_file, "-------------------------\n");
        fprintf(report_file, "TODAYS'S WEATHER OVERVIEW:\n");
        fprintf(report_file, "-------------------------\n");
        fprintf(report_file, "TEMPERATURE: %.2f°C\n", weather_average->temperature);
        fprintf(report_file, "HUMIDITY: %.2f%%\n", weather_average->humidity);
        fprintf(report_file, "PRESSURE: %.2f hPa\n", weather_average->pressure);
        fprintf(report_file, "VISIBILITY: %.2f meters\n", weather_average->visibility);
        fprintf(report_file, "WIND SPEED: %.2f m/s\n\n", weather_average->wind_speed);

        // Detailed analysis
        fprintf(report_file, "--------------------------\n");
        fprintf(report_file, "DETAILED WEATHER ANALYSIS:\n");
        fprintf(report_file, "--------------------------\n");
        fprintf(report_file, "The temperature today is %.2f°C, with humidity at %.2f%%. The pressure stands at %.2f hPa, providing an insight into atmospheric conditions. Visibility reaches %.2f meters, while the wind speed measures %.2f m/s.\n\n",
                weather_average->temperature, weather_average->humidity, weather_average->pressure, weather_average->visibility, weather_average->wind_speed);

        // Description and explanations for each parameter
        fprintf(report_file, "TEMPERATURE: The average temperature indicates the general heat or coldness of the air. It affects human comfort and various weather conditions.\n\n");
        fprintf(report_file, "HUMIDITY: Humidity measures the amount of water vapor in the air. High humidity can make it feel hotter, while low humidity can cause dryness.\n\n");
        fprintf(report_file, "PRESSURE: Atmospheric pressure affects weather patterns. High pressure usually brings fair weather, while low pressure may indicate storms or precipitation.\n\n");
        fprintf(report_file, "VISIBILITY: Visibility refers to the distance one can see clearly. Low visibility often occurs during fog, rain, or snowfall.\n\n");
        fprintf(report_file, "WIND SPEED: Wind speed measures how fast the air is moving. It influences weather patterns and can impact outdoor activities.\n\n");
       
        // Average weather data
        fprintf(report_file, "---------------------------\n");
        fprintf(report_file, "AVERAGE WEATHER CONDITIONS:\n");
        fprintf(report_file, "---------------------------\n");
        fprintf(report_file, "Average Temperature: %.2f°C\n", weather_average->temperature / measurements_count);
        fprintf(report_file, "Average Humidity: %.2f%%\n", weather_average->humidity / measurements_count);
        fprintf(report_file, "Average Pressure: %.2f hPa\n", weather_average->pressure / measurements_count);
        fprintf(report_file, "Average Visibility: %.2f meters\n", weather_average->visibility / measurements_count);
        fprintf(report_file, "Average Wind Speed: %.2f m/s\n\n", weather_average->wind_speed / measurements_count);

        fprintf(report_file, "THANKYOU FOR READING OUR DETAILED WEATHER REPORT!\n");
        fprintf(report_file, "-----------------------------------------------\n");
        fclose(report_file);
    } else {
        printf("Failed to open report_data.txt for writing!\n");
    }
}

struct UploadStatus {
    const char *data;
    size_t size;
};

static size_t ReadCallback(void *ptr, size_t size, size_t nmemb, void *userp) {
    struct UploadStatus *upload_ctx = (struct UploadStatus *)userp;

    size_t to_copy = size * nmemb;
    if (to_copy > upload_ctx->size)
        to_copy = upload_ctx->size;

    if (to_copy) {
        memcpy(ptr, upload_ctx->data, to_copy);
        upload_ctx->data += to_copy;
        upload_ctx->size -= to_copy;
        return to_copy;
    }
}

char APP_PASSWORD[] = "dypa bfot nkga jrda"; 


void send_email() {
    CURL *emailCurl = curl_easy_init();
    FILE *f; // Declare FILE pointer for file handling

    if (emailCurl) {
        // Open file in read mode
        f = fopen("report_data.txt", "r");
        if (!f) {
            printf("Failed to open report_data.txt for reading!\n");
            return;
        }

        // Read the contents of the file
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        char *body = malloc(fsize + 1);
        if (!body) {
            printf("Memory allocation failed!\n");
            fclose(f);
            return;
        }

        fread(body, 1, fsize, f);
        fclose(f);

        body[fsize] = '\0';

        const char *from = "alisiddique.336@gmail.com";
        const char *to = "alisiddique.336@gmail.com";
        const char *subject = "Weather Report";

        char payload[4096];
        snprintf(payload, sizeof(payload), "From: %s\r\nTo: %s\r\nSubject: %s\r\n\r\n%s", from, to, subject, body);

        struct UploadStatus upload_ctx = {payload, strlen(payload)};

        curl_easy_setopt(emailCurl, CURLOPT_URL, "smtps://smtp.gmail.com:465");
        curl_easy_setopt(emailCurl, CURLOPT_USERNAME, "alisiddique.336@gmail.com");
        curl_easy_setopt(emailCurl, CURLOPT_PASSWORD, "dypa bfot nkga jrda");
        curl_easy_setopt(emailCurl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
        curl_easy_setopt(emailCurl, CURLOPT_MAIL_FROM, from);

        struct curl_slist *recipients = NULL;
        recipients = curl_slist_append(recipients, to);
        curl_easy_setopt(emailCurl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(emailCurl, CURLOPT_USERNAME, from);
        curl_easy_setopt(emailCurl, CURLOPT_PASSWORD, APP_PASSWORD);

        curl_easy_setopt(emailCurl, CURLOPT_READFUNCTION, ReadCallback);
        curl_easy_setopt(emailCurl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(emailCurl, CURLOPT_UPLOAD, 1L);

        CURLcode emailRes = curl_easy_perform(emailCurl);
        if (emailRes == CURLE_OK) {
            printf("Email sent successfully!\n");
        } else {
            printf("Failed to send email: %s\n", curl_easy_strerror(emailRes));
        }

        free(body); // Free allocated memory for body
    } else {
        printf("Email CURL initialization failed!\n");
    }
   
}

#endif //HEADERFILE

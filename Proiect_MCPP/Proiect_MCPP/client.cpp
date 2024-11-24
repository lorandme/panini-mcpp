#include <iostream>
#include <string>
#include <curl/curl.h>

size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* out) {
    size_t total_size = size * nmemb;
    out->append((char*)contents, total_size);
    return total_size;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string read_buffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Setează URL-ul endpoint-ului "/update" (exemplu: pentru actualizarea poziției tancului)
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:18080/update");

        // Datele JSON pentru poziția tancului
        std::string json_data = "{\"tancX\": 10, \"tancY\": 20}";

        // Setează datele POST
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());

        // Setează tipul de conținut (application/json)
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, "Content-Type: application/json"));

        // Setează callback-ul pentru a captura răspunsul
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

        // Trimite cererea
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Eroare la trimiterea cererii: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            std::cout << "Răspuns server: " << read_buffer << std::endl;
        }

        // Curăță și termină sesiunea curl
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}

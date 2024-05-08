#include <ESP8266WiFi.h>

// Konfigurasi jaringan WiFi
const char* ssid = "Nama_WiFi";
const char* password = "Password_WiFi";

// Pin yang digunakan
const int soilMoisturePin = A0;  // Pin untuk sensor kelembaban tanah
const int pumpPin = D1;          // Pin untuk mengontrol pompa air
const int ledPin = D2;           // Pin untuk menampilkan status penyiraman

// Ambang batas kelembaban tanah (sesuaikan dengan kebutuhan Anda)
const int dryThreshold = 500;    // Nilai kelembaban tanah di bawah ambang batas akan memicu penyiraman

void setup() {
  Serial.begin(115200);
  pinMode(soilMoisturePin, INPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Menghubungkan ke jaringan WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Membaca nilai kelembaban tanah
  int soilMoisture = analogRead(soilMoisturePin);

  // Menampilkan nilai kelembaban tanah pada Serial Monitor
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoisture);

  // Memeriksa apakah tanah terlalu kering
  if (soilMoisture < dryThreshold) {
    // Menghidupkan pompa air dan LED
    digitalWrite(pumpPin, HIGH);
    digitalWrite(ledPin, HIGH);
    Serial.println("Watering...");

    // Menyiram selama 5 detik (sesuaikan dengan kebutuhan Anda)
    delay(5000);

    // Mematikan pompa air dan LED
    digitalWrite(pumpPin, LOW);
    digitalWrite(ledPin, LOW);
    Serial.println("Watering finished.");
  }

  // Menunggu sebelum membaca kelembaban tanah lagi (sesuaikan dengan kebutuhan Anda)
  delay(60000); // Menunggu 1 menit
}

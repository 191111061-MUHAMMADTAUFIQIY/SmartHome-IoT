#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <DHT.h>

//================ FIREBASE ===================
#define API_KEY "AIzaSyCVQpN5DnSC2KR4gF-jWnjYEUmKAZA46Qc"
#define DATABASE_URL "https://smarthomeiot-4bb14-default-rtdb.asia-southeast1.firebasedatabase.app/"

#define USER_EMAIL "smarthome@gmail.com"
#define USER_PASSWORD "12345678"

//================ WIFI =======================
char ssid[] = "POCO";
char pass[] = "88888888";

//================ PIN ========================
#define DHTPIN 4
#define DHTTYPE DHT11

#define PIR_PIN 5
#define LDR_PIN 27

#define RELAY_LAMP 18
#define RELAY_FAN 19

DHT dht(DHTPIN, DHTTYPE);

//================ FIREBASE ===================
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long lastSend = 0;

//================ PIR DELAY ==================
unsigned long lastMotionTime = 0;

// 1 Menit = 60000 ms
const unsigned long motionDelay = 60000;

bool adaOrang = false;

void setup()
{
  Serial.begin(115200);
  delay(2000);

  Serial.println("=== SMART HOME START ===");

  pinMode(PIR_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);

  pinMode(RELAY_LAMP, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);

  digitalWrite(RELAY_LAMP, LOW);
  digitalWrite(RELAY_FAN, LOW);

  dht.begin();

  //================ WIFI ===================
  WiFi.begin(ssid, pass);

  Serial.print("Menghubungkan WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("WiFi Berhasil Terhubung");

  //================ FIREBASE ===================
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("Menghubungkan Firebase...");

  while (!Firebase.ready())
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("Firebase Connected");
}

void loop()
{
  if (millis() - lastSend > 2000)
  {
    lastSend = millis();

    //================ BACA SENSOR =================
    int pir = digitalRead(PIR_PIN);
    int ldr = digitalRead(LDR_PIN);

    float suhu = dht.readTemperature();
    float hum = dht.readHumidity();

    if (isnan(suhu) || isnan(hum))
    {
      Serial.println("Gagal membaca DHT11");
      return;
    }

    //================ LOGIKA PIR DELAY =================
    if (pir == HIGH)
    {
      adaOrang = true;
      lastMotionTime = millis();
    }
    else
    {
      if (millis() - lastMotionTime >= motionDelay)
      {
        adaOrang = false;
      }
    }

    //================ LOGIKA SMART HOME =================
    bool lampu = false;
    bool kipas = false;

    if (adaOrang)
    {
      // Gelap
      if (ldr == HIGH)
      {
        lampu = true;
      }

      // Suhu >= 30°C
       if (suhu >= 30.0)
      {
        kipas = true;
      }
    }

    //================ OUTPUT =================
    digitalWrite(RELAY_LAMP, lampu ? HIGH : LOW);
    digitalWrite(RELAY_FAN, kipas ? HIGH : LOW);

    //================ FIREBASE =================
    Firebase.RTDB.setFloat(&fbdo, "/SmartHome/Suhu", suhu);
    Firebase.RTDB.setFloat(&fbdo, "/SmartHome/Kelembaban", hum);

    Firebase.RTDB.setString(
      &fbdo,
      "/SmartHome/PIR",
      adaOrang ? "Ada Orang" : "Tidak Ada Orang");

    Firebase.RTDB.setString(
      &fbdo,
      "/SmartHome/LDR",
      ldr == HIGH ? "Gelap" : "Terang");

    Firebase.RTDB.setString(
      &fbdo,
      "/SmartHome/Lampu",
      lampu ? "ON" : "OFF");

    Firebase.RTDB.setString(
      &fbdo,
      "/SmartHome/Kipas",
      kipas ? "ON" : "OFF");

    //================ SERIAL =================
    Serial.println("==============================");

    Serial.print("Status Ruangan : ");
    Serial.println(adaOrang ? "Ada Orang" : "Tidak Ada Orang");

    Serial.print("PIR            : ");
    Serial.println(pir == HIGH ? "Gerakan Terdeteksi" : "Tidak Ada Gerakan");

    Serial.print("LDR            : ");
    Serial.println(ldr == HIGH ? "Gelap" : "Terang");

    Serial.print("Suhu           : ");
    Serial.print(suhu);
    Serial.println(" °C");

    Serial.print("Kelembaban     : ");
    Serial.print(hum);
    Serial.println(" %");

    Serial.print("Lampu          : ");
    Serial.println(lampu ? "ON" : "OFF");

    Serial.print("Kipas          : ");
    Serial.println(kipas ? "ON" : "OFF");

    if (adaOrang)
    {
      Serial.print("Sisa Delay PIR : ");
      Serial.println("Aktif");
    }
    else
    {
      Serial.println("Ruangan Kosong");
    }

    if (fbdo.httpCode() == 200)
    {
      Serial.println("Data berhasil dikirim ke Firebase");
    }
    else
    {
      Serial.print("Firebase Error : ");
      Serial.println(fbdo.errorReason());
    }

    Serial.println();
  }
}
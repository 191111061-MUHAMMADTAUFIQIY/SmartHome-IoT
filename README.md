# Smart Home IoT

## Sistem Rumah Pintar Berbasis IoT untuk Efisiensi Energi

### Deskripsi

Proyek ini merupakan Tugas Akhir yang membangun sistem rumah pintar berbasis Internet of Things (IoT). Sistem menggunakan ESP32 sebagai mikrokontroler untuk memonitor suhu, kelembapan, gerakan, dan intensitas cahaya secara real-time melalui Firebase serta aplikasi Android.

---

## Fitur

- Monitoring suhu (DHT11)
- Monitoring kelembapan
- Monitoring gerakan (PIR)
- Monitoring cahaya (LDR)
- Kontrol lampu
- Kontrol kipas
- Monitoring real-time menggunakan Firebase

---

## Hardware

- ESP32
- Sensor DHT11
- Sensor PIR
- Sensor LDR
- Relay 2 Channel
- Lampu
- Kipas DC

---

## Software

- Arduino IDE
- Android Studio
- Firebase Realtime Database
- Java
- XML

---

## Struktur Folder

```
ESP32/
Android/
APK/
Dokumentasi/
README.md
```

---

## Cara Menjalankan Firmware ESP32

1. Install Arduino IDE.
2. Install Board ESP32.
3. Install library yang diperlukan.
4. Buka file SmartHomeIoT.ino.
5. Masukkan SSID WiFi dan Password.
6. Upload ke ESP32.

---

## Cara Menjalankan Aplikasi Android

1. Install Android Studio.
2. Buka folder Android.
3. Sync Gradle.
4. Jalankan aplikasi pada emulator atau smartphone Android.

---

## Konfigurasi Firebase

Masukkan file `google-services.json` ke dalam folder:

```
Android/app/
```

Pastikan URL Firebase sesuai dengan project yang digunakan.

---

## Docker

Proyek ini tidak menggunakan Docker karena merupakan sistem IoT berbasis ESP32 dengan Firebase Realtime Database sebagai layanan cloud dan aplikasi Android sebagai antarmuka pengguna.

---

## Penulis

Muhammad Taufiqiy

Program Studi Teknik Informatika

Universitas Bhinneka PGRI

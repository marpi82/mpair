======
mpair
======

Zaawansowana Stacja Monitoringu Jakości Powietrza
==================================================

**mpair** to open-source'owa stacja monitoringu jakości powietrza IoT z obsługą protokołu Matter/Thread, łącznością PoE+ i profesjonalnymi czujnikami.

.. image:: https://img.shields.io/badge/Hardware-CERN--OHL--S--2.0-blue
   :target: LICENSE-hardware.pl.rst
   :alt: Licencja Hardware

.. image:: https://img.shields.io/badge/Software-GPL--3.0-green
   :target: LICENSE-software.pl.rst
   :alt: Licencja Software

.. image:: https://img.shields.io/badge/Dokumentacja-CC--BY--SA--4.0-orange
   :target: LICENSE-docs.pl.rst
   :alt: Licencja Dokumentacji

Funkcje
=======

Funkcje Sprzętowe
-----------------

* **Architektura Dual MCU**
  
  * ESP32-S3-WROOM-1-N16R8 (główny kontroler)
  * ESP32-H2-MINI-1-N4 (łączność Matter/Thread)

* **Łączność**
  
  * Obsługa Matter over Thread
  * Fast Ethernet 100Mbps (LAN8710A)
  * PoE/PoE+ (802.3af/at) z RT5300B-12V lub wtyk DC 12V
  * USB-C do programowania i debugowania

* **Czujniki**
  
  * SPS30 - Czujnik pyłów zawieszonych (PM1.0, PM2.5, PM4.0, PM10)
  * MH-Z14A - Czujnik CO₂ NDIR
  * SHT31 - Temperatura i wilgotność (wewnętrzny)
  * BME280 - Temperatura, wilgotność i ciśnienie atmosferyczne (zewnętrzny)
  * GPS NEO-6 - Lokalizacja i synchronizacja czasu

* **Dodatkowe Funkcje**
  
  * Grzałka PTC (70°C) dla systemu HECA - podgrzewa powietrze, aby zmniejszyć wilgotność względną i zapobiec pomiarowi kropel wody przez czujnik SPS30
  * Wskaźniki LED RGB WS2812
  * Wyświetlacz OLED SSD1309 2.42" (128×64, opcjonalnie dla wersji wewnętrznej)

Funkcje Oprogramowania
-----------------------

* Obsługa protokołu Matter/Thread dla integracji z systemami smart home
* Monitor jakości powietrza w czasie rzeczywistym
* Logowanie i wizualizacja danych
* Aktualizacje firmware OTA
* Interfejs konfiguracyjny webowy
* Wiele protokołów eksportu danych:
  
  * Wsparcie brokera MQTT
  * Endpoint metryk Prometheus
  * Endpoint JSON REST API
  * Publikowanie danych do Luftdaten (sensor.community)
  * Publikowanie danych do madavi.de
  * Publikowanie danych do opensensemap.org

Specyfikacja Techniczna
========================

Zasilanie
---------

* **Wejście:** PoE/PoE+ (802.3af/at), wtyk DC 12V lub USB-C (5V tylko do programowania)
* **Szyny Zasilania:** 12V, 5V, 3.3V (izolowane przetwornice Buck z TX4138)
* **Pobór Mocy:** TBD

Interfejsy Komunikacyjne
-------------------------

* **Ethernet:** 100Mbps przez LAN8710A (RMII)
* **Bezprzewodowy:** Matter over Thread przez ESP32-H2
* **USB:** USB 2.0 Full Speed przez ESP32-S3
* **Inter-MCU:** UART (ESP32-S3 ↔ ESP32-H2)

Zakresy Pomiarowe
-----------------

* **PM:** 0-1000 µg/m³ (PM1.0, PM2.5, PM4.0, PM10)
* **CO₂:** 0-5000 ppm (MH-Z14A)
* **Temperatura:** -40°C do +85°C
* **Wilgotność:** 0-100% RH
* **Ciśnienie:** 300-1100 hPa (BME280)

Struktura Projektu
==================

::

    mpair/
    ├── hardware/
    │   ├── EasyEDA/           # Pliki projektu EasyEDA Pro
    │   ├── gerbers/           # Pliki produkcyjne (Gerber, drill, BOM)
    │   └── schematics/        # Schematy PDF i dokumentacja
    ├── software/
    │   ├── firmware/          # Firmware ESP32 (ESP-IDF / Arduino)
    │   ├── bootloader/        # Własny bootloader (jeśli potrzebny)
    │   └── tests/             # Testy jednostkowe i integracyjne
    └── docs/                  # Dodatkowa dokumentacja

Pierwsze Kroki
==============

Wymagania
---------

* Thread Border Router (np. Smilight SLZB-06M) dla łączności Matter/Thread
* System smart home z obsługą Matter (Home Assistant, Apple Home, Google Home, itp.) - opcjonalnie
* ESP-IDF v5.x lub Arduino-ESP32 v3.x
* EasyEDA Pro (do modyfikacji hardware)

Kompilacja Firmware
-------------------

.. code-block:: bash

    cd software/firmware
    idf.py build
    idf.py flash monitor

Montaż Hardware
---------------

Szczegółowe instrukcje montażu i BOM są dostępne w katalogu ``hardware/``.

Konfiguracja
------------

1. Podłącz urządzenie przez USB, Ethernet lub zasil przez PoE/DC
2. Wejdź do interfejsu webowego pod adresem ``http://mpair.local``
3. Skonfiguruj dane Thread, parametry czujników oraz ustawienia publikacji danych
4. (Opcjonalnie) Sparuj z systemem smart home używając kodu QR Matter
5. Skonfiguruj endpointy eksportu danych (MQTT, Prometheus, Luftdaten, itp.)

Licencje
========

Ten projekt wykorzystuje różne licencje dla poszczególnych komponentów:

Hardware
--------

**CERN Open Hardware Licence Version 2 - Strongly Reciprocal (CERN-OHL-S-2.0)**

Projekty hardware są licencjonowane na zasadach CERN-OHL-S-2.0, co oznacza:

* Możesz swobodnie używać, modyfikować i dystrybuować projekty hardware
* Wszelkie modyfikacje muszą być udostępnione na tej samej licencji
* Musisz udostępnić źródła projektów
* Dozwolone jest użycie komercyjne

Zobacz `LICENSE-hardware.pl.rst <LICENSE-hardware.pl.rst>`_ dla pełnego tekstu licencji.

Software
--------

**GNU General Public License v3.0 (GPL-3.0)**

Oprogramowanie (firmware, narzędzia) jest licencjonowane na zasadach GPL-3.0, co oznacza:

* Możesz swobodnie używać, modyfikować i dystrybuować oprogramowanie
* Wszelkie modyfikacje muszą być udostępnione na tej samej licencji
* Kod źródłowy musi być udostępniony
* Dozwolone jest użycie komercyjne

Zobacz `LICENSE-software.pl.rst <LICENSE-software.pl.rst>`_ dla pełnego tekstu licencji.

Dokumentacja
------------

**Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)**

Cała dokumentacja jest licencjonowana na zasadach CC BY-SA 4.0, co oznacza:

* Możesz swobodnie udostępniać i adaptować dokumentację
* Musisz podać odpowiednie uznanie autorstwa
* Musisz dystrybuować swoje wkłady na tej samej licencji
* Dozwolone jest użycie komercyjne

Zobacz `LICENSE-docs.pl.rst <LICENSE-docs.pl.rst>`_ dla pełnego tekstu licencji.

Współpraca
==========

Wkład w projekt jest mile widziany! Proszę:

1. Zforkuj repozytorium
2. Stwórz gałąź funkcji (``git checkout -b feature/niesamowita-funkcja``)
3. Zatwierdź zmiany (``git commit -m 'Dodaj niesamowitą funkcję'``)
4. Wypchnij do gałęzi (``git push origin feature/niesamowita-funkcja``)
5. Otwórz Pull Request

Upewnij się, że Twój wkład jest zgodny z odpowiednimi licencjami.

Podziękowania
=============

* Inspiracja z NAMF (Nettigo Air Monitor Firmware)
* Referencje projektowe hardware z Olimex ESP32-PoE2
* Obsługa Matter/Thread przez ESP-IDF

Wsparcie
========

* **Zgłaszanie Problemów:** Użyj GitHub Issues dla zgłoszeń błędów i propozycji funkcji
* **Dyskusje:** Użyj GitHub Discussions dla pytań i pomysłów
* **Dokumentacja:** Sprawdź katalog `docs/ <docs/>`_ dla szczegółowych informacji

Plan Rozwoju
============

* ☐ Projekt PCB i prototypowanie
* ☐ Rozwój firmware (ESP32-S3 + ESP32-H2)
* ☐ Implementacja typu urządzenia Matter
* ☐ Integracja i testy z Home Assistant
* ☐ Projekt obudowy (do druku 3D)
* ☐ Certyfikacja (opcjonalnie - Matter, PoE)
* ☐ Wersja produkcyjna

Zastrzeżenia
============

Ten projekt jest dostarczany "as-is" bez jakiejkolwiek gwarancji. Autorzy nie ponoszą odpowiedzialności za jakiekolwiek szkody lub utratę danych wynikające z użycia tego hardware'u lub oprogramowania.

----

**Stworzone z ❤️ dla monitoringu czystego powietrza**

*Wersja: 0.1.0-alpha*

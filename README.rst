======
mpair
======

Advanced Air Quality Monitoring Station
========================================

**mpair** is an open-source IoT air quality monitoring station with support for Matter/Thread protocol, PoE+ connectivity, and professional-grade sensors.

.. image:: https://img.shields.io/badge/Hardware-CERN--OHL--S--2.0-blue
   :target: LICENSE-hardware.rst
   :alt: Hardware License

.. image:: https://img.shields.io/badge/Software-GPL--3.0-green
   :target: LICENSE-software.rst
   :alt: Software License

.. image:: https://img.shields.io/badge/Documentation-CC--BY--SA--4.0-orange
   :target: LICENSE-docs.rst
   :alt: Documentation License

Features
========

Hardware Features
-----------------

* **Dual MCU Architecture**
  
  * ESP32-S3-WROOM-1-N16R8 (main controller)
  * ESP32-H2-MINI-1-N4 (Matter/Thread connectivity)

* **Connectivity**
  
  * Matter over Thread support
  * Fast Ethernet 100Mbps (LAN8710A)
  * PoE/PoE+ (802.3af/at) with RT5300B-12V or 12V DC jack
  * USB-C for programming and debugging

* **Sensors**
  
  * SPS30 - Particulate Matter sensor (PM1.0, PM2.5, PM4.0, PM10)
  * MH-Z14A - NDIR CO₂ sensor
  * SHT31 - Temperature and humidity (indoor)
  * BME280 - Temperature, humidity, and barometric pressure (outdoor)
  * GPS NEO-6 - Location and time synchronization

* **Additional Features**
  
  * PTC heater (70°C) for HECA - heats air to reduce relative humidity and prevent SPS30 from measuring water droplets
  * WS2812 RGB LED indicators
  * SSD1309 2.42" OLED display (128×64, optional for indoor version)

Software Features
-----------------

* Matter/Thread protocol support for smart home integration
* Real-time air quality monitoring
* Data logging and visualization
* OTA firmware updates
* Web-based configuration interface
* Multiple data export protocols:
  
  * MQTT broker support
  * Prometheus metrics endpoint
  * JSON REST API endpoint
  * Data publishing to Luftdaten (sensor.community)
  * Data publishing to madavi.de
  * Data publishing to opensensemap.org

Technical Specifications
========================

Power Supply
------------

* **Input:** PoE/PoE+ (802.3af/at), 12V DC jack, or USB-C (5V for programming only)
* **Power Rails:** 12V, 5V, 3.3V (isolated Buck converters with TX4138)
* **Consumption:** TBD

Communication Interfaces
------------------------

* **Ethernet:** 100Mbps via LAN8710A (RMII)
* **Wireless:** Matter over Thread via ESP32-H2
* **USB:** USB 2.0 Full Speed via ESP32-S3
* **Inter-MCU:** UART (ESP32-S3 ↔ ESP32-H2)

Measurement Ranges
------------------

* **PM:** 0-1000 µg/m³ (PM1.0, PM2.5, PM4.0, PM10)
* **CO₂:** 0-5000 ppm (MH-Z14A)
* **Temperature:** -40°C to +85°C
* **Humidity:** 0-100% RH
* **Pressure:** 300-1100 hPa (BME280)

Project Structure
=================

::

    mpair/
    ├── hardware/
    │   ├── EasyEDA/           # EasyEDA Pro project files
    │   ├── gerbers/           # Manufacturing files (Gerber, drill, BOM)
    │   └── schematics/        # PDF schematics and documentation
    ├── software/
    │   ├── firmware/          # ESP32 firmware (ESP-IDF / Arduino)
    │   ├── bootloader/        # Custom bootloader (if needed)
    │   └── tests/             # Unit and integration tests
    └── docs/                  # Additional documentation

Getting Started
===============

Prerequisites
-------------

* Thread Border Router (e.g., Smilight SLZB-06M) for Matter/Thread connectivity
* Smart home system with Matter support (Home Assistant, Apple Home, Google Home, etc.) - optional
* ESP-IDF v5.x or Arduino-ESP32 v3.x
* EasyEDA Pro (for hardware modifications)

Building Firmware
-----------------

.. code-block:: bash

    cd software/firmware
    idf.py build
    idf.py flash monitor

Hardware Assembly
-----------------

Detailed assembly instructions and BOM are available in the ``hardware/`` directory.

Configuration
-------------

1. Connect the device via USB, Ethernet, or power it with PoE/DC
2. Access the web interface at ``http://mpair.local``
3. Configure Thread credentials, sensor parameters, and data publishing settings
4. (Optional) Pair with your smart home system using Matter QR code
5. Configure data export endpoints (MQTT, Prometheus, Luftdaten, etc.)

Licenses
========

This project uses multiple licenses for different components:

Hardware
--------

**CERN Open Hardware Licence Version 2 - Strongly Reciprocal (CERN-OHL-S-2.0)**

The hardware designs are licensed under CERN-OHL-S-2.0, which means:

* You are free to use, modify, and distribute the hardware designs
* Any modifications must be released under the same license
* You must make design sources available
* Commercial use is allowed

See `LICENSE-hardware.rst <LICENSE-hardware.rst>`_ for full license text.

Software
--------

**GNU General Public License v3.0 (GPL-3.0)**

The software (firmware, utilities) is licensed under GPL-3.0, which means:

* You are free to use, modify, and distribute the software
* Any modifications must be released under the same license
* Source code must be made available
* Commercial use is allowed

See `LICENSE-software.rst <LICENSE-software.rst>`_ for full license text.

Documentation
-------------

**Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)**

All documentation is licensed under CC BY-SA 4.0, which means:

* You are free to share and adapt the documentation
* You must give appropriate credit
* You must distribute your contributions under the same license
* Commercial use is allowed

See `LICENSE-docs.rst <LICENSE-docs.rst>`_ for full license text.

Contributing
============

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch (``git checkout -b feature/amazing-feature``)
3. Commit your changes (``git commit -m 'Add amazing feature'``)
4. Push to the branch (``git push origin feature/amazing-feature``)
5. Open a Pull Request

Please ensure your contributions comply with the respective licenses.

Credits
=======

* Inspired by NAMF (Nettigo Air Monitor Firmware)
* Hardware design references from Olimex ESP32-PoE2
* Matter/Thread support via ESP-IDF

Support
=======

* **Issues:** Use GitHub Issues for bug reports and feature requests
* **Discussions:** Use GitHub Discussions for questions and ideas
* **Documentation:** Check the `docs/ <docs/>`_ directory for detailed information

Roadmap
=======

* ☐ PCB design and prototyping
* ☐ Firmware development (ESP32-S3 + ESP32-H2)
* ☐ Matter device type implementation
* ☐ Home Assistant integration and testing
* ☐ Enclosure design (3D printable)
* ☐ Certification (optional - Matter, PoE)
* ☐ Production-ready version

Disclaimer
==========

This project is provided "as-is" without any warranty. The authors are not responsible for any damage or data loss resulting from the use of this hardware or software.

----

**Made with ❤️ for clean air monitoring**

*Version: 0.1.0-alpha*

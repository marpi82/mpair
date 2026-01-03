====================================
Licencja Oprogramowania - GPL-3.0
====================================

GNU General Public License v3.0
================================

**Projekt:** mpair - Zaawansowana Stacja Monitoringu Jakości Powietrza

**Prawa autorskie:** 2026 kontrybutorzy mpair

Licencja
========

Oprogramowanie (firmware, narzędzia, skrypty) w tym projekcie jest objęte licencją **GNU General Public License version 3.0 (GPL-3.0)**.

Jest to silna licencja copyleft, która zapewnia, że oprogramowanie i wszelkie modyfikacje pozostają wolne i open source.

Podsumowanie
------------

**Możesz:**

* **Używać** - Uruchamiać oprogramowanie do dowolnych celów
* **Studiować** - Badać jak działa oprogramowanie i dostosować je do swoich potrzeb
* **Modyfikować** - Modyfikować oprogramowanie i tworzyć dzieła pochodne
* **Dystrybuować** - Dystrybuować kopie oprogramowania
* **Dzielić się ulepszeniami** - Dzielić się swoimi modyfikacjami ze społecznością

**Pod następującymi warunkami:**

* **Copyleft** - Jeśli dystrybuujesz oprogramowanie lub modyfikacje, musisz licencjonować je na GPL-3.0
* **Kod źródłowy** - Musisz udostępnić kod źródłowy
* **Oznaczenie zmian** - Musisz udokumentować jakie zmiany wprowadziłeś
* **Brak gwarancji** - Oprogramowanie jest dostarczane bez gwarancji
* **Przyznanie praw patentowych** - Kontrybutorzy przyznają Ci prawa patentowe do swoich wkładów

Objęte pliki
============

Ta licencja dotyczy wszystkich plików oprogramowania w katalogu ``software/``, w tym między innymi:

* Kod źródłowy firmware ESP32 (C/C++)
* Skrypty i narzędzia Python
* Skrypty build i pliki konfiguracyjne
* Skrypty Shell
* Dokumentacja oprogramowania i komentarze

Pełny tekst licencji
====================

Kompletny tekst GNU General Public License version 3.0 można znaleźć pod adresem:

https://www.gnu.org/licenses/gpl-3.0.txt

Lub na oficjalnej stronie GNU:

https://www.gnu.org/licenses/gpl-3.0.html

Kluczowe wymagania
==================

Dystrybucja
-----------

Gdy dystrybuujesz oprogramowanie lub zmodyfikowane wersje:

1. **Udostępnij kod źródłowy** - Udostępnij kompletny kod źródłowy
2. **Dołącz licencję** - Dołącz kopię GPL-3.0
3. **Dołącz prawa autorskie** - Zachowaj wszystkie informacje o prawach autorskich
4. **Dokumentuj zmiany** - Określ co zmieniłeś
5. **Użyj tej samej licencji** - Licencjonuj na GPL-3.0

Łączenie z innym kodem
-----------------------

* **Kod GPL-3.0** - Można łączyć swobodnie
* **Kod GPL-2.0** - Można łączyć (upgrade do GPL-3.0)
* **Kod LGPL** - Można łączyć
* **Licencje permisywne** (MIT, BSD, Apache) - Można łączyć (staje się GPL-3.0)
* **Kod własnościowy** - W większości przypadków nie można łączyć

Użycie w sieci
--------------

Jeśli uruchamiasz zmodyfikowane oprogramowanie GPL-3.0 na serwerze, musisz:

* Oferować kod źródłowy użytkownikom, którzy z nim wchodzą w interakcję przez sieć (jeśli używasz AGPL-3.0)
* Uwaga: Standardowe GPL-3.0 tego nie wymaga, ale jest to dobra praktyka

Kompatybilność licencji
========================

GPL-3.0 jest kompatybilna z:

* GPL-2.0-or-later
* LGPL-2.1, LGPL-3.0
* Apache License 2.0
* MIT License, licencjami BSD
* CERN-OHL-S-2.0 (dla połączonych prac hardware/software)

GPL-3.0 NIE jest kompatybilna z:

* GPL-2.0-only (bez "or later")
* Licencjami własnościowymi
* Niektórymi licencjami permisywnymi z klauzulami patentowymi

Atrybucja
=========

Podczas używania lub dystrybuowania tego oprogramowania, proszę o podanie atrybucji:

    **mpair** - Zaawansowana Stacja Monitoringu Jakości Powietrza

    Licencjonowane na zasadach GNU GPL-3.0

    https://github.com/[twoja-nazwa-użytkownika]/mpair

Jak zachować zgodność
======================

Jeśli modyfikujesz i dystrybuujesz to oprogramowanie:

1. **Zachowaj tę licencję** - Dołącz kopię GPL-3.0
2. **Udostępnij źródła** - Udostępnij kompletny kod źródłowy
3. **Dokumentuj zmiany** - Dodaj changelog lub komentarze opisujące modyfikacje
4. **Użyj tej samej licencji** - Licencjonuj swoje dzieło pochodne na GPL-3.0
5. **Bez dodatkowych ograniczeń** - Nie dodawaj warunków ograniczających prawa GPL
6. **Ochrona patentowa** - Przyznaj niezbędne prawa patentowe

Dla usług SaaS / sieciowych
============================

Jeśli uruchamiasz to oprogramowanie jako usługę (np. monitoring jakości powietrza w chmurze):

* Zgodnie ze standardowym GPL-3.0, **nie musisz** udostępniać modyfikacji
* Rozważ użycie AGPL-3.0 dla SaaS, jeśli chcesz wymagać udostępniania źródeł
* Z uprzejmości, rozważ wniesienie ulepszeń z powrotem do projektu

Biblioteki stron trzecich
==========================

To oprogramowanie może używać bibliotek stron trzecich z kompatybilnymi licencjami:

* ESP-IDF - Apache License 2.0 (kompatybilna)
* FreeRTOS - MIT License (kompatybilna)
* Biblioteki MQTT - Różne (sprawdź indywidualne licencje)

Zobacz plik ``software/THIRD_PARTY_LICENSES.md`` dla kompletnej atrybucji.

Odnośniki
=========

* GNU GPL: https://www.gnu.org/licenses/gpl-3.0.html
* GPL FAQ: https://www.gnu.org/licenses/gpl-faq.html
* Zgodność z GPL: https://www.gnu.org/licenses/gpl-howto.html
* Szybki przewodnik: https://www.gnu.org/licenses/quick-guide-gplv3.html

----

**Dla licencji hardware, zobacz:** `LICENSE-hardware.pl.rst <LICENSE-hardware.pl.rst>`_

**Dla licencji dokumentacji, zobacz:** `LICENSE-docs.pl.rst <LICENSE-docs.pl.rst>`_

/****************************************************************************
 * Copyright 2019 D. Breunig
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ****************************************************************************/

/**
* @file adsVerbindung.h
* @author D. Breunig
* @date 22 Mai 2019
* @brief ADS Verbindung
*/

#ifndef ADS_TEST_ADSVERBINDUNG_H
#define ADS_TEST_ADSVERBINDUNG_H

#include "AdsLib.h"

#include <vector>
#include <map>
#include <functional>
#include <mutex>
#include <thread>

class adsVerbindung {

    std::mutex mtx;

    std::string indexVerbindung;

    AmsNetId ziel_NetId;
    std::string ziel_IpV4;
    long port;
    AmsAddr ziel;

    std::map<std::string, std::vector<std::uint8_t>> beobVariablen;
    std::map<std::string, bool> beobVariablen_rufeFunktion;
    std::function<void(const std::string&, const std::string&,
                       const std::vector<uint8_t>)> Aenderungsfunktion_beobVariablen;

    bool beobachte = false;

    std::thread beobachte_thread;

    void beobachten();

public:
    //adsVerbindung(std::vector<std::uint8_t>& netId, std::string& ipV4);

    adsVerbindung(std::string& netId, std::string& ipV4);

    adsVerbindung(std::string& name, std::string& netId, std::string& ipV4);

    void setzeEigeneNetId(std::vector<std::uint8_t>& netId);

    long erstelleRoute();

    long oeffnePort();

    void erstelleZiel();

    long schliesse();

    long leseStatus();

    std::vector<uint8_t> lese(uint32_t indexGroup, uint32_t indexOffset, uint32_t max_length);

    std::vector<uint8_t> leseAnhandName(const std::string& name);

    long schreibe(uint32_t indexGroup, uint32_t indexOffset, const std::vector<uint8_t>& buffer);

    long schreibeAnhandName(const std::string& name, const std::vector<uint8_t>& buffer);

    uint32_t beobachte_pause_usec = 100000;

    void beobachteVariable(const std::string& name, bool aenderungsfunktion_aufrufen);

    void beobachteVariablen(const std::map<std::string, bool>& variablen);

    int initialisieren();

    void start();

    void halt();

    void setzeAenderungsfunktion(std::function<void(const std::string&, const std::string&, const std::vector<uint8_t>)> funktion);
};

#endif //ADS_TEST_ADSVERBINDUNG_H

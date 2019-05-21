//
// Created by dbb on 21.05.19.
//

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
    uint32_t beobachte_pause_usec = 10000;
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

    long schreibe(uint32_t indexGroup, uint32_t indexOffset, std::shared_ptr<uint8_t>& buffer, uint32_t bufferSize);

    void beobachteVariable(const std::string& name, bool aenderungsfunktion_aufrufen);

    void beobachteVariablen(const std::map<std::string, bool>& variablen);

    int initialisieren();

    void start();

    void halt();
    void setzeAenderungsfunktion(std::function<void(const std::string&, const std::string&, const std::vector<uint8_t>)> funktion);
};

#endif //ADS_TEST_ADSVERBINDUNG_H

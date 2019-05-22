#include "adsFunktionen.h"

#include "adsVerbindung.h"
#include <chrono>

void adsVerbindung::beobachten() {
    while (beobachte) {
        mtx.lock();
        for (auto& i : beobVariablen) {
            auto read = leseAnhandName(i.first);
            if (beobVariablen_rufeFunktion.at(i.first) && Aenderungsfunktion_beobVariablen) {
                bool go = (i.second.size() != read.size());

                for (unsigned int l = 0; l < i.second.size() && !go; ++l) go = (i.second.at(l) != read.at(l));

                if (go) Aenderungsfunktion_beobVariablen(indexVerbindung, i.first, read);
            }

            i.second.clear();
            for (auto& j : read) i.second.push_back(j);
        }
        mtx.unlock();

        std::this_thread::sleep_for(std::chrono::microseconds(beobachte_pause_usec));
    }
}
/*
adsVerbindung::adsVerbindung(std::vector<std::uint8_t>& netId, std::string& ipV4) {
    indexVerbindung = "";
    ziel_NetId = AmsNetId{netId[0], netId[1], netId[2], netId[3], netId[4], netId[5]}; //Sortierung?
    ziel_IpV4 = ipV4;
    port = 0;
}
*/
adsVerbindung::adsVerbindung(std::string& netId, std::string& ipV4) {
    indexVerbindung = "";
    ziel_NetId = AmsNetId{netId};
    ziel_IpV4 = ipV4;
    port = 0;
}

adsVerbindung::adsVerbindung(std::string& name, std::string& netId, std::string& ipV4) {
    indexVerbindung = name;
    ziel_NetId = AmsNetId{netId};
    ziel_IpV4 = ipV4;
    port = 0;
}

void adsVerbindung::setzeEigeneNetId(std::vector<std::uint8_t>& netId) {
    AdsSetLocalAddress(AmsNetId{netId[0], netId[1], netId[2], netId[3], netId[4], netId[5]});
}

long adsVerbindung::erstelleRoute() {
    long r = AdsAddRoute(ziel_NetId, ziel_IpV4.c_str());

    return r;
}

long adsVerbindung::oeffnePort() {
    port = AdsPortOpenEx();

    return port;
}

void adsVerbindung::erstelleZiel() {
    ziel = AmsAddr{ziel_NetId, AMSPORT_R0_PLC_TC3};
}

long adsVerbindung::schliesse() {
    long status = AdsPortCloseEx(port);;

    return status;
}

long adsVerbindung::leseStatus() {
    return adsFunktionen::leseStatus(port, ziel);
}

std::vector<uint8_t> adsVerbindung::lese(uint32_t indexGroup, uint32_t indexOffset, uint32_t max_length) {
    const auto r = adsFunktionen::lese(port, ziel, indexGroup, indexOffset, max_length);

    return r;
}

std::vector<uint8_t> adsVerbindung::leseAnhandName(const std::string& name) {
    const auto r = adsFunktionen::leseAnhandName(port, ziel, name);

    return r;
}

long adsVerbindung::schreibe(uint32_t indexGroup, uint32_t indexOffset, std::shared_ptr<uint8_t>& buffer, uint32_t bufferSize) {
    const auto r = adsFunktionen::schreibe(port, ziel, indexGroup, indexOffset, buffer, bufferSize);

    return r;
}

void adsVerbindung::beobachteVariable(const std::string& name, bool aenderungsfunktion_aufrufen) {
    mtx.lock();
    if (!beobVariablen.count(name)) beobVariablen.insert({name, std::vector<uint8_t>()});
    if (!beobVariablen_rufeFunktion.count(name)) beobVariablen_rufeFunktion.insert({name, aenderungsfunktion_aufrufen});
    mtx.unlock();
}

void adsVerbindung::beobachteVariablen(const std::map<std::string, bool>& variablen){
    for(auto& s : variablen) beobachteVariable(s.first, s.second);
}

int adsVerbindung::initialisieren() {
    long r = erstelleRoute();

    if (r) return -1;

    long port = oeffnePort();

    if (!port) return -2;

    erstelleZiel();

    return 0;
}

void adsVerbindung::start() {
    if (beobachte) return;

    beobachte = true;
    beobachte_thread = std::thread(&adsVerbindung::beobachten, this);
}

void adsVerbindung::halt() {
    mtx.lock();
    beobachte = false;
    mtx.unlock();
    beobachte_thread.join();
}

void adsVerbindung::setzeAenderungsfunktion(
        std::function<void(const std::string&, const std::string&, const std::vector<uint8_t>)> funktion) {
    Aenderungsfunktion_beobVariablen = funktion;
}
/**
* @file main.cpp
* @author D. Breunig
* @date 22 Mai 2019
* @brief ADS Verbindung Beispiel
*/

#include "adsVerbindung.h"

#include <iostream>
#include <chrono>

void callbackfunktion(const std::string& instanz, const std::string& var_name, const std::vector<uint8_t>& var_wert) {

    std::cout << instanz << ": " << var_name << " = ";

    size_t s;
    s = 0;

    if (var_name == "MAIN.typSubDInt") {
        s = sizeof(uint64_t);
    } else if (var_name == "MAIN.typSubUSInt") {
        s = sizeof(uint16_t);
    }

    if(s != 0){
        uint8_t ergebnis[s] = {0};

        for(int i = 0; i < var_wert.size() && i < s; ++i) ergebnis[i] = var_wert[i]; //memcpy?

        if (var_name == "MAIN.typSubDInt") {
            std::cout << *(uint64_t*)ergebnis;
        } else if (var_name == "MAIN.typSubUSInt") {
            std::cout << *(uint16_t*)ergebnis;
        }

        std::cout << std::endl;
    }
}

int main() {
    std::string name = "twincat_vm";
    std::string zielIp = "10.3.18.38"; //"172.21.5.156";
    std::string netId = zielIp + ".1.1";

    std::unique_ptr<adsVerbindung> s(new adsVerbindung(name, netId, zielIp));

    s->setzeAenderungsfunktion(callbackfunktion);

    s->beobachteVariablen(std::map<std::string, bool>{
        {"MAIN.typSubDInt", true},
        {"MAIN.typSubUSInt", true}
    });

    s->initialisieren();

    s->start();

    std::this_thread::sleep_for(std::chrono::seconds(100));;

    s->halt();

    s->schliesse();

    return 0;
}


#include <iostream>


#include <zconf.h>

#include "adsVerbindung.h"




void callbackfunktion(const std::string& instanz, const std::string& var_name, const std::vector<uint8_t> var_wert) {

    std::cout << instanz << ": " << var_name << " = ";

    if (var_name == "MAIN.typSubDInt") {
        uint64_t ergebnis = 0;

        for (int j = 0; j < var_wert.size(); ++j) {
            ergebnis += (var_wert[j] << j * 8);
        }

        std::cout << ergebnis;
    } else if (var_name == "MAIN.typSubUSInt") {
        uint16_t ergebnis = 0;

        for (int j = 0; j < var_wert.size(); ++j) {
            ergebnis += (var_wert[j] << j * 8);
        }

        std::cout << ergebnis;
    }

    std::cout << std::endl;
}

int main() {
    std::string name = "twincat_vm";
    std::string zielIp = "10.3.18.38";
    std::string netId = zielIp + ".1.1";

    std::unique_ptr<adsVerbindung> s(new adsVerbindung(name, netId, zielIp));

    s->setzeAenderungsfunktion(callbackfunktion);

    s->beobachteVariablen(std::map<std::string, bool>{
        {"MAIN.typSubDInt", true},
        {"MAIN.typSubUSInt", true}
    });

    s->initialisieren();

    s->start();

    usleep(100000000);

    s->halt();

    s->schliesse();

    return 0;
}
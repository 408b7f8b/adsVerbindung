//
// Created by dbb on 21.05.19.
//

#ifndef ADS_TEST_ADSFUNKTIONEN_H
#define ADS_TEST_ADSFUNKTIONEN_H

#include "AdsLib.h"

#include <vector>
#include <memory>

class adsFunktionen {
public:

    static AdsSymbolEntry holeSymbolInfo(long port, const AmsAddr& server, const std::string& name);

    static uint32_t holeSymbolGroesse(long port, const AmsAddr& server, const std::string& handleName);

    static uint32_t holeHandleName(long port, const AmsAddr& server, const std::string& handleName);

    static long handleFreigeben(long port, const AmsAddr& server, uint32_t handle);

    static long leseStatus(long port, const AmsAddr& server);

    static std::vector<uint8_t> lese(long port, const AmsAddr& server, uint32_t indexGroup, uint32_t indexOffset,
                                     uint32_t max_bytes);

    static std::vector<uint8_t> leseAnhandName(long port, const AmsAddr& server, const std::string& name);

    static long schreibe(long port, const AmsAddr& server, uint32_t indexGroup, uint32_t indexOffset,
                         std::shared_ptr<uint8_t>& buffer, uint32_t bufferSize);
};


#endif //ADS_TEST_ADSFUNKTIONEN_H

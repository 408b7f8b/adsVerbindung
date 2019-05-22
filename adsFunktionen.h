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
* @file adsFunktionen.h
* @author D. Breunig
* @date 22 Mai 2019
* @brief ADS Funktionen
*/

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

    static long schreibe(long port, const AmsAddr& server, const uint32_t indexGroup, const uint32_t indexOffset, const std::vector<uint8_t>& buffer);

    static long schreibeAnhandName(long port, const AmsAddr& server, const std::string& name, const std::vector<uint8_t>& buffer);
};


#endif //ADS_TEST_ADSFUNKTIONEN_H

#include "adsFunktionen.h"

AdsSymbolEntry adsFunktionen::holeSymbolInfo(long port, const AmsAddr& server, const std::string& name) {
    AdsSymbolEntry symbolInfo;
    uint32_t bytesRead;

    const long status = AdsSyncReadWriteReqEx2(port,
                                               &server,
                                               ADSIGRP_SYM_INFOBYNAMEEX,
                                               0,
                                               sizeof(symbolInfo),
                                               &symbolInfo,
                                               name.size(),
                                               name.c_str(),
                                               &bytesRead);

    return symbolInfo;
}

uint32_t adsFunktionen::holeSymbolGroesse(long port, const AmsAddr& server, const std::string& handleName) {
    auto symbolInfo = holeSymbolInfo(port, server, handleName);

    return symbolInfo.size;
}

uint32_t adsFunktionen::holeHandleName(long port, const AmsAddr& server, const std::string& handleName) {
    uint32_t handle = 0;
    const long handleStatus = AdsSyncReadWriteReqEx2(port,
                                                     &server,
                                                     ADSIGRP_SYM_HNDBYNAME,
                                                     0,
                                                     sizeof(handle),
                                                     &handle,
                                                     handleName.size(),
                                                     handleName.c_str(),
                                                     nullptr);
    return handle;
}

long adsFunktionen::handleFreigeben(long port, const AmsAddr& server, uint32_t handle) {
    const long releaseHandle = AdsSyncWriteReqEx(port, &server, ADSIGRP_SYM_RELEASEHND, 0, sizeof(handle), &handle);

    return releaseHandle;
}

long adsFunktionen::leseStatus(long port, const AmsAddr& server) {
    uint16_t adsState;
    uint16_t devState;

    const long status = AdsSyncReadStateReqEx(port, &server, &adsState, &devState);

    return status;
}

std::vector<uint8_t> adsFunktionen::lese(long port, const AmsAddr& server, uint32_t indexGroup, uint32_t indexOffset,
                                 uint32_t max_bytes) {
    uint32_t bytesRead;

    std::shared_ptr<uint8_t> buffer(new uint8_t[max_bytes], std::default_delete<uint8_t[]>());

    const long status = AdsSyncReadReqEx2(port, &server, indexGroup, indexOffset, max_bytes, buffer.get(),
                                          &bytesRead);

    std::vector<uint8_t> r;

    for (int i = 0; i < bytesRead; ++i) r.push_back(buffer.get()[i]);

    return r;
}

std::vector<uint8_t> adsFunktionen::leseAnhandName(long port, const AmsAddr& server, const std::string& name) {
    const uint32_t handle = holeHandleName(port, server, name);
    const uint32_t bufferSize = holeSymbolGroesse(port, server, name);

    const auto r = lese(port, server, ADSIGRP_SYM_VALBYHND, handle, bufferSize);

    handleFreigeben(port, server, handle);

    return r;
}

long adsFunktionen::schreibe(long port, const AmsAddr& server, uint32_t indexGroup, uint32_t indexOffset,
                     std::shared_ptr<uint8_t>& buffer, uint32_t bufferSize) {
    const auto r = AdsSyncWriteReqEx(port, &server, indexGroup, indexOffset, bufferSize, buffer.get());

    return r;
}
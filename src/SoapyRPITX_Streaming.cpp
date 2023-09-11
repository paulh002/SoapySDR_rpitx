/*
 * Copyright 2023 Emiliano Gonzalez (egonzalez . hiperion @ gmail . com))
 * * Project Site: https://github.com/hiperiondev/SoapySDR_rpitx *
 *
 * This is based on other projects:
 *    librpitx (https://github.com/F5OEO/librpitx)
 *        Copyright (C) 2018  Evariste COURJAUD F5OEO
 *    SoapyPlutoSDR (https://github.com/pothosware/SoapyPlutoSDR)
 *
 *    please contact their authors for more information.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 *
 */

#include <memory>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <iterator>
#include <algorithm>
#include <chrono>

#include "SoapyRPITX.hpp"

//TODO: Need to be a power of 2 for maximum efficiency ?
# define DEFAULT_RX_BUFFER_SIZE (1 << 16)

std::vector<std::string> SoapyRPITX::getStreamFormats(const int direction, const size_t channel) const {
    std::vector<std::string> formats;

    formats.push_back(SOAPY_SDR_CS16);
    formats.push_back(SOAPY_SDR_CF32);

    return formats;
}

std::string SoapyRPITX::getNativeStreamFormat(const int direction, const size_t channel, double &fullScale) const {
    if (direction == SOAPY_SDR_TX) {
        // TODO:
    }

    return SOAPY_SDR_CF32;
}

SoapySDR::ArgInfoList SoapyRPITX::getStreamArgsInfo(const int direction, const size_t channel) const {
    // TODO:
    SoapySDR::ArgInfoList streamArgs;

    return streamArgs;
}

bool SoapyRPITX::IsValidRxStreamHandle(SoapySDR::Stream *handle) const {
    return false;
}

bool SoapyRPITX::IsValidTxStreamHandle(SoapySDR::Stream *handle) const {
    if (handle == nullptr) {
        return false;
    }

    //handle is an opaque pointer hiding either rx_stream or tx_streamer:
    //check that the handle matches one of them, consistently with direction:
    if (tx_stream) {
        //test if these handles really belong to us:
        if (reinterpret_cast<tx_streamer*>(handle) == tx_stream.get()) {
            return true;
        }
    }

    return false;
}

SoapySDR::Stream* SoapyRPITX::setupStream(const int direction, const std::string &format, const std::vector<size_t> &channels, const SoapySDR::Kwargs &args) {
    //check the format
    rpitxStreamFormat streamFormat;
    if (format == SOAPY_SDR_CF32) {
        SoapySDR_log(SOAPY_SDR_INFO, "Using format CF32.");
        streamFormat = RPITX_SDR_CF32;
    } else if (format == SOAPY_SDR_CS16) {
        SoapySDR_log(SOAPY_SDR_INFO, "Using format CS16.");
        streamFormat = RPITX_SDR_CS16;
    } else {
        throw std::runtime_error("setupStream invalid format '" + format + "' -- Only CS16 and CF32 are supported by RPITX module.");
    }

    if (direction == SOAPY_SDR_TX) {

        std::lock_guard<rpitx_spin_mutex> lock(tx_device_mutex);

        // TODO:

        this->tx_stream = std::unique_ptr<tx_streamer>(new tx_streamer(streamFormat, channels, args));

        return reinterpret_cast<SoapySDR::Stream*>(this->tx_stream.get());
    }

    return nullptr;
}

void SoapyRPITX::closeStream(SoapySDR::Stream *handle) {
    //scope lock :
    {
        std::lock_guard<rpitx_spin_mutex> lock(tx_device_mutex);

        if (IsValidTxStreamHandle(handle)) {
            this->tx_stream.reset();

            // TODO:
        }
    }
}

size_t SoapyRPITX::getStreamMTU(SoapySDR::Stream *handle) const {
    if (IsValidTxStreamHandle(handle)) {
        return 4096;
    }

    return 0;
}

int SoapyRPITX::activateStream(SoapySDR::Stream *handle, const int flags, const long long timeNs, const size_t numElems) {
    // TODO:
    if (flags & ~SOAPY_SDR_END_BURST)
        return SOAPY_SDR_NOT_SUPPORTED;

    return 0;
}

int SoapyRPITX::deactivateStream(SoapySDR::Stream *handle, const int flags, const long long timeNs) {
    //scope lock :
    {
        std::lock_guard<rpitx_spin_mutex> lock(tx_device_mutex);

        if (IsValidTxStreamHandle(handle)) {
            this->tx_stream->flush();
            return 0;
        }
    }

    return 0;
}

int SoapyRPITX::readStream(SoapySDR::Stream *handle, void *const*buffs, const size_t numElems, int &flags, long long &timeNs, const long timeoutUs) {
    return SOAPY_SDR_NOT_SUPPORTED;
}

int SoapyRPITX::writeStream(SoapySDR::Stream *handle, const void *const*buffs, const size_t numElems, int &flags, const long long timeNs,
        const long timeoutUs) {
    std::lock_guard<rpitx_spin_mutex> lock(tx_device_mutex);

    if (IsValidTxStreamHandle(handle)) {
        return this->tx_stream->send(buffs, numElems, flags, timeNs, timeoutUs);;
    } else {
        return SOAPY_SDR_NOT_SUPPORTED;
    }
}

int SoapyRPITX::readStreamStatus(SoapySDR::Stream *stream, size_t &chanMask, int &flags, long long &timeNs, const long timeoutUs) {
    return SOAPY_SDR_NOT_SUPPORTED;
}

tx_streamer::tx_streamer(const rpitxStreamFormat _format, const std::vector<size_t> &channels, const SoapySDR::Kwargs &args) {

    // TODO:
    direct_copy = has_direct_copy();

    SoapySDR_logf(SOAPY_SDR_INFO, "Has direct TX copy: %d", (int) direct_copy);
}

tx_streamer::~tx_streamer() {
    //TODO:
}

int tx_streamer::send(const void *const*buffs, const size_t numElems, int &flags, const long long timeNs, const long timeoutUs) {
    size_t items = std::min(buf_size - items_in_buf, numElems);

    if (direct_copy && format == RPITX_SDR_CS16) {
        // TODO:
    } else {
        // TODO:
    }

    return items;
}

int tx_streamer::flush() {
    return send_buf();
}

int tx_streamer::send_buf() {
    if (items_in_buf > 0) {
        if (items_in_buf < buf_size) {
            // TODO:
        }

        ssize_t ret = items_in_buf;
        items_in_buf = 0;

        if (ret < 0) {
            return ret;
        }

        return int(ret);
    }

    return 0;
}

bool tx_streamer::has_direct_copy() {
    return 0;
}
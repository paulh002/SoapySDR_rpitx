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

#include <stddef.h>

float Soapy_libRPITX_Frequency = 01e6;
float Soapy_libRPITX_PPM = 0;
int Soapy_libRPITX_SampleRate = 48000;
int Soapy_libRPITX_IQBurst = 4000;

int Soapy_libRPITX_setFrequency(float frequency) {
    Soapy_libRPITX_Frequency = frequency;
    return 0;
}

float Soapy_libRPITX_getFrequency(void) {
    return Soapy_libRPITX_Frequency;
}

int Soapy_libRPITX_setPPM(float ppm) {
    Soapy_libRPITX_PPM = ppm;
    return 0;
}

float Soapy_libRPITX_getPPM(void) {
    return Soapy_libRPITX_PPM;
}

int Soapy_libRPITX_setSampleRate(int samplerate) {
    Soapy_libRPITX_SampleRate = samplerate;
    return 0;
}

int Soapy_libRPITX_getSampleRate(void) {
    return Soapy_libRPITX_SampleRate;
}

int Soapy_libRPITX_setIQBurst(unsigned int iqburst) {
    Soapy_libRPITX_IQBurst = iqburst;
    return 0;
}

unsigned int Soapy_libRPITX_getIQBurst(void) {
    return Soapy_libRPITX_IQBurst;
}

void Soapy_libRPITX_setGainMode(const int direction, const size_t channel, const bool automatic) {

}

int Soapy_libRPITX_getGainMode(const int direction, const size_t channel, const bool automatic) {
    return 0;
}

void Soapy_libRPITX_setGain(const int direction, const size_t channel, const double value) {

}

double Soapy_libRPITX_getGain(void) {
    return 0;
}
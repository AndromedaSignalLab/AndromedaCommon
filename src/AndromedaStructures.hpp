/*
API Structures of AndromedaSignalLab Common
Copyright (C) 2022 Volkan Orhan

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once
#include <string>
#include <sstream>
#include <filesystem>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>

namespace AndromedaSignalLab {
    enum class SamplingFrequency:int {
        Hz8000=8000,
        Hz9600=9600,
        Hz11025=11025,
        Hz12000=12000,
        Hz16000=16000,
        Hz22050=22050,
        Hz24000=24000,
        Hz32000=32000,
        Hz44100=44100,
        Hz48000=48000,
        Hz88200=88200,
        Hz96000=96000,
        Hz192000=192000
    };

    enum class BitDepth:int {
        Bits8 = 8,
        Bits16 = 16,
        Bits24 = 24,
        Bits32 = 32
    };

    enum class ChannelMode:int {
        Mono = 1,
        Stereo = 2,
        Quadraphonic = 4,
        Pentaphonic = 5,
        Surround_5_1 = 6,
        Surround_7_1 = 8
    };

    enum class SampleDataFormat {
        Float32 = 320,
        Int32 = 32,
        Int16 = 16
    };

    struct SoundResolution {
        BitDepth bitDepth = BitDepth::Bits16;
        SamplingFrequency sampleRate = SamplingFrequency::Hz44100;
        ChannelMode channelMode = ChannelMode::Stereo;
        SampleDataFormat sampleDataFormat = SampleDataFormat::Float32;
    };

    enum class WindowFunction :int {
        None = 0,
        HanningWindow = 1,
        HammingWindow = 2,
        BlackmanWindow = 3
    };

    enum class Stage {
        PreAlpha,
        Alpha,
        Beta,
        ReleaseCandidate,
        StableRelease
    };


    enum class AFormat
    {
        FMT_U8, FMT_S8, FMT_U16_LE, FMT_U16_BE, FMT_U16_NE, FMT_S16_LE, FMT_S16_BE, FMT_S16_NE
    };


    struct Version {
        unsigned int major = 0;
        unsigned int minor = 0;
        unsigned int release = 0;
        unsigned int patch = 0;
        Stage stage = Stage::StableRelease;
        unsigned int stageRevision = 0;

        inline std::string prettyString();
        inline std::string technicalString();
    };
}

inline std::string AndromedaSignalLab::Version::technicalString() {
    std::ostringstream version;
    version << major << "." << minor;

    if (release != 0 || patch != 0) {
        version << "." << release;
    }

    if (patch != 0) {
        version << "." << patch;
    }

    switch (stage) {
        case Stage::PreAlpha:
            version << "-pre-alpha";
            break;
        case Stage::Alpha:
            version << "-alpha";
            break;
        case Stage::Beta:
            version << "-beta";
            break;
        case Stage::ReleaseCandidate:
            version << "-rc";
            break;
        case Stage::StableRelease:
            break;
        default:
            break;
    }

    if (stage != Stage::StableRelease && stageRevision != 0)
        version << "." << stageRevision;

    return version.str();
}

inline std::string AndromedaSignalLab::Version::prettyString() {
    std::ostringstream version;
    version << major << "." << minor;

    if (release != 0 || patch != 0) {
        version << "." << release;
    }

    if (patch != 0) {
        version << "." << patch;
    }

    switch (stage) {
        case Stage::PreAlpha:
            version << " Pre-Alpha";
            break;
        case Stage::Alpha:
            version << " Alpha";
            break;
        case Stage::Beta:
            version << " Beta";
            break;
        case Stage::ReleaseCandidate:
            version << " Release Candidate";
            break;
        default:
            break;
    }

    if (stage != Stage::StableRelease && stageRevision != 0)
        version << " " << stageRevision;

    return version.str();
}


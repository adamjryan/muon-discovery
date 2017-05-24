/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef SRC_MAIN_HEADER_GEN_IO_MUONCORE_DISCOVERY_SERVICEDESCRIPTORSER_H_2710748379__H_
#define SRC_MAIN_HEADER_GEN_IO_MUONCORE_DISCOVERY_SERVICEDESCRIPTORSER_H_2710748379__H_


#include <sstream>
#include "boost/any.hpp"
#include "avro/Specific.hh"
#include "avro/Encoder.hh"
#include "avro/Decoder.hh"

struct ServiceDescriptorSer {
    std::string identifier;
    std::vector<std::string > tags;
    std::vector<std::string > codecs;
    std::vector<std::string > connectionUris;
    std::vector<std::string > capabilities;
    ServiceDescriptorSer() :
        identifier(std::string()),
        tags(std::vector<std::string >()),
        codecs(std::vector<std::string >()),
        connectionUris(std::vector<std::string >()),
        capabilities(std::vector<std::string >())
        { }
};

namespace avro {
template<> struct codec_traits<ServiceDescriptorSer> {
    static void encode(Encoder& e, const ServiceDescriptorSer& v) {
        avro::encode(e, v.identifier);
        avro::encode(e, v.tags);
        avro::encode(e, v.codecs);
        avro::encode(e, v.connectionUris);
        avro::encode(e, v.capabilities);
    }
    static void decode(Decoder& d, ServiceDescriptorSer& v) {
        if (avro::ResolvingDecoder *rd =
            dynamic_cast<avro::ResolvingDecoder *>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end(); ++it) {
                switch (*it) {
                case 0:
                    avro::decode(d, v.identifier);
                    break;
                case 1:
                    avro::decode(d, v.tags);
                    break;
                case 2:
                    avro::decode(d, v.codecs);
                    break;
                case 3:
                    avro::decode(d, v.connectionUris);
                    break;
                case 4:
                    avro::decode(d, v.capabilities);
                    break;
                default:
                    break;
                }
            }
        } else {
            avro::decode(d, v.identifier);
            avro::decode(d, v.tags);
            avro::decode(d, v.codecs);
            avro::decode(d, v.connectionUris);
            avro::decode(d, v.capabilities);
        }
    }
};

}
#endif

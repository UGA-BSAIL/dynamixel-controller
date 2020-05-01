// ################################################################################
// Copyright 2020 University of Georgia Bio-Sensing and Instrumentation Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ################################################################################

// Author: Hunter Halloran (Jyumpp)

#ifndef DYNAMIXEL_CONTROLLER_DYNIO_H
#define DYNAMIXEL_CONTROLLER_DYNIO_H

#include <iostream>
#include <nlohmann/json.hpp>
#include "DynamixelSDK/src/DynamixelSDK.h"

typedef const int & c_int;

using string=std::string;
using json=nlohmann::json;

class DynamixelIO {
public:
	explicit DynamixelIO(const string &deviceName = "/dev/ttyUSB0", c_int baudRate = 57600);

	void writeControlTable(c_int protocol, c_int dxlId, c_int value, c_int address, c_int size);

	uint32_t readControlTable(c_int protocol, c_int dxlId, c_int address, c_int size);

private:
	dynamixel::PortHandler *portHandler;
	dynamixel::PacketHandler *packetHandler[2];

	int checkError(c_int protocol, c_int dxlCommResult, const uint8_t &dxlError);
};


#endif //DYNAMIXEL_CONTROLLER_DYNIO_H

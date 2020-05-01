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

#ifndef DYNAMIXEL_CONTROLLER_DYNAMIXEL_H
#define DYNAMIXEL_CONTROLLER_DYNAMIXEL_H

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "DynamixelSDK/src/DynamixelSDK.h"

typedef const int &c_int;

using string=std::string;
using json=nlohmann::json;

namespace dynio {
	class DynamixelMotor;

	typedef std::unique_ptr<DynamixelMotor> dyn_ptr;

	class DynamixelIO {
	public:
		explicit DynamixelIO(const string &deviceName = "/dev/ttyUSB0", c_int baudRate = 57600);

		~DynamixelIO();

		void writeControlTable(c_int protocol, c_int dxlID, c_int value, c_int address, c_int size);

		uint32_t readControlTable(c_int protocol, c_int dxlID, c_int address, c_int size);

		dyn_ptr newMotor(c_int dxlID, const string &jsonFile, int protocol = 1, c_int controlTableProtocol = -1);

		dyn_ptr newAX12(c_int dxlID);

		dyn_ptr newMX12(c_int dxlID);

		dyn_ptr newMX28(c_int dxlID, c_int protocol = 1, c_int controlTableProtocol = -1);

		dyn_ptr newMX64(c_int dxlID, c_int protocol = 1, c_int controlTableProtocol = -1);

		dyn_ptr newMX106(c_int dxlID, c_int protocol = 1, c_int controlTableProtocol = -1);

	private:
		dynamixel::PortHandler *portHandler;
		std::array<dynamixel::PacketHandler *, 2> packetHandler{}{}{};

		int checkError(c_int protocol, c_int dxlCommResult, const uint8_t &dxlError);
	};

	class DynamixelMotor {
	public:
		DynamixelMotor(c_int dxlID, DynamixelIO *dxlIO, const string &jsonFile, c_int protocol = 1,
		               c_int controlTableProtocol = -1);

		void writeControlTable(const string &dataName, c_int value);

		uint32_t readControlTable(const string &dataName);

		void setVelocityMode(c_int goalCurrent = -1);

		void setPositionMode(int minLimit = -1, int maxLimit = -1, c_int goalCurrent = -1);

		void setExtendedPositionMode(c_int goalCurrent = -1);

		void setVelocity(int velocity);

		void setAcceleration(c_int acceleration);

		void setPosition(c_int position);

		void setAngle(const float &angle);

		uint32_t getPosition();

		float getAngle();

		uint32_t getCurrent();

		void torqueEnable();

		void torqueDisable();

	private:
		int CONTROL_TABLE_PROTOCOL, DXL_ID, PROTOCOL, MIN_POSITION, MAX_POSITION, MAX_ANGLE;
		DynamixelIO *DXL_IO;
		json CONTROL_TABLE;
	};

}
#endif //DYNAMIXEL_CONTROLLER_DYNAMIXEL_H

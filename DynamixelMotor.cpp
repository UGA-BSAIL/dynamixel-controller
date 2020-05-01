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

#include "dynio.h"

namespace dynio {
	DynamixelMotor::DynamixelMotor(c_int &dxlID, DynamixelIO *dxlIO, const string &jsonFile,
	                               c_int &protocol, c_int &controlTableProtocol) {
		if (protocol == 1 || controlTableProtocol == -1) {
			CONTROL_TABLE_PROTOCOL = protocol;
		} else CONTROL_TABLE_PROTOCOL = controlTableProtocol;

		std::ifstream jsonFileStream(jsonFile);
		json config;
		jsonFileStream >> config;

		try {
			if (CONTROL_TABLE_PROTOCOL == 1)
				config = config.at("Protocol_1");
			else
				config = config.at("Protocol_2");
			// std::cout << config << std::endl;
			DXL_ID = dxlID;
			DXL_IO = dxlIO;
			PROTOCOL = protocol;
			CONTROL_TABLE = config.at("Control_Table");
			MIN_POSITION = config.at("Values").at("Min_Position").get<int>();
			MAX_POSITION = config.at("Values").at("Max_Position").get<int>();
			MAX_ANGLE = config.at("Values").at("Max_Angle").get<int>();
		} catch (std::exception &e) {
			std::cerr << "Invalid JSON Format with error " << e.what() << std::endl;
		}
	}

	void DynamixelMotor::writeControlTable(const string &dataName, const int &value) {
		DXL_IO->writeControlTable(PROTOCOL, DXL_ID, value, CONTROL_TABLE.at(dataName).get<std::vector<int>>()[0],
		                          CONTROL_TABLE.at(dataName).get<std::vector<int>>()[1]);
	}

	uint32_t DynamixelMotor::readControlTable(const string &dataName) {
		return DXL_IO->readControlTable(PROTOCOL, DXL_ID, CONTROL_TABLE.at(dataName).get<std::vector<int>>()[0],
		                                CONTROL_TABLE.at(dataName).get<std::vector<int>>()[1]);
	}

	void DynamixelMotor::setVelocityMode(const int &goalCurrent) {
		if (CONTROL_TABLE_PROTOCOL == 1) {
			writeControlTable("CW_Angle_Limit", 0);
			writeControlTable("CCW_Angle_Limit", 0);
			if (goalCurrent >= 0)
				writeControlTable("Max_Torque", goalCurrent);
		} else if (CONTROL_TABLE_PROTOCOL == 2) {
			writeControlTable("Operating_Mode", 1);
			if (goalCurrent >= 0)
				writeControlTable("Goal_Current", goalCurrent);
		}
	}

	void DynamixelMotor::setPositionMode(int minLimit, int maxLimit, const int &goalCurrent) {
		if (CONTROL_TABLE_PROTOCOL == 1) {
			if (minLimit < 0 || maxLimit < 0) {
				minLimit = MIN_POSITION;
				maxLimit = MAX_POSITION;
			}
			writeControlTable("CW_Angle_Limit", minLimit);
			writeControlTable("CCW_Angle_Limit", maxLimit);
			if (goalCurrent >= 0)
				writeControlTable("Max_Torque", goalCurrent);
		} else if (CONTROL_TABLE_PROTOCOL == 2) {
			if (goalCurrent >= 0)
				writeControlTable("Goal_Current", goalCurrent);
		}
	}

	void DynamixelMotor::setExtendedPositionMode(const int &goalCurrent) {
		if (CONTROL_TABLE_PROTOCOL == 1) {
			writeControlTable("CW_Angle_Limit", MAX_POSITION);
			writeControlTable("CCW_Angle_Limit", MAX_POSITION);
			if (goalCurrent >= 0)
				writeControlTable("Max_Torque", goalCurrent);
		} else if (CONTROL_TABLE_PROTOCOL == 2) {
			writeControlTable("Operating_Mode", 4);
			if (goalCurrent >= 0)
				writeControlTable("Goal_Current", goalCurrent);
		}
	}

	void DynamixelMotor::setVelocity(int velocity) {
		if (CONTROL_TABLE_PROTOCOL == 1) {
			if (velocity < 0) {
				velocity *= -1;
				velocity += 1024;
			}
			writeControlTable("Moving_Speed", velocity);
		} else if (CONTROL_TABLE_PROTOCOL == 2) {
			if (readControlTable("Operating_Mode") == 1)
				writeControlTable("Goal_Velocity", velocity);
			else
				writeControlTable("Profile_Velocity", velocity);
		}
	}

	void DynamixelMotor::setAcceleration(const int &acceleration) {
		if (CONTROL_TABLE_PROTOCOL == 1)
			writeControlTable("Goal_Acceleration", acceleration);
		else if (CONTROL_TABLE_PROTOCOL == 2)
			writeControlTable("Profile_Acceleration", acceleration);

	}

	void DynamixelMotor::setPosition(const int &position) {
		writeControlTable("Goal_Position", position);
	}

	void DynamixelMotor::setAngle(const float &angle) {
		setPosition((int) ((angle / (float) MAX_ANGLE) * (((float) MAX_POSITION + 1)
		                                                  - (float) MIN_POSITION)) + MIN_POSITION);
	}

	uint32_t DynamixelMotor::getPosition() {
		return readControlTable("Present_Position");
	}

	float DynamixelMotor::getAngle() {
		return ((float) (getPosition() - MIN_POSITION) / (float) ((MAX_POSITION + 1) - MIN_POSITION)) *
		       (float) MAX_ANGLE;
	}

	uint32_t DynamixelMotor::getCurrent() {
		if (CONTROL_TABLE_PROTOCOL == 1) {
			int current = readControlTable("Present_Load");
			if (current < 0)
				return -1;
			if (current > 1023) {
				current -= 1023;
				current *= -1;
			}
			return current;
		} else if (CONTROL_TABLE_PROTOCOL == 2)
			return readControlTable("Present_Current");
		else return -1;
	}

	void DynamixelMotor::torqueEnable() {
		writeControlTable("Torque_Enable", 1);
	}

	void DynamixelMotor::torqueDisable() {
		writeControlTable("Torque_Enable", 0);
	}
}
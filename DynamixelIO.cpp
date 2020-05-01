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
	DynamixelIO::DynamixelIO(const string &deviceName, c_int baudRate) {
		portHandler = dynamixel::PortHandler::getPortHandler(deviceName.c_str());
		packetHandler = {dynamixel::PacketHandler::getPacketHandler(1.0),
		                 dynamixel::PacketHandler::getPacketHandler(2.0)};

		if (!deviceName.empty()) {
			if (!portHandler->openPort()) {
				throw std::runtime_error("PortOpenError");
			}
			if (!portHandler->setBaudRate(baudRate)) {
				throw std::runtime_error("BaudChangeError");
			}
		}
	}

	DynamixelIO::~DynamixelIO() {
		delete portHandler;
		delete packetHandler[0];
		delete packetHandler[1];
	}

	int DynamixelIO::checkError(c_int protocol, c_int dxlCommResult, const uint8_t &dxlError) {
		if (dxlCommResult != COMM_SUCCESS)
			std::cerr << packetHandler[protocol - 1]->getTxRxResult(dxlCommResult) << std::endl;
		else if (dxlError)
			std::cerr << packetHandler[protocol - 1]->getRxPacketError(dxlError) << std::endl;
		return dxlCommResult;
	}

	void DynamixelIO::writeControlTable(const int &protocol, const int &dxlID, const int &value, const int &address,
	                                    const int &size) {
		int dxlCommResult = 0;
		uint8_t dxlError = 0;

		// std::cout << "Write: " << address << " " << size << std::endl;

		if (size == 1)
			dxlCommResult = packetHandler[protocol - 1]->write1ByteTxRx(portHandler, dxlID, address, value, &dxlError);
		else if (size == 2)
			dxlCommResult = packetHandler[protocol - 1]->write2ByteTxRx(portHandler, dxlID, address, value, &dxlError);
		else if (size == 4)
			dxlCommResult = packetHandler[protocol - 1]->write4ByteTxRx(portHandler, dxlID, address, value, &dxlError);

		checkError(protocol, dxlCommResult, dxlError);

	}

	uint32_t DynamixelIO::readControlTable(const int &protocol, const int &dxlID, const int &address, const int &size) {
		int dxlCommResult = 0;
		uint8_t dxlError = 0;
		uint32_t retVal = 0;

		// std::cout << "Read: " <<  address << " " << size << std::endl;

		if (size == 1)
			dxlCommResult = packetHandler[protocol - 1]->read1ByteTxRx(portHandler, dxlID, address,
			                                                           (uint8_t *) &retVal,
			                                                           &dxlError);
		else if (size == 2)
			dxlCommResult = packetHandler[protocol - 1]->read2ByteTxRx(portHandler, dxlID, address,
			                                                           (uint16_t *) &retVal,
			                                                           &dxlError);
		else if (size == 4)
			dxlCommResult = packetHandler[protocol - 1]->read4ByteTxRx(portHandler, dxlID, address,
			                                                           (uint32_t *) &retVal,
			                                                           &dxlError);

		checkError(protocol, dxlCommResult, dxlError);
		return retVal;
	}

	std::unique_ptr<DynamixelMotor> DynamixelIO::newMotor(c_int dxlID, const string &jsonFile, int protocol,
	                                                      c_int controlTableProtocol) {
		return std::unique_ptr<DynamixelMotor>(new DynamixelMotor(dxlID, this,
		                                                          jsonFile, protocol, controlTableProtocol));
	}

	dyn_ptr DynamixelIO::newAX12(const int &dxlID) {
		return std::unique_ptr<DynamixelMotor>(new DynamixelMotor(dxlID, this,
		                                                          "DynamixelJSON/AX12.json"));
	}

	dyn_ptr DynamixelIO::newMX12(const int &dxlID) {
		return std::unique_ptr<DynamixelMotor>(new DynamixelMotor(dxlID, this,
		                                                          "DynamixelJSON/MX12.json"));
	}

	dyn_ptr DynamixelIO::newMX28(const int &dxlID, const int &protocol, const int &controlTableProtocol) {
		return std::unique_ptr<DynamixelMotor>(new DynamixelMotor(dxlID, this,
		                                                          "DynamixelJSON/MX28.json", protocol,
		                                                          controlTableProtocol));
	}

	dyn_ptr DynamixelIO::newMX64(const int &dxlID, const int &protocol, const int &controlTableProtocol) {
		return std::unique_ptr<DynamixelMotor>(new DynamixelMotor(dxlID, this,
		                                                          "DynamixelJSON/MX64.json", protocol,
		                                                          controlTableProtocol));
	}

	dyn_ptr DynamixelIO::newMX106(const int &dxlID, const int &protocol, const int &controlTableProtocol) {
		return std::unique_ptr<DynamixelMotor>(new DynamixelMotor(dxlID, this,
		                                                          "DynamixelJSON/MX106.json", protocol,
		                                                          controlTableProtocol));
	}
}
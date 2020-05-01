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
		packetHandler[0] = dynamixel::PacketHandler::getPacketHandler(1.0);
		packetHandler[1] = dynamixel::PacketHandler::getPacketHandler(2.0);

		if (!portHandler->openPort()) {
			throw std::runtime_error("PortOpenError");
		}
		if (!portHandler->setBaudRate(baudRate)) {
			throw std::runtime_error("BaudChangeError");
		}
	}

	int DynamixelIO::checkError(c_int protocol, c_int dxlCommResult, const uint8_t &dxlError) {
		if (dxlCommResult != COMM_SUCCESS)
			std::cerr << packetHandler[protocol - 1]->getTxRxResult(dxlCommResult) << std::endl;
		else if (dxlError)
			std::cerr << packetHandler[protocol - 1]->getRxPacketError(dxlError) << std::endl;
		return dxlCommResult;
	}

	void DynamixelIO::writeControlTable(const int &protocol, const int &dxlId, const int &value, const int &address,
	                                    const int &size) {
		int dxlCommResult = 0;
		uint8_t dxlError = 0;

		if (size == 1)
			dxlCommResult = packetHandler[protocol - 1]->write1ByteTxRx(portHandler, dxlId, address, value, &dxlError);
		else if (size == 2)
			dxlCommResult = packetHandler[protocol - 1]->write2ByteTxRx(portHandler, dxlId, address, value, &dxlError);
		else if (size == 4)
			dxlCommResult = packetHandler[protocol - 1]->write4ByteTxRx(portHandler, dxlId, address, value, &dxlError);

		checkError(protocol, dxlCommResult, dxlError);
	}

	uint32_t DynamixelIO::readControlTable(const int &protocol, const int &dxlId, const int &address, const int &size) {
		int dxlCommResult = 0;
		uint8_t dxlError = 0;
		uint32_t retVal = 0;

		if (size == 1)
			dxlCommResult = packetHandler[protocol - 1]->read1ByteTxRx(portHandler, dxlId, address, (uint8_t *) &retVal,
			                                                           &dxlError);
		else if (size == 2)
			dxlCommResult = packetHandler[protocol - 1]->read2ByteTxRx(portHandler, dxlId, address,
			                                                           (uint16_t *) &retVal,
			                                                           &dxlError);
		else if (size == 4)
			dxlCommResult = packetHandler[protocol - 1]->read4ByteTxRx(portHandler, dxlId, address,
			                                                           (uint32_t *) &retVal,
			                                                           &dxlError);

		checkError(protocol, dxlCommResult, dxlError);
		return retVal;
	}
}
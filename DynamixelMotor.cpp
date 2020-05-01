//
// Created by Hunter Halloran on 4/30/20.
//

#include <fstream>
#include "dynio.h"

namespace dynio {
	DynamixelMotor::DynamixelMotor(c_int &dxlId, const DynamixelIO &dxlIo, const string &jsonFile,
	                               c_int &protocol, c_int &controlTableProtocol) {
		if (protocol == 1 || controlTableProtocol == -1) {
			CONTROL_TABLE_PROTOCOL = 2;
		} else CONTROL_TABLE_PROTOCOL = controlTableProtocol;

		std::ifstream jsonFileStream(jsonFile);
		json config;
		jsonFileStream >> config;

		if (CONTROL_TABLE_PROTOCOL == 1)
			config = config["Protocol_1"];
		else
			config = config["Protocol_2"];

		DXL_ID = dxlId;
		DXL_IO = dxlIo;
		PROTOCOL = protocol;
		CONTROL_TABLE = config["Control_Table"];
		MIN_POSITION = config["Values"]["Min_Position"];
		MAX_POSITION = config["Values"]["Max_Position"];
		MAX_ANGLE = config["Values"]["Max_Angle"];
	}
}


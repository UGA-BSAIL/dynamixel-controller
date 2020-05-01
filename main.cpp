//
// Created by Hunter Halloran on 4/30/20.
//

#include "dynio.h"

using namespace dynio;



int main() {
	DynamixelIO dxlIO("/dev/tty.USB");
	auto motor = dxlIO.newAX12(1);
	motor->writeControlTable("Torque_Enable", 1);
}

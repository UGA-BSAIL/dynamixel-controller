//
// Created by Hunter Halloran on 4/30/20.
//

#include "dynio.h"

using namespace dynio;



int main() {
	DynamixelIO dxlIO("");
	auto motor = dxlIO.newMX64(1,2);
	motor->writeControlTable("Torque_Enable", 1);
	motor->torqueEnable();
	motor->setVelocityMode();
	motor->setVelocity(200);
}

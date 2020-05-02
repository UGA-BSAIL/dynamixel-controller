//
// Created by Hunter Halloran on 4/30/20.
//

#include "dynio.h"

using namespace dynio;

class test {
public:
	DynamixelIO dxlIO;
	dyn_ptr motor;

	explicit test(const string &device) {
		dxlIO = DynamixelIO(device);
		motor = dxlIO.newAX12(1);
		auto motor2 = dxlIO.newMX28(2);
	}

	void run() {
		motor->torqueEnable();
		motor->getPosition();
	}
};

int main() {
	test a("");
	a.run();

}
################################################################################
# Copyright 2020 Hunter Halloran
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################

from dynamixel_sdk import *
import json
import pkg_resources


class DynamixelIO:
    """Creates communication handler for Dynamixel motors"""

    def __init__(self,
                 device_name='/dev/ttyUSB0',
                 baud_rate=57600):
        if device_name is None:
            return
        self.port_handler = PortHandler(device_name)
        self.packet_handler = [PacketHandler(1), PacketHandler(2)]
        if not self.port_handler.setBaudRate(baud_rate):
            raise (NameError("BaudChangeError"))

        if not self.port_handler.openPort():
            raise (NameError("PortOpenError"))

    def __check_error(self, protocol, dxl_comm_result, dxl_error):
        """Prints when not successful"""
        if dxl_comm_result != COMM_SUCCESS:
            print("%s" % self.packet_handler[protocol - 1].getTxRxResult(dxl_comm_result))
        elif dxl_error != 0:
            print("%s" % self.packet_handler[protocol - 1].getRxPacketError(dxl_error))

    def write_control_table(self, protocol, dxl_id, value, address, size):
        """Writes a specified value to a given address in the control table"""
        dxl_comm_result = 0
        dxl_error = 0
        if size == 1:
            dxl_comm_result, dxl_error = self.packet_handler[protocol - 1].write1ByteTxRx(self.port_handler, dxl_id,
                                                                                          address, value)
        elif size == 2:
            dxl_comm_result, dxl_error = self.packet_handler[protocol - 1].write2ByteTxRx(self.port_handler, dxl_id,
                                                                                          address, value)
        elif size == 4:
            dxl_comm_result, dxl_error = self.packet_handler[protocol - 1].write4ByteTxRx(self.port_handler, dxl_id,
                                                                                          address, value)
        self.__check_error(protocol, dxl_comm_result, dxl_error)

    def read_control_table(self, protocol, dxl_id, address, size):
        """Returns the held value from a given address in the control table"""
        ret_val = 0
        dxl_comm_result = 0
        dxl_error = 0
        if size == 1:
            ret_val, dxl_comm_result, dxl_error = self.packet_handler[protocol - 1].read1ByteTxRx(self.port_handler,
                                                                                                  dxl_id, address)
        elif size == 2:
            ret_val, dxl_comm_result, dxl_error = self.packet_handler[protocol - 1].read2ByteTxRx(self.port_handler,
                                                                                                  dxl_id, address)
        elif size == 4:
            ret_val, dxl_comm_result, dxl_error = self.packet_handler[protocol - 1].read4ByteTxRx(self.port_handler,
                                                                                                  dxl_id, address)
        self.__check_error(protocol, dxl_comm_result, dxl_error)
        return ret_val

    def new_motor(self, dxl_id, json_file, protocol=2, control_table_protocol=None):
        """Returns a new DynamixelMotor object of a given protocol with a given control table"""
        return DynamixelMotor(dxl_id, self, json_file, protocol, control_table_protocol)

    def new_mx_2(self, dxl_id, protocol=2):
        """Returns a new DynamixelMotor object of a given protocol for an MX series"""
        return DynamixelMotor(dxl_id, self,
                              pkg_resources.resource_filename(__name__, "DynamixelJSON/MX_Protocol_2.json"),
                              protocol, 2)

    def new_mx12_1(self, dxl_id):
        """Returns a new DynamixelMotor object for an MX12"""
        return DynamixelMotor(dxl_id, self,
                              pkg_resources.resource_filename(__name__, "DynamixelJSON/MX12_28_Protocol_1.json"))

    def new_mx28_1(self, dxl_id):
        """Returns a new DynamixelMotor object for an MX28"""
        return self.new_mx12_1(dxl_id)

    def new_mx64_1(self, dxl_id):
        """Returns a new DynamixelMotor object for an MX64"""
        return DynamixelMotor(dxl_id, self,
                              pkg_resources.resource_filename(__name__, "DynamixelJSON/MX64_Protocol_1.json"))

    def new_mx106_1(self, dxl_id):
        """Returns a new DynamixelMotor object for an MX106"""
        return DynamixelMotor(dxl_id, self,
                              pkg_resources.resource_filename(__name__, "DynamixelJSON/MX106_Protocol_1.json"))


class DynamixelMotor:
    """Creates the basis of individual motor objects"""

    def __init__(self, dxl_id, dynamixel_io, json_file, protocol=1, control_table_protocol=None):
        if protocol == 1 or control_table_protocol is None:
            control_table_protocol = protocol
        self.CONTROL_TABLE_PROTOCOL = control_table_protocol
        self.dxl_id = dxl_id
        self.dynamixel_io = dynamixel_io
        self.PROTOCOL = protocol
        self.CONTROL_TABLE = json.load(open(json_file))

    def write_control_table(self, data_name, value):
        """Writes a value to a control table area of a specific name"""
        self.dynamixel_io.write_control_table(self.PROTOCOL, self.dxl_id, value, self.CONTROL_TABLE.get(data_name)[0],
                                              self.CONTROL_TABLE.get(data_name)[1])

    def read_control_table(self, data_name):
        """Reads the value from a control table area of a specific name"""
        return self.dynamixel_io.read_control_table(self.PROTOCOL, self.dxl_id, self.CONTROL_TABLE.get(data_name)[0],
                                                    self.CONTROL_TABLE.get(data_name)[1])

    def set_velocity_mode(self):
        """Sets the motor to run in velocity (wheel) mode"""
        if self.CONTROL_TABLE_PROTOCOL == 1:
            self.write_control_table("CW_Angle_Limit", 0)
            self.write_control_table("CCW_Angle_Limit", 0)
        elif self.CONTROL_TABLE_PROTOCOL == 2:
            self.write_control_table("Operating_Mode", 1)

    def set_position_mode(self, min_limit=None, max_limit=None, goal_current=None):
        """Sets the motor to run in position (joint) mode"""
        if self.CONTROL_TABLE_PROTOCOL == 1:
            if min_limit is None or max_limit is None:
                min_limit = 0
                max_limit = 4095
            self.write_control_table("CW_Angle_Limit", min_limit)
            self.write_control_table("CCW_Angle_Limit", max_limit)
            if goal_current is not None:
                self.write_control_table("Max_Torque", goal_current)
        elif self.CONTROL_TABLE_PROTOCOL == 2:
            self.write_control_table("Operating_Mode", 3)
            if min_limit is not None:
                self.write_control_table("Min_Position_Limit", min_limit)
            if max_limit is not None:
                self.write_control_table("Max_Position_Limit", max_limit)
            if goal_current is not None:
                self.write_control_table("Goal_Current", goal_current)

    def set_extended_position_mode(self, goal_current=None):
        """Sets the motor to run in extended position (multi-turn) mode"""
        if self.CONTROL_TABLE_PROTOCOL == 1:
            self.write_control_table("CW_Angle_Limit", 4095)
            self.write_control_table("CCW_Angle_Limit", 4095)
            if goal_current is not None:
                self.write_control_table("Max_Torque", goal_current)
        elif self.CONTROL_TABLE_PROTOCOL == 2:
            self.write_control_table("Operating_Mode", 4)
            if goal_current is not None:
                self.write_control_table("Goal_Current", goal_current)

    def set_velocity(self, velocity):
        """Sets the goal velocity of the motor"""
        if self.CONTROL_TABLE_PROTOCOL == 1:
            if velocity < 0:
                velocity = abs(velocity)
                velocity += 1024
            self.write_control_table("Moving_Speed", velocity)
        elif self.CONTROL_TABLE_PROTOCOL == 2:
            if self.read_control_table("Operating_Mode") == 1:
                self.write_control_table("Goal_Velocity", velocity)
            else:
                self.write_control_table("Profile_Velocity", velocity)

    def set_acceleration(self, acceleration):
        """Sets the goal acceleration of the motor"""
        if self.CONTROL_TABLE_PROTOCOL == 1:
            self.write_control_table("Goal_Acceleration", acceleration)
        elif self.CONTROL_TABLE_PROTOCOL == 2:
            self.write_control_table("Profile_Acceleration", acceleration)

    def set_position(self, position):
        """Sets the goal position of the motor"""
        self.write_control_table("Goal_Position", position)

    def get_position(self):
        """Returns the motor position"""
        return self.read_control_table("Present_Position")

    def torque_enable(self):
        """Enables motor torque"""
        self.write_control_table("Torque_Enable", 1)

    def torque_disable(self):
        """Disables motor torque"""
        self.write_control_table("Torque_Enable", 0)

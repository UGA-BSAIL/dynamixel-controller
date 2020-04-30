
# dynio


# dynio.dynamixel_controller


## DynamixelIO
```python
DynamixelIO(self, device_name='/dev/ttyUSB0', baud_rate=57600)
```
Creates communication handler for Dynamixel motors

### write_control_table
```python
DynamixelIO.write_control_table(protocol, dxl_id, value, address, size)
```
Writes a specified value to a given address in the control table

### read_control_table
```python
DynamixelIO.read_control_table(protocol, dxl_id, address, size)
```
Returns the held value from a given address in the control table

### new_motor
```python
DynamixelIO.new_motor(dxl_id,
                      json_file,
                      protocol=2,
                      control_table_protocol=None)
```
Returns a new DynamixelMotor object of a given protocol with a given control table

### new_ax12
```python
DynamixelIO.new_ax12(dxl_id)
```
Returns a new DynamixelMotor object for an AX12

### new_mx12
```python
DynamixelIO.new_mx12(dxl_id)
```
Returns a new DynamixelMotor object for an MX12

### new_mx28
```python
DynamixelIO.new_mx28(dxl_id, protocol=1, control_table_protocol=None)
```
Returns a new DynamixelMotor object for an MX28

### new_mx64
```python
DynamixelIO.new_mx64(dxl_id, protocol=1, control_table_protocol=None)
```
Returns a new DynamixelMotor object for an MX64

### new_mx106
```python
DynamixelIO.new_mx106(dxl_id, protocol=1, control_table_protocol=None)
```
Returns a new DynamixelMotor object for an MX106

### new_ax12_1
```python
DynamixelIO.new_ax12_1(*args, **kwargs)
```
Returns a new DynamixelMotor object for an AX12

.. deprecated:: 0.8
   This will be removed in 1.0. Use new_ax12() instead

### new_mx_2
```python
DynamixelIO.new_mx_2(*args, **kwargs)
```
Returns a new DynamixelMotor object of a given protocol for an MX series

.. deprecated:: 0.8
   This will be removed in 1.0. Use the specific new motor function instead

### new_mx12_1
```python
DynamixelIO.new_mx12_1(*args, **kwargs)
```
Returns a new DynamixelMotor object for an MX12

.. deprecated:: 0.8
   This will be removed in 1.0. Use new_mx12() instead

### new_mx28_1
```python
DynamixelIO.new_mx28_1(*args, **kwargs)
```
Returns a new DynamixelMotor object for an MX28

.. deprecated:: 0.8
   This will be removed in 1.0. Use new_mx28() instead

### new_mx64_1
```python
DynamixelIO.new_mx64_1(*args, **kwargs)
```
Returns a new DynamixelMotor object for an MX64

.. deprecated:: 0.8
   This will be removed in 1.0. Use new_mx64() instead

### new_mx106_1
```python
DynamixelIO.new_mx106_1(*args, **kwargs)
```
Returns a new DynamixelMotor object for an MX106

.. deprecated:: 0.8
   This will be removed in 1.0. Use new_mx106() instead

## DynamixelMotor
```python
DynamixelMotor(self,
               dxl_id,
               dxl_io,
               json_file,
               protocol=1,
               control_table_protocol=None)
```
Creates the basis of individual motor objects

### write_control_table
```python
DynamixelMotor.write_control_table(data_name, value)
```
Writes a value to a control table area of a specific name

### read_control_table
```python
DynamixelMotor.read_control_table(data_name)
```
Reads the value from a control table area of a specific name

### set_velocity_mode
```python
DynamixelMotor.set_velocity_mode(goal_current=None)
```
Sets the motor to run in velocity (wheel) mode and sets the goal current if provided

### set_position_mode
```python
DynamixelMotor.set_position_mode(min_limit=None,
                                 max_limit=None,
                                 goal_current=None)
```
Sets the motor to run in position (joint) mode and sets the goal current if provided.
If position limits are not specified, the full range of motion is used instead

### set_extended_position_mode
```python
DynamixelMotor.set_extended_position_mode(goal_current=None)
```
Sets the motor to run in extended position (multi-turn) mode

### set_velocity
```python
DynamixelMotor.set_velocity(velocity)
```
Sets the goal velocity of the motor

### set_acceleration
```python
DynamixelMotor.set_acceleration(acceleration)
```
Sets the goal acceleration of the motor

### set_position
```python
DynamixelMotor.set_position(position)
```
Sets the goal position of the motor

### set_angle
```python
DynamixelMotor.set_angle(angle)
```
Sets the goal position of the motor with a given angle in degrees

### get_position
```python
DynamixelMotor.get_position()
```
Returns the motor position

### get_angle
```python
DynamixelMotor.get_angle()
```
Returns the motor position as an angle in degrees

### get_current
```python
DynamixelMotor.get_current()
```
Returns the current motor load

### torque_enable
```python
DynamixelMotor.torque_enable()
```
Enables motor torque

### torque_disable
```python
DynamixelMotor.torque_disable()
```
Disables motor torque

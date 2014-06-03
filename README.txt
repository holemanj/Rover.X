A personal project to develop code for an autonomous rover built on
the Dagu Rover 5 chassis (http://www.robotshop.com/en/dagu-rover-5-2wd-tracked-chassis.html).

Motor control is managed via a motor controller board
(http://www.robotshop.com/en/dagu-4-channel-brushed-dc-motor-controller.html).

Currently, I am controlling the system with a Microchip PIC18F45K20, which comes
on the Microchip PICKit 44-pin Demo Board. The motor speed is controlled by the
PWM outputs, fed through the motor controller board. One of the benefits of this
controller is that it can be configured to leave a full 8-bit wide parallel
available for use, as well as the normal serial communication.

Eventually, this firmware will consist of a "consumer" process that will ingest
arbitrary control codes (either from a user or from decision making routines
on the controller itself).

The idea is to "layer" the code thus:
 - "low level" routines: these provide the outputs to the PWM outputs, read from
wheel pulse sensors, etc

 - a "rover geometry" layer that encapsulates vehicle parameters that will be used
to transform desired motion to appropriate PWM outputs (possibly using sensor
data as inputs)

 - a "control" layer that provides an interface for other applications (RF control,
AI driver, etc).
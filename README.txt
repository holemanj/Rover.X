A personal project to develop code for an autonomous rover built on
the Dagu Rover 5 chassis (http://http://www.dagurobot.com/Robot_Chassis/Rover-5-Chassis).

Motor control is managed via a motor controller board
(http://http://www.dagurobot.com/Robot_Controller/Rover5_tank_motor_driver_board).

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

 - a "control" layer that provides an interface for other applications.  Controls
will have three basic forms:
    1) "Finite step". "Travel x distance at y speed". The system will attempt,
as much as possible to maintain the required speed. The only sensor required for
this is a way to determine distance traveled (this can be done by a rotation counter
sensor mounted on the motors), and a way to measure time intervals (to obtain a
speed).  When the instruction is complete, the rover will stop and remain in the
stopped state.
    2) "Finite duration". "Travel x speed for y amount of time". The system will
attempt to travel at the required speed until the duration has expired.  This will
require an additional timer beyond that used by finite step instructions in order
to measure the duration.  Since this is most likely to be used for "macro scale"
motions, it can be a coarse-precision timer capable of longer intervals. Like the
finite step instructions, when the duration has expired, the rover still stop.
    3) "Open ended" instructions: "Travel x speed".  These will set (and attempt
to maintain) a state for the rover, which will persist until a new instruction arrives
to replace it.  This will require input buffering, with some sort of interrupt
structure to trigger when a new instruction has arrived.

*Notes: The buffer for the open ended instruction could potentially be used to
"queue up" finite step instructions.  Also, the open-ended instructions have the
same form as the finite duration except that there is no specified duration, and
thus will not stop until a new instruction arrives.  It might be possible to
characterize the difference between types 2 and 3 by what happens when a new
instruction arrives: type 3 will change its behavior immediately to that of the
new instruction; type 2 will only change after its duration has expired.

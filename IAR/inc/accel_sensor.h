#ifndef __ACCEL_SENSOR_H__
#define __ACCEL_SENSOR_H__

#pragma diag_suppress=Ta035

#pragma swi_number=0x0060
__swi __arm int accel_sensor_activate();

#pragma swi_number=0x0061
__swi __arm int accel_sensor_is_active();

#pragma swi_number=0x0062
__swi __arm int accel_sensor_position(short *x, short *y, short *z);

#pragma swi_number=0x0063
__swi __arm int accel_sensor_state(short x, short y, short z);


#endif // __ACCEL_SENSOR_H__


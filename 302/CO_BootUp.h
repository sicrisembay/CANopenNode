#ifndef CO_BOOTUP_H
#define CO_BOOTUP_H

#include "301/CO_NMT_Heartbeat.h"

typedef enum {
    CO_BOOTUP_NO_ERROR = 0,
    CO_BOOTUP_ERROR_A, /* The slave no longer exists in the Network list */
    CO_BOOTUP_ERROR_B, /* No response on access to Actual Device Type (object
                        * 1000h) received*/
    CO_BOOTUP_ERROR_C, /* Actual Device Type (object 1000h) of the slave node
                        * did not match with the expected
                        * DeviceTypeIdentification in object 1F84h */
    CO_BOOTUP_ERROR_D, /* Actual Vendor ID (object 1018h) of the slave node did
                        * not match with the expected Vendor ID in object 1F85h
                        */
    CO_BOOTUP_ERROR_E, /* Slave node did not respond with its state during Check
                        * node state -process. Slave is a heartbeat producer */
    CO_BOOTUP_ERROR_F, /* Slave node did not respond with its state during Check
                        * node state -process. Slave is a Node Guard slave (NMT
                        * slave) */
    CO_BOOTUP_ERROR_G, /* It was requested to verify the application software
                        * version, but the expected version date and time values
                        * were not configured in objects 1F53h and 1F54h
                        * respectively */
    CO_BOOTUP_ERROR_H, /* Actual application software version Date or Time
                        * (object 1F52h) did not match with the expected date
                        * and time values in objects 1F53h and 1F54h
                        * respectively. Automatic software update was not
                        * allowed */
    CO_BOOTUP_ERROR_I, /* Actual application software version Date or Time
                        * (object 1027h) did not match with the expected date
                        * and time values in objects 1F53h and 1F54h
                        * respectively and automatic software update failed */
    CO_BOOTUP_ERROR_J, /* Automatic configuration download failed */
    CO_BOOTUP_ERROR_K, /* The slave node did not send its heartbeat message
                        * during Start Error Control Service although it was
                        * reported to be a heartbeat producer (Note! This error
                        * situation is illustrated in Figure 11 in chapter 5.3)
                        */
    CO_BOOTUP_ERROR_L, /* Slave was initially operational. (CANopen manager may
                        * resume operation with other nodes) */
    CO_BOOTUP_ERROR_M, /* Actual ProductCode (object 1018h) of the slave node
                        * did not match with the expected Product Code in object
                        * 1F86h */
    CO_BOOTUP_ERROR_N, /* Actual RevisionNumber (object 1018h) of the slave node
                        * did not match with the expected RevisionNumber in
                        * object 1F87h */
    CO_BOOTUP_ERROR_O, /* Actual SerialNumber (object 1018h) of the slave node
                        * did not match with the expected SerialNumber in object
                        * 1F88h */

    NBR_CO_BOOTUP_ERROR
} CO_BOOTUP_ERROR_t;

typedef struct {
    CO_NMT_t *nmt;
} CO_BOOT_t;

#endif /* CO_BOOTUP_H */
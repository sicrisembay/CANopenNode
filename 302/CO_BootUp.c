#include "302/CO_BootUp.h"

static void CO_Boot_enter_operational(CO_BOOT_t *boot)
{
    (void)boot; // unused
}
static void CO_Boot_enter_slave_mode(CO_BOOT_t *boot)
{
    (void)boot; // unused
}

static void CO_Boot_send_nmt_start(CO_BOOT_t *boot, uint8_t nodeId) {}

static CO_BOOTUP_ERROR_t CO_Boot_start_error_control_service(CO_BOOT_t *boot)
{
    return CO_BOOTUP_NO_ERROR;
}

static CO_BOOTUP_ERROR_t CO_Boot_check_configuration(CO_BOOT_t *boot)
{
    return CO_BOOTUP_NO_ERROR;
}

static CO_BOOTUP_ERROR_t CO_Boot_slave_process(CO_BOOT_t *boot)
{
    (void)boot;

    /* Is the slave node ID still in the network list? */
    if (1) { // (OD_1F81.bit0)
        /* No */
        return CO_BOOTUP_ERROR_A;
    } else {
        /* Yes */

        if (1) { // (OD_1F84 != 0)
            /* Request for slave device type (Slave_1000) */
            /// read_SDO(0x1000, 0)
            if (1) {
                /* No Response Received */
                return CO_BOOTUP_ERROR_B;
            }
            /* Is slave identity OK */
            if (1) { // (OD_1F84 != Slave_1000)
                return CO_BOOTUP_ERROR_C;
            }
        }

        if (1) { // (OD_1F85 != 0)
            /* Request for slave Vendor Identifiaiton (Slave_1018_01) */
            /// read_SDO(0x1018, 1)
            if (1) { // (OD_1F85 != Slave_1018_01)
                return CO_BOOTUP_ERROR_D;
            }
        }

        if (1) { // (OD_1F86 != 0)
            /* Request for slave Product Identification (Slave_1018_02) */
            /// read_SDO(0x1018, 2)
            if (1) { // (OD_1F86 != Slave_1018_02)
                return CO_BOOTUP_ERROR_M;
            }
        }

        if (1) { // (OD_1F87 != 0)
            /* Request for slave Revision Number (Slave_1018_03) */
            /// read_SDO(1018, 3)
            if (1) { // (OD_1F87 != Slave_1018_03)
                return CO_BOOTUP_ERROR_N;
            }
        }

        if (1) { // (OD_1F88 != 0)
            /* Request for slave Serial Number (Slave_1018_04) */
            /// read_SDO(1018, 4)
            if (1) { // (OD_1F88 != Slave_1018_04)
                return CO_BOOTUP_ERROR_O;
            }
        }
    }

    /* Figure 8 of DSP-302 */
    /* Check Configuration */
    if (CO_BOOTUP_NO_ERROR != CO_Boot_check_configuration(boot)) {
        return CO_BOOTUP_ERROR_J;
    }
    /* Start Error Control Service */
    if (CO_BOOTUP_NO_ERROR != CO_Boot_start_error_control_service(boot)) {
        return CO_BOOTUP_ERROR_K;
    }

    if (1) { // (OD_1F80.bit3 == 0)
        /* Allowed to start the nodes */

        /* Start nodes individually */
        if (1) { // (OD_1F80.bit1 == 0)
            /* Yes */
            uint8_t nodeId = 0x7F; /// nodeId of slave
            CO_Boot_send_nmt_start(boot, nodeId);
        } else {
            /* No */
            if (1) {
                /* My state is OPERATIONAL */
                uint8_t nodeId = 0x7F; /// nodeId of slave
                CO_Boot_send_nmt_start(boot, nodeId);
            }
        }
    }

    return CO_BOOTUP_NO_ERROR;
}

void CO_Boot_process(CO_BOOT_t *boot)
{
    /* Entry (Normal Operation) */

    /* Am I configured as NMT Master? */
    if (1) { // (OD_1F80.bit0 == 1)

        /* Yes, I am configured as NMT Master */

        /* Flying Master Process */
        if (1) { // (OD_1F80.bit5 == 1)
            /* Execute Flying Master Process */

            /* Result of Flying Master Process */
            if (1) {
                /* Won */

                /* LSS required? */
                if (1) {
                    /* Yes. Execute LSS Master */
                }

                /* Keep alive bit of node set? */
                if (1) { // (OD_1F81.bit4 == 1)
                    /* Master must not send NMT Reset Communication to this
                     * slave node if this slave node is in operational state */

                } else {
                    /* Slave node may be reset with NMT Reset Communication
                     * independent of its state */
                }

                /* Start Boot Slave Process? */
                if (1) { // (OD_1F81.bit2 == 1)
                    /* Yes.
                     * Execute Boot Slave Process (see Figure 3 of DSP302)
                     */

                    /* Start Parallel Process Boot Slave */
                    CO_BOOTUP_ERROR_t bootSlaveErr =
                        CO_Boot_slave_process(boot);

                    /* Received successful boot or time has elapsed */
                    if (1) /* Done*/ {
                        /* End of Process Start Boot Slave */
                    }
                }

                /* Has all mandaotry slaves booted? */
                if (1) { // (OD_1F81.bit0 == 1) && (OD_1F81.bit3 == 1)
                    /* If mandatory slaves has not booted yet, Halt network
                     * boot-up procedure */
                }

                /* Enter myself operational? */
                if (1) { // (OD_1F80.bit2 == 0)
                    /* Yes, automatically enter to operational */
                    CO_Boot_enter_operational(boot);
                } else {
                    /* No. Indefinitely wait until "Enter operational" is
                     * received from Application */
                }

                if (1) { // (OD_1F80.bit3 == 0)
                    /* Allowed to start up the slaves */

                    if (1) { // (OD_1F80.bit1 == 1)
                        /* Start ALL slave nodes */

                    } else {
                        /* Start only explicitly assigned slaves */
                    }
                }

                /* Done with boot-up procedure */

            } else {
                /* Lost */
                CO_Boot_enter_slave_mode(boot);
            }
        } else {
            /* Do not participate in Flying Master Process */
            /// ???
        }
    } else {
        /* No, I am not configured as NMT Master */

        /* Auto-Start? */
        if (1) { // (OD_1F80.bit2 == 0)
            /* Enter myself automatically operational */
            CO_Boot_enter_operational(boot);
        }

        /* Enter Slave Mode */
        CO_Boot_enter_slave_mode(boot);
    }
}
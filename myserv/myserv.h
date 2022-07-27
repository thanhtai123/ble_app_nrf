#ifndef _MYSERV_H_
#define _MYSERV_H_

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define BLE_MSV_DEF(_name)
//static ble_msv_t _name;                                                                             
// NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 
//                      BLE_LBS_BLE_OBSERVER_PRIO,                                                     
//                      ble_lbs_on_ble_evt, &_name)


#define MSV_UUID_BASE                                       \
    {                                                      \
        0x4f, 0x3a, 0x15, 0x97, 0x99, 0x86, 0x10, 0xa9,    \
            0x5c ,0x40 ,0x91, 0xc4, 0x00, 0x00, 0x28, 0xfb \
    }
#define MSV_UUID_SERVICE 0x0000
#define MSV_UUID_CHARACT 0x2a37
#define MSV_UUID_DESCRIP 0x2902
#define MSV_CONN_STAT_DISC      0
#define MSV_CONN_STAT_CONN      1
#define MSV_CONN_STAT_SER_DISC  2
#define MSV_CONN_STAT_CLI_DISC  3


// Forward declaration of the ble_lbs_t type.
typedef struct ble_msv_s ble_msv_t;
//typedef void (*ble_msv_handler_t) (uint16_t conn_handle, ble_msv_t * p_msv, uint8_t new_state);


struct ble_msv_s
{
    uint16_t service_handle;                       /**< Handle of LED Button Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t myserv_char_handles;  /**< Handles related to the Button Characteristic. */
    uint8_t uuid_type;                             /**< UUID type for the LED Button Service. */
    uint8_t conn_stat;
};

uint32_t ble_myserv_init(ble_msv_t * p_msv);

//uint32_t ble_msv_on_button_change(uint16_t conn_handle, ble_msv_t * p_lbs, uint8_t button_state);

//void ble_msv_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);
#ifdef __cplusplus
}
#endif
#endif
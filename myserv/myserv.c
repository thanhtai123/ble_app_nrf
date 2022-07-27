#include "sdk_common.h"
#include "myserv.h"
#include "ble_srv_common.h"


uint32_t ble_myserv_init(ble_msv_t * p_msv)
{
    uint32_t              err_code;
    ble_uuid_t            ble_uuid;

    //register vendor UUID 128 bit base
    ble_uuid128_t base_uuid = {MSV_UUID_BASE};
    err_code = sd_ble_uuid_vs_add(&base_uuid, &p_msv->uuid_type);
    VERIFY_SUCCESS(err_code);

    //add service
    /**
     * @todo:
     * add 1 service
     * 16-bit UUID = 0x0000
    */
    ble_uuid.uuid = MSV_UUID_SERVICE;
    ble_uuid.type = p_msv->uuid_type;
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_msv->service_handle);
    VERIFY_SUCCESS(err_code);
    //add characteristic
    /**
     * @todo:
     * add 1 characteristic
     * UUID = 0x2a37
     * properties: Read, Write, Notify, WriteNoResponse. 
     * permission: Read, Write.
    */
    ble_add_char_params_t char_params;
    memset(&char_params, 0, sizeof(char_params));
    char_params.uuid = MSV_UUID_CHARACT;
    char_params.uuid_type = p_msv->uuid_type;
    char_params.init_len = 1;
    char_params.max_len = 1;
    char_params.read_access = SEC_OPEN;
    char_params.write_access =  SEC_OPEN;
    char_params.char_props.read = 1;
    char_params.char_props.write = 1;
    char_params.char_props.write_wo_resp = 1;
    char_params.char_props.notify = 1;
    char_params.cccd_write_access = SEC_OPEN;
    err_code = characteristic_add(p_msv->service_handle,
                                  &char_params,
                                  &p_msv->myserv_char_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    //add descriptor
    /**
     * UUID=0x2902
     * permission: Read, Write
    */
    ble_add_descr_params_t descr_params;
    memset(&descr_params, 0, sizeof(descr_params));
    descr_params.init_len = 1;
    descr_params.max_len = 1;
    descr_params.uuid = MSV_UUID_DESCRIP;
    descr_params.uuid_type = p_msv->uuid_type;
    descr_params.read_access = SEC_OPEN;
    descr_params.write_access = SEC_OPEN;
    return descriptor_add(p_msv->myserv_char_handles.value_handle,
                          &descr_params,
                          &p_msv->myserv_char_handles.user_desc_handle);
}

/******************************************************
*
*
*
*
*       DO NOT FIX THIS FILE
*
*
*
*
*******************************************************/

#ifndef GADGET_H__
#define GADGET_H__
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "microbot.h"

#define FIRMWARE_VERSION_MAJOR 0
#define FIRMWARE_VERSION_MINOR 1
#define FIRMWARE_BUILD_NUMBER 0
#define MODEL_NUMBER 2
#define REQUEST_CNT 2
#define EVENT_CNT 1

static char MIB_PRODUCT_NAME[PRODUCT_NAME_LEN]  = "mibio";  // max 12

#pragma pack(push,1)


typedef enum
{ 
  MIB_EP_SET_PIN = 0,
  MIB_EP_CLEAR_PIN = 1,
} request_ids;


typedef struct set_pin_t set_pin_t;
struct set_pin_t
{ 
  uint8_t pin_number;
};

typedef struct set_pin_return_t set_pin_return_t;
struct set_pin_return_t
{ 
  uint8_t result;
};
static set_pin_return_t* set_pin_return_size;

typedef struct clear_pin_t clear_pin_t;
struct clear_pin_t
{ 
  uint8_t pin_number;
};

typedef struct clear_pin_return_t clear_pin_return_t;
struct clear_pin_return_t
{ 
  uint8_t result;
};
static clear_pin_return_t* clear_pin_return_size;



typedef enum
{ 
  MIB_EVT_PIN_INTERRUPT = 0,
} event_ids;

typedef struct pin_interrupt_t pin_interrupt_t;
struct pin_interrupt_t
{ 
  uint8_t pin_number;
  uint8_t pin_state;
};


#pragma pack(pop)


void set_pin(ep_hnd* _hnd, set_pin_t* data_t);
void clear_pin(ep_hnd* _hnd, clear_pin_t* data_t);

#ifndef GADGET_INIT__
#define GADGET_INIT__
static uint32_t mib_init(mib_init_t* init_data) {
  uint32_t err_code = NRF_SUCCESS;
  init_data->endpoints = (p_endpoints*)malloc(sizeof(p_endpoints) * REQUEST_CNT);
  init_data->return_size = (uint32_t*)malloc(sizeof(uint32_t) * REQUEST_CNT);
  
  init_data->endpoints[MIB_EP_SET_PIN] = set_pin;
  init_data->return_size[MIB_EP_SET_PIN] = sizeof(*set_pin_return_size);

  init_data->endpoints[MIB_EP_CLEAR_PIN] = clear_pin;
  init_data->return_size[MIB_EP_CLEAR_PIN] = sizeof(*clear_pin_return_size);


  init_data->model_number = MODEL_NUMBER;
  init_data->firmware_version_major = FIRMWARE_VERSION_MAJOR;
  init_data->firmware_version_minor = FIRMWARE_VERSION_MINOR;
  init_data->firmware_build_number = FIRMWARE_BUILD_NUMBER;
  memcpy(init_data->product_name, MIB_PRODUCT_NAME, PRODUCT_NAME_LEN);

  init_data->endpoint_length = REQUEST_CNT;

  err_code = mib_initialize(init_data);
  return err_code;
}
#endif // GADGET_INIT__
#endif // GADGET_H__

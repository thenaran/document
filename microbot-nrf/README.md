Microbot-NRF SDK Getting started
===

Prerequisite
==
Development Hardware Kit
-
* Example Project target board
  * Microbot-IO of Naran
  * See Microbot-IO : https://microbot.is/others/
  ![](res/mib-io.png)

* Hardware specification
  * nrf51822 PinMap
 ![](res/mib-io-pin-map.png)

Base
-
* Microbot-NRF는 Nordic NRF5x SDK v11.0.0을 사용하여 다음을 지원합니다. 
  * Download URL : https://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.sdk5.v11.0.0%2Fgetting_started_installing.html
  * Nrf51 - s130(SoftDevice)
  * Nrf52 - s132(SoftDevice)

IDE
-
* Keil uVision4 이상의 IDE를 설치 하셔야 합니다. 회원가입이 필요합니다.
  * Download url : https://www.keil.com/download/product/
  * Installation Guide : https://yadom.fr/downloadable/download/sample/sample_id/202/

Firmware Download Tool
-
* J-Link가 구비되어 있어야 합니다. 
  * Driver : https://www.segger.com/downloads/jlink/ (일반적으로 Keil uVision 설치시 같이 진행됩니다.)	

Configuration
==
Define Endpoints or Events on MicrobotCloud
-
* Endpoints 와 Events는 JSON을 사용하여 정의할 수 있습니다.
* 정의된 Endpoints와 Events를 기반으로 Microbot-NRF library에서 사용되는 gadget.h 파일을 다운받을수 있습니다.
  * Endpoint는 행위를 나타내는 Request로 표현하며 Request의 구성요소는 다음과 같습니다.
    * Request
      * name : EndPoint의 호출명이 됩니다.
      * params : Endpoint의 payload와 Return의 payload를 정의 합니다. payload는 List로 여러개를 선언할 수 있습니다. 선언된 payload는 하나의 structure 로 제공 됩니다.				
        * name : structure의 member variable name 입니다.
        * type : member variable의 데이터 형입니다.
          * char : 1 Byte
          * boolean : 1 Byte
          * uint8_t  : 1 Byte
          * uint16_t : 2 Byte
          * uint32_t : 4 Byte

        * length : argument의 길이
        * default : initialize value
      * return
        * name : structure의 member variable name 입니다.
        * type : argument의 데이터 형입니다.
          * char : 1 Byte
          * boolean : 1 Byte
          * uint8_t  : 1 Byte
          * uint16_t : 2 Byte
          * uint32_t : 4 Byte
        * length : argument의 길이
        * default : initialize value
        * dynamic_return : true & false
          * 리턴의 길이가 가변적일 경우 true로 설정하셔야 합니다. (default : false)
      * timeout : EndPoint 호출뒤 return을 받는데 걸리는 timeout입니다.
        * 0 은 return을 받지 않는 단방향 통신을 의미합니다.
      * Example : Request (JSON)

        ``` json
        "requests":[{
          "name":"set_pin",
          "params":[{
            "name":"pin_number",
            "type":"uint8_t",
            "length":1,
            "default":14
          }],
          "returns":[{
            "name":"result",
            "type":"uint8_t",
            "length":1,
            "default":0
          }],
          "timeout":5
          },
          {
          "name":"clear_pin",
          "params":[{
            "name":"pin_number",
            "type":"uint8_t",
            "length":1,
            "default":0
          }],
          "returns":[{
            "name":"result",
            "type":"uint8_t",
            "length":1,
            "default":0
          }],
          "timeout":5
          }]
        ```

      * Example : gadget.h

        ``` c
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
                
        void set_pin(ep_hnd* _hnd, set_pin_t* data_t);
        void clear_pin(ep_hnd* _hnd, clear_pin_t* data_t);
        ```
  

    * Event의 구성요소는 다음과 같습니다.
      * name : Event handler name이 됩니다.
      * params : Event의 payload를 정의 합니다. payload는 List로 여러개를 선언할 수 있습니다. 
        선언된 payload는 하나의 structure 로 제공 됩니다. 제공되는 structure 의 이름은 events name에 \_t 를 더해진 이름이 자동으로 지정됩니다.
        * name : structure의 member variable name 입니다.
        * type : member variable의 데이터 형입니다.
          * char : 1 Byte
          * boolean : 1 Byte
          * uint8_t  : 1 Byte
          * uint16_t : 2 Byte
          * uint32_t : 4 Byte
        * length : argument의 길이
        * default : initialize value 
        * Example : Event (JSON)


          ``` json
          "events":[{
            "name":"pin_interrupt",
            "params":[{
                "name":"pin_number",
                "type":"uint8_t",
                "length":1
                },
                {
                "name":"pin_state",
                "type":"uint8_t",
                "length":1
                }],
            "dynamic_event":"false"}]
          ```

        * Example : gadget.h

          ``` c
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
          ```
        
JSON Example
-
* example.json 을 Microbot Console에 업로드하면 다음과 같은 gadget.h를 다운로드 받을수 있습니다.

```json
{
  "product": "mibio",
  "version": "0.1",
  "requests": [{
      "name": "set_pin",
      "params": [{
        "name": "pin_number",
        "type": "uint8_t",
        "length": 1,
        "default": 14
      }],
      "returns": [{
        "name": "result",
        "type": "uint8_t",
        "length": 1
      }],
      "timeout": 5
    },
    {
      "name": "clear_pin",
      "params": [{
        "name": "pin_number",
        "type": "uint8_t",
        "length": 1,
        "default": 14
      }],
      "returns": [{
        "name": "result",
        "type": "uint8_t",
        "length": 1
      }],
      "timeout": 5
    }
  ],
  "events": [{
    "name": "pin_interrupt",
    "params": [{
        "name": "pin_number",
        "type": "uint8_t",
        "length": 1
      },
      {
        "name": "pin_state",
        "type": "uint8_t",
        "length": 1
      }
    ]
  }]
}
```


* gadget.h of Example json
  * download 받은 gadget.h파일은 절대 수정하지 않는것을 권고 합니다.


``` c
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
```

Usage
=
Example Project
-
* Unzip 'example.zip'
* NRF51822 & NRF51422
  * microbot-nrf/example/pca10028/s130\_with\_dfu/arm5/ble_app_hrs_s130_with_dfu_pca10028.uvprojx
* NRF52832 (# Beta Release)
  * microbot-nrf/example/pca10040/s132\_with\_dfu/arm5/ble_app_hrs_s130_with_dfu_pca10040.uvprojx

Example project options
-
* 프로젝트의 속성 확인
  1. IDE 화면에서 좌측 상단의 Project Navigation 화면에서 nrf51xxx_.../s13x 폴더를 마우스 우클릭합니다.
  2. Options for Target 'nrf51xxx.../s130'... 을 클릭 합니다. (단축키 Alt + F7)
  ![](res/Usage-project-1.png)
  3. Options for Target 'nrf...' Dialog 창이 나오면 각 탭에서 다음 사항을 확인 합니다.
    * Device : 테스트 하고자 하는 디바이스가 올바르게 선택되었는지 확인합니다.
    ![](res/Usage-project-3.png)
    * Target : IROM1, IRAM1 에 체크되어 있고 올바른 값인지 확인합니다.
      * nrf51422 & nrf51822
        * IROM1 (start : 0x1B000, size: 0x25000, startup : set)
        * IRAM1 (start : 0x20001F00, size 0x5100, noInit: clear)
      * nrf52832
        * IROM1 (start : 0x1B000, size: 0x25800, startup : set)
        * IRAM1 (start : 0x20002800, size 0xD800, noInit: clear)
        ![](res/Usage-project-4.png)
    * C/C++ : Define(text input box)에 하기의 모든 옵션이 표기되어야 합니다.
      * BLE\_DFU\_APP_SUPPORT 
      * BLE\_STACK\_SUPPORT_REQD
      * NRF51 or NRF52 (Please Choice your device) 
      * S130 & S132 (Please Choice your device, nrf51:S130 & nrf52:S132)
      * BOARD\_CUSTOM
        * 만약 nrf development kit을 사용하시면 BOARD\_CUSTOM을 지우고 다음과 같이 작성합니다.
        * nrf51 : BOARD\_PCA10028
        * nrf52 : BOARD\_PCA10040
      * SWI\_DISABLE0 
      * SOFTDEVICE\_PRESENT 
      * NRF\_LOG\_USES_UART=1
      * Copy this codes 

      ```
      BLE_DFU_APP_SUPPORT BLE_DFU_APP_SUPPORT BLE_STACK_SUPPORT_REQD SWI_DISABLE0 SOFTDEVICE_PRESENT NRF51&NRF52 S130&S132
      ```

      ![](res/Usage-project-5.png)
    * Debug : Use 드랍박스가 J-LINK/J-TRACE Cortex 로 선택 되어야 합니다. 우측의 'Settings'를 눌러 다음 옵션들을 확인합니다.
    ![](res/Usage-project-6.png)
      * Debug tab
        * Port : SW
        * Click to 'Auto Clk'
      * Flash Download
        * select Erase Sectors
        * set to Program, Verify, Reset and Run check box
      * RAM for Algorithm
        * start: 0x20000000 size : 0x2000
      ![](res/Usage-project-7.png)

Import Microbot-NRF library to Example Project
-
* Download from MicrobotCloud in 'Download SDK'
* Unzip 'microbot-nrf-sdk-v01.00.zip'
* 압축 해제를 하면 lib폴더에서 다음 파일들을 볼 수 있습니다.
  * microbot.h
  * mib_bsp.h
  * bsp\_btn\_ble.h
  * ble\_dfu.h
  * ble\_advdata.h
  * ble\_advertising.h
  * dfu\_app\_handler.h
  * nrf\_drv\_wdt.h
  * microbot-nrf51.lib or microbot-nrf52.lib
  ![](res/Usage-project-8.png)
* Add new Group
  1. Keil 프로젝트를 실행 시킵니다.
  2. IDE 화면내 좌측 상단의 Project Navigation에서 nrf51xxx\_.../s13x 폴더를 마우스 우클릭합니다.
  3. Add Group ... 을 눌러 lib 이름의 group을 생성 합니다.
  ![](res/Usage-project-9.png)
* Add Library file
  1. Project Navigation 화면에서 생성한 'lib' group을 마우스 우클릭합니다.
  2. Add Existing Files to Group 'lib' ... 을 눌릅니다.
  ![](res/Usage-project-10.png)
  3. lib 폴더에서 NRF5x의 타겟보드 버전을 선택한 뒤에 Add버튼을 눌러 추가합니다.
  ![](res/Usage-project-11.png)
* Add Include Path
  1. Project Navigation 화면에서 nrf51xxx.../s13x 폴더를 마우스 우클릭합니다.
  2. Options for Target 'nrf51xxx.../s13x'... 을 클릭 합니다. (단축키 Alt + F7)
  ![](res/Usage-project-12.png)
  3. C/C++ 탭을 선택하여 'Include Paths'에 다음과 같이 입력합니다.
    * lib 폴더의 header파일을 프로젝트에 기본 path로 등록하기 위하여 다음과 같이 입력 합니다. 
    ![](res/Usage-project-14.png)
  
Microbot-NRF library에 gadget.h 적용하기
-
* 상기 Step에서 Keil Project Option에 '.\\lib' 를 포함 하였다고 가정합니다.
* Microbot Console에서 json 명세에 의하여 생성된 gadget.h 파일을 다운로드 받습니다.
* gadget.h파일을 microbot-nrf5x.lib파일이 위치한 lib폴더로 이동 시킵니다.
* 또는 gadget.h파일이 저장된 path를 'include headers'에 추가합니다.
  * 예제에서는 dev라는 폴더에 gadget.h파일을 추가하였습니다.
  ![](res/Usage-project-15.png)
  ![](res/Usage-project-16.png)
* Example Project 내에 main.c를 보면 다음과 같이 간단한 main.c가 정의 되어있을 것 입니다.

```c
// Step 1 : just add this header!!
#include "gadget.h"
#include "nrf_gpio.h"
#include "nrf_drv_gpiote.h"

// Step 2 : for the mib_init_t 
#define LED_0          				8					// BLUE
#define LED_1          				9 				// GREEN
#define LED_2          				10				// RED
#define BUTTON_0       				22
#define MIN_BATTERY_LEVEL			640				/**< Minimum battery level.  2.7V*/     //0%
#define MAX_BATTERY_LEVEL			770				/**< Maximum battery level. 4.1V*/ //    100%
#define BOARD_REVISION_MAJOR	0
#define BOARD_REVISION_MINOR	1
#define APP_VERSION_MAJOR			3
#define APP_VERSION_MINOR			37
#define INTERRUPT_PIN 				12

// Step 3 : define mib_init_t 
static mib_init_t        microbot_init;

// Step 4 : microbot-nrf event_handler, more case 'Microbot sdk document'
void microbot_evt_handler(ble_microbot_evt_t * p_evt)
{
  switch (p_evt->evt_type)
  {
  case MIB_EVT_REVEAL:
    break;
  case MIB_EVT_CONNECTED:
    break;
  case MIB_EVT_DISCONNECTED:
    break;
  case MIB_EVT_BTN_PUSH:
    break;
  case MIB_EVT_BTN_RELEASE:
    break;
  case MIB_EVT_BTN_LONG_PUSH:
    break;
  default:
    break;
  }
}

// Step 5 : Copy & Paste of endpoint functions in gadget.h
//          and Definition of endpoints
void set_pin(ep_hnd* _hnd, set_pin_t* data)
{
  nrf_gpio_cfg_output(data->pin_number);
  nrf_gpio_pin_set(data->pin_number);
  mib_return(_hnd, data);
}
void clear_pin(ep_hnd* _hnd, clear_pin_t* data)
{
  nrf_gpio_cfg_output(data->pin_number);
  nrf_gpio_pin_clear(data->pin_number);
  mib_return(_hnd, data);
}

static void init()
{
  uint32_t err_code;
  microbot_init.evt_handler = microbot_evt_handler;
  microbot_init.led_red_pin_number = LED_2;
  microbot_init.led_green_pin_number = LED_1;
  microbot_init.led_blue_pin_number  = LED_0;
  microbot_init.max_batt  = MAX_BATTERY_LEVEL;
  microbot_init.min_batt  = MIN_BATTERY_LEVEL;
  microbot_init.button_pin_number = BUTTON_0;
  microbot_init.button_active_state  = false;
  microbot_init.bsp_button_pull = NRF_GPIO_PIN_PULLUP;

  // Step 6 : call 'mib_init()'! do not call 'mib_initialize()'
  err_code = mib_init(&microbot_init);
  APP_ERROR_CHECK(err_code);
}

void interrupt_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
  pin_interrupt_t data;
  data.pin_number = (uint8_t)pin;
  data.pin_state = action;
  // Step 7 : raise event definition like this function
  mib_event_write(MIB_EVT_PIN_INTERRUPT, &data, sizeof(pin_interrupt_t));
}

static void pin_interrupt_init()
{
  // gyro gpio interrupt
  nrf_drv_gpiote_in_config_t pin_interrupt_config_in = GPIOTE_CONFIG_IN_SENSE_TOGGLE(false);
  pin_interrupt_config_in.pull = NRF_GPIO_PIN_PULLDOWN;
  nrf_drv_gpiote_in_init(INTERRUPT_PIN, &pin_interrupt_config_in, interrupt_handler);
  nrf_drv_gpiote_in_event_enable(INTERRUPT_PIN, true);
}

int main(void)
{
  init();
  pin_interrupt_init();
  // Step 8 : call microbot service loop
  start_microbot();
}
```

* Description of example 'main.c'
  * Step 1 : include "gadget.h" 
  * Step 2 : declare pin number variable for the mib_init_t 
  * Step 3 : declare mib_init_t structure 
  * Step 4 : definition microbot-nrf event_handler, more case 'Microbot-SDK Document'
  * Step 5 : Copy & Paste of endpoint functions in gadget.h, and Definition of endpoints
  * Step 6 : call 'mib_init()'! do not call 'mib_initialize()'
  * Step 7 : raise event definition like 'pin_interrupt_init()'
  * Step 8 : call microbot service loop


* 다운로드 받은 gadget.h는 microbot console에 명세한 json에 의해서 생성되어집니다.
* 생성된 gadget.h는 수정을 하지 않는것을 권고합니다. 

First time build of example project
-
1. Download and Unzip to 'example.zip'
2. Download and Unzip to 'microbot-nrf.zip'
3. Import library to example project
4. Download 'gadget.h' from Microbot Console, and paste to 'dev' folder
5. build(F7) and Run(F8)

Microbot-NRF SDK Getting started
===

Prerequisite
==
Base
-
* Microbot-NRF는 Nordic NRF5x 시리즈의 BLE 기술을 사용합니다.  

IDE
-
* Keil uVision4 이상의 IDE를 설치 하셔야 합니다. 회원가입이 필요합니다.
	* Download url : https://www.keil.com/download/product/
	* Installation Guide : https://yadom.fr/downloadable/download/sample/sample_id/202/

Download Tool
-
* J-Link가 구비되어 있어야 합니다. (일반적으로 Keil uVision 설치시 같이 진행됩니다.)
	* Driver : https://www.segger.com/downloads/jlink/

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
				
                | type | byte |
				|----|----|
             |char|1 Byte|
             |boolean|1 Byte|
				|uint8_t|1 Byte|
				|uint16_t|2 Byte|
				|uint32_t|4 Byte|
				* length : argument의 길이
				* default : initialize value
			* return
				* name : structure의 member variable name 입니다.
				* type : argument의 데이터 형입니다.
				
                | type | byte |
				|----|----|
                |char|1 Byte|
                |boolean|1 Byte|
				|uint8_t|1 Byte|
				|uint16_t|2 Byte|
				|uint32_t|4 Byte|
				* length : argument의 길이
				* default : initialize value  
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
			            "default":0
			        }],
			        "returns":[{
			            "name":"result",
			            "type":"uint8_t",
			            "length":1,
			            "default":0
			        }],
			        "timeout":3
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
			        "timeout":3
			    }]
	
				```
			* Example : gadget.h

				``` c
				// gadget.h
				typedef enum
				{
				  MIB_EP_SET_PIN = 0,
				  MIB_EP_CLEAR_PIN,
				} request_ids;
				
				typedef struct set_pin_t set_pin_t;
				struct set_pin_t
				{
				  uint8_t pin_number[1];
				};
				typedef struct clear_pin_t clear_pin_t;
				struct clear_pin_t
				{
				  uint8_t pin_number[1];
				};
				
				typedef struct set_pin_return_t set_pin_return_t;
				struct set_pin_return_t
				{
				  uint8_t result[1];
				};
				
				typedef struct clear_pin_return_t clear_pin_return_t;
				struct clear_pin_return_t
				{
				  uint8_t result[1];
				};
				
				void set_pin(ep_hnd* _hnd, set_pin_t* data_t);
				void clear_pin(ep_hnd* _hnd, clear_pin_t* data_t);
				```
		* Event의 구성요소는 다음과 같습니다.
			* name : Event handler name이 됩니다.
			* params : Event의 payload를 정의 합니다. payload는 List로 여러개를 선언할 수 있습니다. 
			  선언된 payload는 하나의 structure 로 제공 됩니다. 제공되는 structure 의 이름은 request name에 \_t 를 더해진 이름이 자동으로 지정됩니다.
				* name : structure의 member variable name 입니다.
				* type : member variable의 데이터 형입니다.
				
                | type | byte |
				|----|----|
                |char|1 Byte|
                |boolean|1 Byte|
				|uint8_t|1 Byte|
				|uint16_t|2 Byte|
				|uint32_t|4 Byte|
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
					        }]
					    }]
					```

				* Example : gadget.h

					``` c
					typedef enum
					{
					  MIB_EVT_PIN_INTERRUPT = 0,
					} event_ids;
					typedef struct mib_event_type_t mib_event_type_t;
					struct mib_event_type_t
					{
					  uint16_t pin_interrupt;
					};
					typedef struct pin_interrupt_t pin_interrupt_t;
					struct pin_interrupt_t
					{
					  uint8_t pin_number[1];
					  uint8_t pin_state[1];
					};
					
					```
				
JSON Example
-
```json
{
"product":"mibio",
"version":"0.1",
"requests":[{
    "name":"set_pin",
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
    "timeout":7
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
    "timeout":7
}]
,
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
        }]
    }]
}
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
	3. Options for Target 'nrf...' Dialog 창이 나오면 각 탭에서 다음 사항을 확인 합니다.
		* Device : 테스트 하고자 하는 디바이스가 올바르게 선택되었는지 확인합니다.
		* Target : IROM1, IRAM1 에 체크되어 있고 올바른 값인지 확인합니다.
			* nrf51422 & nrf51822
				* IROM1 (start : 0x1B000, size: 0x25000, startup : set)
				* IRAM1 (start : 0x20001F00, size 0x5100, noInit: clear)
			* nrf52832
				* IROM1 (start : 0x1B000, size: 0x25800, startup : set)
				* IRAM1 (start : 0x20002800, size 0xD800, noInit: clear)
		* C/C++ : Define(text input box)에 하기의 모든 옵션이 표기되어야 합니다.
			* BLE\_DFU\_APP_SUPPORT 
			* BLE\_STACK\_SUPPORT_REQD 
			* S130 & S132 (nrf51:S130 & nrf52:S132)
			* BOARD\_CUSTOM
				* 만약 nrf development kit을 사용하시면 BOARD\_CUSTOM을 지우고 다음과 같이 작성합니다.
				* nrf51 : BOARD\_PCA10028
				* nrf52 : BOARD\_PCA10040
			* SWI\_DISABLE0 
			* SOFTDEVICE\_PRESENT 
			* NRF51 or NRF52
			* NRF\_LOG\_USES_UART=1 
		* Debug : Use 드랍박스가 J-LINK/J-TRACE Cortex 로 선택 되어야 합니다. 우측의 'Settings'를 눌러 다음 옵션들을 확인합니다.
			* Debug tab
				* Port : SW
				* Click to 'Auto Clk'
			* Flash Download
				* select Erase Sectors
				* set to Program, Verify, Reset and Run check box
			* RAM for Algorithm
				* start: 0x20000000 size : 0x2000

Import Microbot-NRF library to Example Project
-
* Download from MicrobotCloud in 'Download SDK'
* Unzip 'microbot-nrf-fw-sdk-xx-xx.zip'
	* 압축 해제를 하면 당신은 2개의 폴더에서 다음의 파일들을 볼 수 있습니다.
		* src
		    * microbot.c
		    * bsp.c
		    * bsp\_btn\_ble.c
		    * ble\_dfu.c
		    * ble\_advdata.c
		    * ble\_advertising.c
		    * dfu\_app\_handler.c
		* include
		   * microbot.h
		   * bsp.h
		   * bsp\_btn\_ble.h
		   * ble\_dfu.h
		   * ble\_advdata.h
		   * ble\_advertising.h
		   * dfu\_app\_handler.h
* src폴더와, include폴더를 당신의 Keil(uVision) 프로젝트파일이 위치한 곳으로 이동합니다.
	* Keil(uVision) 프로젝트 파일의 확장명은 uvprojx 입니다.
	* example 프로젝트 파일 Path
		* example/pca10028/s130\_with\_dfu/arm5/ble\_app\_hrs\*.uvprojx
* Add new Group
	1. Keil 프로젝트를 실행 시킵니다.
	2. IDE 화면내 좌측 상단의 Project Navigation에서 nrf51xxx\_.../s13x 폴더를 마우스 우클릭합니다.
	3. Add Group ... 을 눌러 src 이름의 group을 생성 합니다. 
* Add Library file
	1. Project Navigation 화면에서 생성한 'src' group을 마우스 우클릭합니다.
	2. Add Existing Files to Group 'src' ... 을 눌릅니다.
	3. src 폴더의 모든 *.c 파일들을 선택하여 Add 합니다.
* Add Include Path
	1. Project Navigation 화면에서 nrf51xxx.../s13x 폴더를 마우스 우클릭합니다.
	2. Options for Target 'nrf51xxx.../s13x'... 을 클릭 합니다. (단축키 Alt + F7)
	3. C/C++ 탭을 선택하여 'Include Paths'에 다음과 같이 입력합니다.
		* .\\include
* Add Dev Path
	1.
	2.Project Navigation 화면에서 nrf51xxx.../s13x 폴더를 마우스 우클릭합니다.
	3. Options for Target 'nrf51xxx.../s13x'... 을 클릭 합니다. (단축키 Alt + F7)
	4. C/C++ 탭을 선택하여 'Include Paths'에 다음과 같이 입력합니다.
		* .\\dev  
	
Microbot-NRF library에 gadget.h 적용하기
-
* 상기 Step에서 Keil Project Option에 '.\\include' 를 포함 하였다고 가정합니다.
* Download gadget.h from Micobot Cloud, 받은 파일을 keil(uVision) project의 include 폴더로 이동합니다.
	* example/pca10028/s130\_with\_dfu/arm5/include
* Example Project 내에 main.c를 보면 다음과 같이 간단한 main.c가 정의 되어있을 것 입니다.
* example project 는 microbot devkit(microbot-io)의 GPIO pin을 제어하는 예제 코드입니다.
	* example/pca10028/s130\_with\_dfu/arm5/custom_board.h에서 LED, BUTTON을 정의 할 수 있습니다. 
		* BSP\_LED\_\*
		* BSP\_BUTTON\_\*
* microbot cloud 에서 다운로드 받은 gadget.h는 완성된 파일이므로 수정하지 않는 것을 권장합니다.
* Example gadget.h

	``` c
	#ifndef GADGET_H__
    #define GADGET_H__
    #include <stdio.h>
    #include <stdint.h>
    #include <stdlib.h>
    #define REQUEST_CNT 2
    #define EVENT_CNT 1
    typedef void (*ep_hnd) (void* self, void* cb_data);
    typedef void (*p_endpoints) (ep_hnd* self, void* data);
    static p_endpoints *endpoints;
    typedef enum
    {
      MIB_EP_SET_PIN = 0,	// {SET_PIN}
      MIB_EP_CLEAR_PIN,     // {CLEAR_PIN}
    } request_ids;
    typedef struct set_pin_t set_pin_t;
    struct set_pin_t
    {
      uint8_t pin_number;
    };
    typedef struct clear_pin_t clear_pin_t;
    struct clear_pin_t
    {
      uint8_t pin_number;
    };
    typedef struct set_pin_return_t set_pin_return_t;
    struct set_pin_return_t
    {
      uint8_t result;
    };
    typedef struct clear_pin_return_t clear_pin_return_t;
    struct clear_pin_return_t
    {
      uint8_t result;
    };
    typedef enum
    {
      MIB_EVT_PIN_INTERRUPT = 0,
    } event_ids;
    typedef struct mib_event_type_t mib_event_type_t;
    struct mib_event_type_t
    {
      uint16_t pin_interrupt;
    };
    typedef struct pin_interrupt_t pin_interrupt_t;
    struct pin_interrupt_t
    {
      uint8_t pin_number;
      uint8_t pin_state;
    };
    
    //endpoint : please copy this functions
    void set_pin(ep_hnd* _hnd, set_pin_t* data_t);
    void clear_pin(ep_hnd* _hnd, clear_pin_t* data_t);
    
    #ifndef GADGET_INIT__
    #define GADGET_INIT__
    static void mib_init(void) {
      endpoints = malloc(sizeof(p_endpoints) * REQUEST_CNT);
      endpoints[MIB_EP_SET_PIN] = set_pin;
      endpoints[MIB_EP_CLEAR_PIN] = clear_pin;
      mib_event.pin_interrupt = MIB_EVT_PIN_INTERRUPT;
    }
    #endif // GADGET_INIT__
    #endif // GADGET_H__
	```

Define to definition of yout endpoints and events
-
* Download 받은 gadget.h 파일의 mib_init(void)상단의 endpoint를 확인합니다.
	1. 정의된 endpoint function을 복사합니다.
	2. example project의 main.c에 복사한 endpoint들을 붙여넣습니다.
	3. 함수의 정의를 완료 합니다.
* Return이 필요한 경우 mib_return()함수를 사용합니다. 
* microbot\_nrf\_init()의 parameters를 테스트하는 환경에 맞춰서 변경하시면 됩니다.
* start\_microbot()은 service loop을 제공합니다.
	* 별도의 ioloop을 사용하고자 한다면 다음의 함수를 ioloop에서 호출해 주세요.
	* TODO : ...
* Example main.c
	
	```c
	#include "microbot.h"
	#include "gadget.h"
	#pragma pack(1)
	#define MIN_BATTERY_LEVEL 640
	#define MAX_BATTERY_LEVEL 770
    #define BOARD_REVISION_MAJOR 0
    #define BOARD_REVISION_MINOR 1
    #define APP_VERSION_MAJOR 0
    #define APP_VERSION_MINOR 1
    static char device_name[5] = "mibio";
	void set_pin(ep_hnd* _hnd, set_pin_t* data_t)
	{
	   set_pin_return_t set_pin_return;
	   // do any code here ...
	   
	   set_pin_return.result = true;
		mib_return(_hnd, set_pin_return);
	}
	void clear_pin(ep_hnd* _hnd, clear_pin_t* data_t)
	{
	   clear_pin_return_t clear_pin_return;
	   // do any code here ...
	   
	   clear_pin_return = true;
		mib_return(_hnd, clear_pin_return);
	} 
    static void microbot_nrf_init()
	{
	  uint32_t err_code;	
	  microbot_init.evt_handler             = microbot_evt_handler;
	  microbot_init.p_report_ref            = NULL;
	  microbot_init.led_red                 = BSP_LED_2_MASK;
	  microbot_init.led_green               = BSP_LED_1_MASK;
	  microbot_init.led_blue                = BSP_LED_0_MASK;
	  microbot_init.button                  = BSP_BUTTON_0
	  microbot_init.max_batt                = MAX_BATTERY_LEVEL;
	  microbot_init.min_batt                = MIN_BATTERY_LEVEL;
	  microbot_init.board_revision_major    = BOARD_REVISION_MAJOR;
	  microbot_init.board_revision_minor    = BOARD_REVISION_MINOR;
	  microbot_init.app_version_major       = APP_VERSION_MAJOR;
	  microbot_init.app_version_minor       = APP_VERSION_MINOR;
	  microbot_init.bsp_button_high_to_low  = false;
	  memcpy(microbot_init.device_tag, device_name, 5);
	  err_code = mib_initialize(microbot_init);
	  APP_ERROR_CHECK(err_code);
	}
	int main(void)
	{
	  microbot_nrf_init();
	  start_microbot();
	}
	```

First time build of example project
-
1. Download and Unzip to 'example.zip'
2. Download and Unzip to 'microbot-nrf.zip'
3. Import src(*.c) and microbot-nrf headers(.\\include) to example project
4. Download 'gadget.h' from MibCloud, and paste to 'dev' folder
5. Check pin number of 'custom_board.h' in 'dev' folder
6. build(F7) and Run(F8)
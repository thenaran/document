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
#include "Board/Config.h"
#if defined(CONFIG_EN_BLUETOOTH)

#include <atomic>
#include <pico/cyw43_arch.h>

#include "Board/board_api_private/board_api_private.h"
#include "Board/ogxm_log.h"

#if defined(CYW43_WL_GPIO_LED_PIN) && defined(LED_INDICATOR_PIN)
static_assert(CYW43_WL_GPIO_LED_PIN != LED_INDICATOR_PIN, "CYW43_WL_GPIO_LED_PIN cannot be the same as LED_INDICATOR_PIN");
#endif

namespace board_api_bt {

std::atomic<bool> inited{false};

void init() {
    if (cyw43_arch_init() != 0) {
        OGXM_LOG("board_api_bt: CYW43 init failed\n");
        panic("CYW43 init failed");
    } else {
        inited.store(true);
        OGXM_LOG("board_api_bt: CYW43 init OK\n");
    }

#if defined(CONFIG_TARGET_PICO_W)
void board_api_bt::connect_wifi(const char* ssid, const char* pass) {
    // Blocking connect using cyw43_arch APIs. This is simplified example code.
    OGXM_LOG("board_api_bt: attempting wifi connect\n");
    cyw43_arch_init();
    // Use default interface and station mode
    cyw43_arch_enable_sta_mode();
    // Attempt join (blocking call may be platform-specific)
    int rc = cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, 10000);
    if (rc == 0) {
        OGXM_LOG("board_api_bt: wifi connected\n");
    } else {
        OGXM_LOG("board_api_bt: wifi connect failed\n");
    }
}
#endif
}

void set_led(bool state) {
    if (!inited.load()) {
        OGXM_LOG("board_api_bt: set_led skipped (not inited)\n");
        return;
    }
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state ? 1 : 0);
    OGXM_LOG(state ? "board_api_bt: set_led ON\n" : "board_api_bt: set_led OFF\n");
}

} // namespace board_api_bt

#endif // defined(CONFIG_EN_BLUETOOTH)
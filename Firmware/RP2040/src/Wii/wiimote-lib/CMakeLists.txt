add_library(wiimote-lib INTERFACE)
if(NOT DEFINED PICO_CYW43_ARCH_LIBRARY)
    set(PICO_CYW43_ARCH_LIBRARY pico_cyw43_arch_none CACHE INTERNAL "CYW43 arch target for wiimote-lib")
endif()
target_include_directories(wiimote-lib INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(wiimote-lib INTERFACE pico_stdlib pico_btstack_classic pico_btstack_cyw43 ${PICO_CYW43_ARCH_LIBRARY})
target_sources(wiimote-lib INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/wiimote_btstack.c
    ${CMAKE_CURRENT_LIST_DIR}/wiimote.c
    ${CMAKE_CURRENT_LIST_DIR}/wm_reports.c
    ${CMAKE_CURRENT_LIST_DIR}/motion.c
    ${CMAKE_CURRENT_LIST_DIR}/wm_crypto.c
    ${CMAKE_CURRENT_LIST_DIR}/inet.c)

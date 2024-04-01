#include <stdio.h>

#include <py/mphal.h>

// Send string of given length to stdout, converting \n to \r\n.
void mp_hal_stdout_tx_strn_cooked(const char* str, size_t len) {
    printf("%.*s", (int)len, str);
}

void mp_hal_stdout_tx_str(const char* str) {
    printf("%s", str);
}

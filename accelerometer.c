#include <16F877A.h>

#fuses NOWDT

#use delay(clock = 20000000)
#use rs232(UART1, baud = 9600)

int8 ticks;
#INT_CCP1
void time_capture() {
    ticks = CCP_1_LOW;
    output_high(PIN_B4);
    delay_us(10);
    output_low(PIN_B4);
    set_timer1(0);
}

void main() {
    ticks = 0;
    enable_interrupts(INT_CCP1);
    enable_interrupts(GLOBAL);
    setup_ccp1(CCP_CAPTURE_RE);
    setup_timer_1(T1_INTERNAL);
    while (1) {
        // tao = RC
        // ticks * 4 / Fosc = R * (10 + 10 * A) * 1e-12
        // A = (ticks - 20) / 20.0
        float acceleration = (ticks - 20) / 20.0;
        printf("Acceleration = %g m/s^2\n\r", acceleration);
    }
}

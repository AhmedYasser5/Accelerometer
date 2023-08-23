# Capacitance-Based Accelerometer

* This is an implementation of an accelerometer sensor. It has a mass that change position with acceleration. The change of the position alters the capacitance of the sensor's output by the equation:

$$C = 10 + 10 \times A$$

where $C$ is the capacitance in $pF$ and $A$ is the acceleration in $m/s^2$.

* The sensor operates on the range from $1$ to $10\ m/s^2$. To measure the acceleration, we connect the sensor to a resistance to form an $RC$ circuit, so that we can benefit from measuring the time constant to calculate the acceleration.

* The charging follows the well-known equation:

$$V_c = 1 - e^{t/RC}$$

## Design criterion:
- An $RC$ circuit is used with a resistor of $400\ kOhm$ to slow down the rate of charge/discharge.
- A comparator is used to capture the time at which the voltage exceeds the voltage at the time constant.
- The output of the comparator is sent to the capture module of timer1.
- In the ISR, the number of ticks is recorded and a pulse is sent to the MOSFET with a duration of $10\ us$.
- The timer is then reset to take further measurements.
- In the main function, only the acceleration is computed from the ticks and
printed.

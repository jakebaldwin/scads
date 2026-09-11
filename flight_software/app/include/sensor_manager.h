#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <cstdint>
#include "sensor_types.h"

/**
 * SensorManager owns sensor hardware drivers and publishes SensorSnapshot
 * data for consumption by Estimator and HealthMonitor.
 *
 * Responsibilities:
 *   - Initialize sensor peripherals (init)
 *   - Poll each sensor on its own schedule, stamping each reading with its
 *     capture time (step)
 *   - Mark per-sensor validity based on driver status
 *   - Bundle the most recent reading from each sensor into a SensorSnapshot
 *     for downstream consumers
 *
 * Note: each Reading in a SensorSnapshot carries its own timestamp_ms. The
 * snapshot is not a simultaneous sample — sensors run at different rates
 * (e.g. IMU ~100 Hz, star tracker ~1 Hz), and consumers are responsible for
 * checking freshness per sensor.
 *
 * For v1, sensor reads may be synthesized rather than driven by real hardware.
 */
class SensorManager {

public:

    SensorManager() = default;

    // Configure sensor peripherals. Must be called after FreeRTOS is running
    // but before step() is invoked.
    void init();

    // Poll sensors that are due for sampling, stamp each reading, and update
    // the published SensorSnapshot. Intended to be called periodically from
    // the SensorManager task.
    void step();

private:

};

#endif

#ifndef HEALTH_MONITOR_H
#define HEALTH_MONITOR_H

struct HealthStatus {
    bool gyro_ok;
    bool magnometer_ok;
    bool sun_sensor_ok;
    bool actuators_ok;
    uint32_t last_update_ms_;
};

class HealthMonitor {

public:

    HealthMonitor() = default;

    void init();
    void step();

private:

};

#endif

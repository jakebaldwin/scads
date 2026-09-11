#ifndef ESTIMATOR_H
#define ESTIMATOR_H

#include <array>

class Estimator {

public:
    explicit Estimator(QueueHandle_t sensor_queue);

    void init();

    void step();

private:
    // storing the current best attitude estimate
    float quat_[4];             // attitude quaternion
    float omega_[3];            // angular rate (radians / sec)
    float gyro_bias_[3];        // gyroscopic bias
    uint32_t last_update_ms_;

    // store count of samples below rate
    uint32_t consecutive_below_threshold_count_;
};

#endif

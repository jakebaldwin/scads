#ifndef SENSOR_TYPES_H
#define SENSOR_TYPES_H

#include <cstdint>

/**
 * Conventions for all sensor data:
 *   - 3-vectors are in spacecraft body frame
 *   - Quaternions are Hamilton convention [w, x, y, z]
 *   - All timestamps are boot-time monotonic, milliseconds
 */

/**
 * ImuReading stores gyroscope data from the IMU
 *
 * gyro_xyz     - 3-vector of angular velocity about each body axis, rad/s
 * timestamp_ms - time of sample capture
 * valid        - true if the reading is trustworthy
 */
struct ImuReading {
    float    gyro_xyz[3];
    uint32_t timestamp_ms;
    bool     valid;
};

/**
 * AccelerometerReading stores sensor data from the accelerometer
 *
 * accel_xyz    - 3-vector of linear acceleration along body axes, m/s^2
 * timestamp_ms - time of sample capture
 * valid        - true if the reading is trustworthy
 */
struct AccelerometerReading {
    float    accel_xyz[3];
    uint32_t timestamp_ms;
    bool     valid;
};

/**
 * MagnetometerReading stores sensor data from the magnetometer.
 *
 * mag_xyz      - 3-vector of local magnetic field, gauss
 * timestamp_ms - time of sample capture
 * valid        - true if the reading is trustworthy
 */
struct MagnetometerReading {
    float    mag_xyz[3];
    uint32_t timestamp_ms;
    bool     valid;
};

/**
 * SunReading stores sensor data from the sun sensor.
 *
 * sun_xyz      - unit 3-vector of sun direction in body frame (dimensionless)
 * timestamp_ms - time of sample capture
 * valid        - true if the sun sensor has lock
 *                (false during eclipse is expected, not a fault)
 */
struct SunReading {
    float    sun_xyz[3];
    uint32_t timestamp_ms;
    bool     valid;
};

/**
 * StarTrackerReading stores attitude data from the star tracker.
 *
 * quat         - Hamilton quaternion [w, x, y, z] attitude estimate
 * timestamp_ms - time of sample capture
 * valid        - true if the tracker has valid star-pattern lock
 */
struct StarTrackerReading {
    float    quat[4];
    uint32_t timestamp_ms;
    bool     valid;
};

/**
 * SensorSnapshot is the aggregated latest readings from all sensors,
 * published by SensorManager and consumed by Estimator and HealthMonitor.
 * Each reading carries its own capture timestamp; the snapshot itself
 * is only a bundle of the most recent values per sensor.
 *
 * imu   - IMU (gyro) reading
 * accel - accelerometer reading
 * mag   - magnetometer reading
 * sun   - sun sensor reading
 * star  - star tracker reading
 */
struct SensorSnapshot {
    ImuReading           imu;
    AccelerometerReading accel;
    MagnetometerReading  mag;
    SunReading           sun;
    StarTrackerReading   star;
};

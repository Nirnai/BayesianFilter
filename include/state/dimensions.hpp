#pragma once

#include <cmath>

struct Dimension {
    Dimension(int val) : value(val) {}
    Dimension(float val) : value(val) {}
    Dimension(double val) : value(val) {}
    double value;
};

/**
 * @brief Represents a Cartesian Dimension like x, y, z
 * 
 */
struct CartesianDimension : public Dimension {
    using Dimension::Dimension;
};

/**
 * @brief Represents a Spherical Dimension like roll, pitch, yaw
 * 
 */
struct SphericalDimension: public Dimension {
    /**
     * @brief Construct a new Spherical Dimension
     * 
     * @param angle Initial angle of the dimension
     */
    SphericalDimension(double angle): Dimension(angle) {
        normalize();
    }

    /**
     * @brief Normalize the input angle into a range [-Pi;Pi)
     * 
     */
    void normalize(){ 
        value = value - (std::floor((value + M_PI)/(2*M_PI)))*2*M_PI;
    }
};

struct MotionDimension: public Dimension {
    using Dimension::Dimension;
}; 

struct X : public CartesianDimension {
    using CartesianDimension::CartesianDimension; 
};

struct Y : public CartesianDimension {
    using CartesianDimension::CartesianDimension; 
};

struct Z : public CartesianDimension {
    using CartesianDimension::CartesianDimension; 
};

struct Roll : public SphericalDimension {
    using SphericalDimension::SphericalDimension; 
};

struct Pitch : public SphericalDimension {
    using SphericalDimension::SphericalDimension; 
};

struct Yaw : public SphericalDimension {
    using SphericalDimension::SphericalDimension; 
};

struct VelocityX: public MotionDimension {
    using MotionDimension::MotionDimension;
};

struct VelocityY: public MotionDimension {
    using MotionDimension::MotionDimension;
};

struct VelocityZ: public MotionDimension {
    using MotionDimension::MotionDimension;
};

struct AccelerationX: public MotionDimension {
    using MotionDimension::MotionDimension;
};

struct AccelerationY: public MotionDimension {
    using MotionDimension::MotionDimension;
};

struct AccelerationZ: public MotionDimension {
    using MotionDimension::MotionDimension;
};

struct RollRate : public MotionDimension {
    using MotionDimension::MotionDimension; 
};

struct PitchRate : public MotionDimension {
    using MotionDimension::MotionDimension; 
};

struct YawRate : public MotionDimension {
    using MotionDimension::MotionDimension; 
};
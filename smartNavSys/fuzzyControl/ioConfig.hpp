#ifndef __IOCONFIG_H__
#define __IOCONFIG_H__

namespace in_sensor1 {
    constexpr const char *NAME{"in_sensor1"};
    namespace membership1 {
        constexpr const char *MEMBERSHIP_LEJOS{"LEJOS"};
        constexpr float value{0};
        constexpr float point1{30};
        constexpr float point2{940};
        constexpr float slope1{((float)1/30)};
        constexpr float slope2{((float)1/30)};
    };
    namespace membership2 {
        constexpr const char *MEMBERSHIP_CERCA{"CERCA"};
        constexpr float value{0};
        constexpr float point1{-60};
        constexpr float point2{60};
        constexpr float slope1{((float)1/30)};
        constexpr float slope2{((float)1/30)};
    };
}; // namespace in_sensor1

namespace in_sensor2 {
    constexpr const char *NAME{"in_sensor2"};
    namespace membership1 {
        constexpr const char *MEMBERSHIP_LEJOS{"LEJOS"};
        constexpr float value{0};
        constexpr float point1{30};
        constexpr float point2{940};
        constexpr float slope1{((float)1/30)};
        constexpr float slope2{((float)1/30)};
    };
    namespace membership2 {
        constexpr const char *MEMBERSHIP_CERCA{"CERCA"};
        constexpr float value{0};
        constexpr float point1{-60};
        constexpr float point2{60};
        constexpr float slope1{((float)1/30)};
        constexpr float slope2{((float)1/30)};
    };
}; // namespace in_sensor2

namespace in_sensor3 {
    constexpr const char *NAME{"in_sensor3"};
    namespace membership1 {
        constexpr const char *MEMBERSHIP_LEJOS{"LEJOS"};
        constexpr float value{0};
        constexpr float point1{30};
        constexpr float point2{940};
        constexpr float slope1{((float)1/30)};
        constexpr float slope2{((float)1/30)};
    };
    namespace membership2 {
        constexpr const char *MEMBERSHIP_CERCA{"CERCA"};
        constexpr float value{0};
        constexpr float point1{-60};
        constexpr float point2{60};
        constexpr float slope1{((float)1/30)};
        constexpr float slope2{((float)1/30)};
    };
}; // namespace in_sensor3

namespace in_ov7670 {
    constexpr const char *NAME{"in_ov7670"};
    namespace membership1 {
        constexpr const char *MEMBERSHIP_DERECHA{"DERECHA"};
        constexpr float value{0};
        constexpr float point1{160};
        constexpr float point2{480};
        constexpr float slope1{((float)1/160)};
        constexpr float slope2{((float)1/160)};
    };
    namespace membership2 {
        constexpr const char *MEMBERSHIP_CENTRO{"CENTRO"};
        constexpr float value{0};
        constexpr float point1{0};
        constexpr float point2{320};
        constexpr float slope1{((float)1/160)};
        constexpr float slope2{((float)1/160)};
    };
    namespace membership3 {
        constexpr const char *MEMBERSHIP_IZQUIERDA{"IZQUIERDA"};
        constexpr float value{0};
        constexpr float point1{-160};
        constexpr float point2{160};
        constexpr float slope1{((float)1/160)};
        constexpr float slope2{((float)1/160)};
    };    
}; // namespace in_ov7670

namespace out_speed {
    constexpr const char *NAME{"out_speed"};
    namespace membership1 {
        constexpr const char *MEMBERSHIP_AUMENTAR{"AUMENTAR"};
        constexpr float value{0};
        constexpr float point1{0.30};
        constexpr float point2{0.60};
        constexpr float slope1{((float)1/0.15)};
        constexpr float slope2{((float)1/0.15)};
    };
    namespace membership2 {
        constexpr const char *MEMBERSHIP_MANTENER{"MANTENER"};
        constexpr float value{0};
        constexpr float point1{0.15};
        constexpr float point2{0.45};
        constexpr float slope1{((float)1/0.15)};
        constexpr float slope2{((float)1/0.15)};
    };
    namespace membership3 {
        constexpr const char *MEMBERSHIP_REDUCIR{"REDUCIR"};
        constexpr float value{0};
        constexpr float point1{0.00};
        constexpr float point2{0.30};
        constexpr float slope1{((float)1/0.15)};
        constexpr float slope2{((float)1/0.15)};
    };    
}; // namespace out_speed

namespace out_heading {
    constexpr const char *NAME{"out_heading"};
    namespace membership1 {
        constexpr const char *MEMBERSHIP_DERECHA{"DERECHA"};
        constexpr float value{0};
        constexpr float point1{0};
        constexpr float point2{40};
        constexpr float slope1{((float)1/20)};
        constexpr float slope2{((float)1/20)};
    };
    namespace membership2 {
        constexpr const char *MEMBERSHIP_CENTRO{"CENTRO"};
        constexpr float value{0};
        constexpr float point1{-20};
        constexpr float point2{20};
        constexpr float slope1{((float)1/20)};
        constexpr float slope2{((float)1/20)};
    };
    namespace membership3 {
        constexpr const char *MEMBERSHIP_IZQUIERDA{"IZQUIERDA"};
        constexpr float value{0};
        constexpr float point1{-40};
        constexpr float point2{0};
        constexpr float slope1{((float)1/20)};
        constexpr float slope2{((float)1/20)};
    };    
}; // namespace out_heading

#endif // __IOCONFIG_H__
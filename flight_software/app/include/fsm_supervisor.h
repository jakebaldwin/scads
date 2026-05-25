#ifndef FSM_SUPERVISOR_H
#define FSM_SUPERVISOR_H

// Implementatino of SRS Section 3.1 Ship Finite-States
enum class ShipState {
    Nominal,
    Maneuvering,
    Detumble,
    Attitude_Estimation,
    Safe
};

class FsmSupervisor {

public:

    FsmSupervisor() = default;

    void transition_to_nominal();
    void transition_to_maneuvering();
    void transition_to_detumble();
    void transition_to_attitude_estimation();
    void transition_to_safe();

    ShipState getState();

private:
    ShipState state_ = ShipState::Nominal;
};

#endif

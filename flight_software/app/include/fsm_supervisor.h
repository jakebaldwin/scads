#ifndef FSM_SUPERVISOR_H
#define FSM_SUPERVISOR_H

// Implementatino of SRS Section 3.1 Ship Finite-States
enum ShipState {
    SHIP_STATE_NOMINAL = 0,
    SHIP_STATE_MANEUVERING = 1,
    SHIP_STATE_DETUMBLE = 2,
    SHIP_STATE_ATTITUDE_ESTIMATION = 3,
    SHIP_STATE_SAFE = 4
};

class FsmSupervisor {

public:

    FsmSupervisor() = default;

    void transition_to_nominal();
    void transition_to_maneuvering();
    void transition_to_detumble();
    void transition_to_attitude_estimation();
    void transition_to_safe();

private:
    ShipState state_;
};

#endif

#include "fsm_supervisor.h"

void FsmSupervisor::transition_to_nominal() {
    state_ = ShipState::Nominal;
}

void FsmSupervisor::transition_to_maneuvering() {
    state_ = ShipState::Maneuvering;
}

void FsmSupervisor::transition_to_detumble() {
    state_ = ShipState::Detumble;
}

void FsmSupervisor::transition_to_attitude_estimation() {
    state_ = ShipState::Attitude_Estimation;
}

void FsmSupervisor::transition_to_safe() {
    state_ = ShipState::Safe;
}

ShipState FsmSupervisor::getState() {
    return state_;
}

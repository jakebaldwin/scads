#include "fsm_supervisor.h"

void FsmSupervisor::transition_to_nominal() {
    state_ = SHIP_STATE_NOMINAL;
}

void FsmSupervisor::transition_to_maneuvering() {
    state_ = SHIP_STATE_MANEUVERING;
}

void FsmSupervisor::transition_to_detumble() {
    state_ = SHIP_STATE_DETUMBLE;
}

void FsmSupervisor::transition_to_attitude_estimation() {
    state_ = SHIP_STATE_ATTITUDE_ESTIMATION;
}

void FsmSupervisor::transition_to_safe() {
    state_ = SHIP_STATE_SAFE;
}

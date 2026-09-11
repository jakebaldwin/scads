#include <gtest/gtest.h>
#include "fsm_supervisor.h"

class FsmSupervisorTest : public testing::Test {
protected:
    FsmSupervisor fsm_supervisor_;

    FsmSupervisorTest() {}

    ~FsmSupervisorTest() override {}

    void SetUp() override {

    }

    void TearDown() override {}

};


TEST_F(FsmSupervisorTest, NominalTransitionToDetumble) {

    // Arrange
    fsm_supervisor_.transition_to_nominal();

    // Act
    fsm_supervisor_.transition_to_detumble();

    // Assert
    EXPECT_EQ(ShipState::Detumble, fsm_supervisor_.get_state());
}




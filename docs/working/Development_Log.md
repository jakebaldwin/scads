Development Log

What did you do today and why?
What didn't work and what did you learn?
What decisions did you make and what were the alternatives you rejected?


## April 24 2026
- Committed current progress of SDP and SRS. Broke it up into several logical
    commits. Need to be more incremental with commit history for better 
    rollback points if required.
- Finished first draft SRS Finite State Machine graph SRS 3.1
- Finished first draft of State Transition Requirments SRS 3.2
- Finished first draft of Fault Detection Requirements SRS 3.3

## April 26 2026
- SRS completed first draft of performance, operational environment, safety and
    fault tolerance, and interface requirements.
- Created TBD_Register to track the outstanding TBDs created in the SRS
- Some formatting and document cleanup on SRS

## April 28 2026
- Began setting up blinky to run on Tiva C to prove toolchain is working
- Began thinking about software layout. Determined I will likely need a 
    hardware interface layer within my FSW to allow for google tests to run
    on my machine (not on hardware).

## May 2 2026
- Added TivaWare third party dependency required for blinky
- Wrote main.c for a simple blinky sample on Tiva C launchpad

## May 4 2026
- Wrote CMakeLists.txt for blinky project and compiled project
- Stole toolchain file and modified for this project

## May 5 2026
- Figured out how to flash binary onto Tiva C and wrote documentation for repo
  setup

## May 6 2026
- Added FreeRTOS to CMakeLists.txt and blinky is still compiling

## May 8 2026
- Updated main.c to use FreeRTOS, define two trivial tasks for turning LED
    on and off red and green.
- Actually ran FreeRTOS software on the launchpad, a blinky with two tasks.
- Updated the tivaware third party libraries and docs to fix compatibility with
    FreeRTOS

## May 16 2026
- Converted main.c to main.cpp, had to add compiler options `-fno-exception` and
    `-fno-rtti` to keep C++ from generating exception table. Since this runs
    on bare metal we aren't using exceptions. RTTI is used for things like 
    typeid, which we also do not need.
- Wrote fsm_supervisor.h and implementation, simple to prove C++ compilation 
    works and made stubs for state transitions of the FSM.
- Figured out how to pass objects to FreeRTOS tasks
- Made simple script for build_and_flash because I kept forgetting the commands


## May 25 2026
- Made FSM states enum class for more idiomatic C++
- Added get method to fsm_supervisor
- Wrote sensor manager interface and sensor types to define what data the
    hardware sensors will provide. I decided to use full suite of industry 
    standard sensors (accelerometer, magnetometer, star tracker, etc) since 
    I am not actually purchasing and building these (yet)
- I decided each sensor reading struct will store timestamp. This makes it
    more complicated for downstream consumers but its the idiomatic choice

## September 11 2026
- Wrote unit tests for fsm supervisor and script to run them
- Decided to place cpp flight logic in its own library so I can unit test it
    more easily with the cross compliation. This required CMakeLists.txt
    updates.
- Wrote scripts/build_and_test.sh to build flight logic library unit tests and
    run them
- Updated compiler to use C++26
- Added health monitor and estimator code stubs
- Stubbed and wrote section 1 of SSDD. 
- Created initial architecture design graph

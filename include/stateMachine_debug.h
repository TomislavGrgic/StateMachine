#ifndef __STATE_MACHINE_DEBUG_H__
#define __STATE_MACHINE_DEBUG_H__

#define STATE_MACHINE_DEBUGGING

#include <stdio.h>
#include "stateMachine_types.h"

void printOutList(StateMachine_Handle *state_machine_in);
void printOutTransitionList(StateMachine_Handle *state_machine_in, StateMachine_StateID state_id_in);
void printOutStateMachineInfo(StateMachine_Handle *state_machine_in);

#endif /*__STATE_MACHINE_DEBUG_H__*/
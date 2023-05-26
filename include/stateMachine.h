#ifndef __STATE_MACHINE_LIB_H__
#define __STATE_MACHINE_LIB_H__

#include <stdlib.h>
#include <stdio.h>
#include "stateMachine_types.h"

StateMachine_Error initializeStateMachine(StateMachine_Handle *state_machine_in);
StateMachine_Error setStartingState(StateMachine_Handle *state_machine_in, StateMachine_StateID in_state_id);
StateMachine_Error _registerState(StateMachine_Handle *state_machine_in, const StateMachine_StateID in_state_id, StateMachine_Callback in_callback);
StateMachine_Error registerTransition(StateMachine_Handle *state_machine_in, const StateMachine_StateID source_id, const StateMachine_StateID destenation_id, StateMachine_Callback in_callback);
StateMachine_Error stateMachineHandler(StateMachine_Handle *state_machine_in, StateMachine_StateID state_id_in);

#endif /*__STATE_MACHINE_LIB_H__*/
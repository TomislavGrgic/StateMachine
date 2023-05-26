#include "stateMachine_debug.h"

#ifdef STATE_MACHINE_DEBUGGING
void printOutList(StateMachine_Handle *state_machine_in){
    printf("List start:\r\n");
    for(StateMachine_Size i = 0; i < state_machine_in->number_of_states; i++){
        printf("state_id %d\r\n",state_machine_in->states[i].state_id);
        printf("list_size %d\r\n",state_machine_in->states[i].list_size);
        printf("state_cb %p\r\n",state_machine_in->states[i].state_cb);
        printf("repeats %d\r\n",state_machine_in->states[i].repeats);
        printf("    State transition list start:\r\n");
        for(StateMachine_Size j = 0; j < state_machine_in->states[i].list_size; j++){
            printf("   Transition ID %d\r\n", state_machine_in->states[i].transition_list[j]);
        }
        printf("    State transition list End\r\n");
    }
    printf("List End\r\n");
}

void printOutTransitionList(StateMachine_Handle *state_machine_in, StateMachine_StateID state_id_in){
    printf("TList start:\r\n");
    for(StateMachine_Size i = 0; i < state_machine_in->states[state_id_in].list_size; i++){
        int list_id = state_machine_in->states[state_id_in].transition_list[i];
        printf("Transition ID: %d (%d) -> (%d)\r\n",list_id, state_id_in, state_machine_in->transitions[list_id].destenation_id);
    }
    printf("TList End\r\n");
}

void printOutStateMachineInfo(StateMachine_Handle *state_machine_in){
    printf("========== State machine info ==============\r\n");
    printf("current_state: %d\r\n", state_machine_in->current_state);
    printf("number_of_states: %d\r\n", state_machine_in->number_of_states);
    printf("number_of_transitions: %d\r\n", state_machine_in->number_of_transitions);
    printOutList(state_machine_in);
    for(StateMachine_Size i = 0; i < state_machine_in->number_of_transitions; i++){
        printf("Transition %d: (%d)\r\n", state_machine_in->transitions[i].transition_id, state_machine_in->transitions[i].destenation_id);
    }
}
#else
void printOutList(StateMachine_Handle *state_machine_in){}
void printOutTransitionList(StateMachine_Handle *state_machine_in, StateMachine_StateID state_id_in){}
void printOutStateMachineInfo(StateMachine_Handle *state_machine_in){}
#endif
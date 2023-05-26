#include "stateMachine.h"

static int getStatePosition(StateMachine_State* state_list, StateMachine_Size list_size, StateMachine_StateID state_id_in);

StateMachine_Error initializeStateMachine(StateMachine_Handle *state_machine_in){
    state_machine_in->number_of_states = 0;
    state_machine_in->number_of_transitions = 0;
    state_machine_in->current_state = STATE_MACHINE_INVALID_STATE_VALUE;
    state_machine_in->states = NULL;
    state_machine_in->transitions = NULL;
    return STATE_MACHINE_NO_ERROR;
}

StateMachine_Error setStartingState(StateMachine_Handle *state_machine_in, StateMachine_StateID in_state_id){
    state_machine_in->current_state = getStatePosition(state_machine_in->states, state_machine_in->number_of_states, in_state_id);
    return STATE_MACHINE_NO_ERROR;
}

StateMachine_Error _registerState(StateMachine_Handle *state_machine_in, const StateMachine_StateID in_state_id, StateMachine_Callback in_callback){
    for(StateMachine_Size i = 0; i < state_machine_in->number_of_states; i++){
        if(state_machine_in->states[i].state_id == in_state_id){
            return STATE_MACHINE_ALREADY_REGISTERED;
        }
    }
    state_machine_in->number_of_states++;

    if(state_machine_in->number_of_states == 0){
        return STATE_MACHINE_LIST_OVERFLOW;
    }

    /*In case that the reallocation fails we use a temporery pointer*/
    StateMachine_State* tmp_pointer =  (StateMachine_State*)realloc(state_machine_in->states, state_machine_in->number_of_states * sizeof(StateMachine_State)); 

    if(tmp_pointer == NULL){
       /*Error: Reallocating memory failed*/
       state_machine_in->number_of_states--; /*Change number of states to initial value*/
       return STATE_MACHINE_REALLOC_FAIL;
    }

    state_machine_in->states = tmp_pointer;
    state_machine_in->states[state_machine_in->number_of_states-1].state_id = in_state_id; 
    state_machine_in->states[state_machine_in->number_of_states-1].state_cb = in_callback;
    state_machine_in->states[state_machine_in->number_of_states-1].transition_list = NULL;
    state_machine_in->states[state_machine_in->number_of_states-1].list_size = 0;  
    state_machine_in->states[state_machine_in->number_of_states-1].repeats = STATE_ONE_SHOT;

    return STATE_MACHINE_NO_ERROR;
}

StateMachine_Error registerTransition(StateMachine_Handle *state_machine_in, StateMachine_StateID source_id, StateMachine_StateID destenation_id, StateMachine_Callback in_callback){
    StateMachine_Error err = _registerState(state_machine_in, source_id, NULL);
    if(err != STATE_MACHINE_NO_ERROR && err != STATE_MACHINE_ALREADY_REGISTERED){
        return err;
    }

    err = _registerState(state_machine_in, destenation_id, NULL);
    if(err != STATE_MACHINE_NO_ERROR && err != STATE_MACHINE_ALREADY_REGISTERED){
        return err;
    }

    int source_position = (StateMachine_StateID)getStatePosition(state_machine_in->states, state_machine_in->number_of_states, source_id);
    //int destenation_position = (StateMachine_StateID)getStatePosition(state_machine_in->states, state_machine_in->number_of_states, destenation_id);

    state_machine_in->number_of_transitions++;
    if(state_machine_in->number_of_transitions == 0){
        return STATE_MACHINE_LIST_OVERFLOW;
    }

    StateMachine_Transitions* tmp_pointer =  (StateMachine_Transitions*)realloc(state_machine_in->transitions, state_machine_in->number_of_transitions * sizeof(StateMachine_Transitions)); 
    if(tmp_pointer == NULL){
        state_machine_in->number_of_transitions--; /*Change number of states to initial value*/
        return STATE_MACHINE_REALLOC_FAIL;
    }
    state_machine_in->transitions = tmp_pointer;

    /*Registering a new transition*/
    StateMachine_TransitionID tmp_transition_id = state_machine_in->number_of_transitions-1;
    state_machine_in->transitions[tmp_transition_id].transition_id = tmp_transition_id;
    state_machine_in->transitions[tmp_transition_id].destenation_id = destenation_id;
    state_machine_in->transitions[tmp_transition_id].transiton_cb = in_callback;

    /*Adding a transition to a state*/
    state_machine_in->states[source_position].list_size++;
    if(state_machine_in->states[source_position].list_size == 0){
        return STATE_MACHINE_LIST_OVERFLOW;
    }

    StateMachine_TransitionID* tmp_pointer2 = (StateMachine_TransitionID*)realloc(state_machine_in->states[source_position].transition_list, state_machine_in->states[source_position].list_size * sizeof(StateMachine_TransitionID));
    if(tmp_pointer == NULL){
        state_machine_in->states[source_position].list_size--; /*Change number of states to initial value*/
        return STATE_MACHINE_REALLOC_FAIL;
    } 
    state_machine_in->states[source_position].transition_list = tmp_pointer2;
    state_machine_in->states[source_position].transition_list[state_machine_in->states[source_position].list_size-1] = tmp_transition_id;

    return STATE_MACHINE_NO_ERROR;
}

static int getStatePosition(StateMachine_State* state_list, StateMachine_Size list_size, StateMachine_StateID state_id_in){
    int position_out = -1;
    for(StateMachine_Size i = 0; i < list_size; i++){
        if(state_list[i].state_id == state_id_in){
            position_out = i;
            break;
        }
    }
    return position_out;
}

StateMachine_Error stateMachineHandler(StateMachine_Handle *state_machine_in, StateMachine_StateID state_id_in){
    if(state_machine_in->current_state == state_id_in && state_machine_in->current_state == STATE_MACHINE_INVALID_STATE_VALUE){
        return STATE_MACHINE_NO_ERROR;
    }
    StateMachine_StateID current_state_position = getStatePosition(state_machine_in->states, state_machine_in->number_of_states, state_machine_in->current_state);

    for(StateMachine_Size i = 0; i < state_machine_in->states[current_state_position].list_size; i++){
        int list_id = state_machine_in->states[current_state_position].transition_list[i];
        if(state_machine_in->transitions[list_id].destenation_id == state_id_in){
            state_machine_in->transitions[list_id].transiton_cb(NULL);
            state_machine_in->current_state = state_id_in;
        }
    }
    return STATE_MACHINE_NO_ERROR;
}
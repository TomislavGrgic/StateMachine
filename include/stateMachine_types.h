#ifndef __STATE_MACHINE_TYPES_H__
#define __STATE_MACHINE_TYPES_H__

#define STATE_MACHINE_INVALID_STATE_VALUE   (~0)

typedef enum state_machine_error_codes{
    STATE_MACHINE_NO_ERROR = 0x0000,
    STATE_MACHINE_INIT_ERROR = 0x0001,
    STATE_MACHINE_LIST_OVERFLOW = 0x0002,
    STATE_MACHINE_REALLOC_FAIL = 0x0003,
    STATE_MACHINE_ALREADY_REGISTERED = 0x0004,
    STATE_MACHINE_NULL_CALLBACK = 0x0005
}StateMachine_Error;

typedef enum state_machine_state_repeats{
    STATE_ONE_SHOT = 0,
    STATE_REPEAT = 1
}StateMachine_Repeat;

typedef void (*StateMachine_Callback)(void*);
typedef unsigned short StateMachine_StateID;
typedef unsigned short StateMachine_TransitionID;
typedef unsigned long StateMachine_Size;

typedef struct state_machine_transitions{
    StateMachine_TransitionID transition_id;
    StateMachine_StateID destenation_id;
    StateMachine_Callback transiton_cb;
}StateMachine_Transitions;

typedef StateMachine_TransitionID* StateMachine_TList;

typedef struct state_machine_state{
    StateMachine_StateID state_id;
    StateMachine_Callback state_cb;
    StateMachine_Repeat repeats;
    StateMachine_TList transition_list;
    StateMachine_Size list_size;
}StateMachine_State;


typedef struct state_machine_handle{
/*Public variables*/
    StateMachine_StateID current_state;
    StateMachine_State* states;
    StateMachine_Size number_of_states;
    StateMachine_Transitions* transitions;
    StateMachine_Size number_of_transitions;
}StateMachine_Handle;

#endif /*__STATE_MACHINE_TYPES_H__*/
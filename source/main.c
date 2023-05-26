#include <stdio.h>
#include "stateMachine.h"
#include "stateMachine_debug.h"

enum my_states{
    ZERO,
    FIRST_STATE,
    SECOND_STATE,
    THIRD_STATE,
    FOURTH_STATE
};

void foo1(void* args){
    printf("State1!\r\n");
}

void foo2(void* args){
    printf("State2!\r\n");
}

void foo3(void* args){
    printf("State3!\r\n");
}

void foo4(void* args){
    printf("State4!\r\n");
}

void foo5(void* args){
    printf("State5!\r\n");
}

int main(){
    StateMachine_Handle stateMachine;

    initializeStateMachine(&stateMachine);
    registerTransition(&stateMachine, FIRST_STATE, SECOND_STATE, foo2);
    registerTransition(&stateMachine, SECOND_STATE, THIRD_STATE, foo3);
    registerTransition(&stateMachine, SECOND_STATE, FIRST_STATE, foo1);
    registerTransition(&stateMachine, THIRD_STATE, SECOND_STATE, foo2);
    setStartingState(&stateMachine, FIRST_STATE);

    while(1){
        printf("Change to state: ");
        int a = 0;
        scanf("%d", &a);
        stateMachineHandler(&stateMachine,a);
    }  
    return 1;
}

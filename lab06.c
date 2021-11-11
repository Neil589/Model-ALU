#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "alu.h"

void part1_test();
void part2_test();


int main(){
    part1_test();
    // part2_test();
    return EXIT_SUCCESS;

}

void part1_test(){
    char sub[2] = {0,0};
    char Bool[3] = {0,0,0};
    char shft[2] = {0,0};
    char math[2] = {0,0};
    char circuitType[12];

    int A = 0;
    int B = 0;

    initialize_alu();

    printf("Enter Sub bit: ");
    scanf("%s", sub);
    printf("Enter Bool bits: ");
    scanf("%s", Bool);
    printf("Enter shift bit: ");
    scanf("%s", shft);
    printf("Enter math bit: ");
    scanf("%s", math);
    printf("Enter circuit type (arithmetic, shift, logic, shiftmux, mathmux):\n");
    scanf("%s", circuitType);
    printf("Enter A value: 0x");
    scanf("%x", &A);
    printf("Enter B value: 0x");
    scanf("%x", &B);

    if(strcmp(circuitType, "arithmetic") == 0){
        arithmetic_circuit->A = A;
        arithmetic_circuit->B = B;
        arithmetic_circuit->Sub = sub[0];
        arithmetic_fun_exe(arithmetic_circuit);
        printf("Operation on arithmetic circuit yields: 0x%08X\n", arithmetic_circuit->Y);
    }else if(strcmp(circuitType, "shift") == 0){
        shift_circuit->A = A;
        shift_circuit->B = B;
        strcpy(shift_circuit->Bool, Bool);
        shift_fun_exe(shift_circuit);
        printf("Operation on shift circuit yields: 0x%08X\n", shift_circuit->Y);
    }else if(strcmp(circuitType, "logic") == 0){
        logic_circuit->A = A;
        logic_circuit->B = B;
        strcpy(logic_circuit->Bool, Bool);
        logic_fun_exe(logic_circuit);
        printf("Operation on logic circuit yields: 0x%08X\n", logic_circuit->Y);
    }else if(strcmp(circuitType, "shiftmux") == 0){
        shft_mux->A = A;
        shft_mux->B = B;
        shft_mux->Selector = shft[0];
        mux_fun_exe(shft_mux);
        printf("Operation on shift multiplexer yields: 0x%08X\n", shft_mux->Y);
    }else if(strcmp(circuitType, "mathmux") == 0){
        math_mux->A = A;
        math_mux->B = B;
        math_mux->Selector = math[0];
        mux_fun_exe(math_mux);
        printf("Operation on math multiplexer yields: 0x%08X\n", math_mux->Y);
    }else{
        printf("You did not choose an appropriate name.");
    }
}

void part2_test(){
    char sub[2] = {0,0};
    char Bool[3] = {0,0,0};
    char shft[2] = {0,0};
    char math[2] = {0,0};

    int A = 0;
    int B = 0;

    initialize_alu();

    printf("Enter Sub bit: ");
    scanf("%s", sub);
    printf("Enter Bool bits: ");
    scanf("%s", Bool);
    printf("Enter shift bit: ");
    scanf("%s", shft);
    printf("Enter math bit: ");
    scanf("%s", math);

    if(configure_alu(sub[0], Bool, shft[0], math[0]) == OK){
        printf("Enter A value: 0x");
        scanf("%x", &A);
        printf("Enter B value: 0x");
        scanf("%x", &B);
        printf("0x%08X\n", run_alu(A, B));
    }else{
        printf("invalid configuration values!\n");
    }
}

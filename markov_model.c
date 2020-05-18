#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <math.h>
#define MAX_CHAR 100001
#define state_num 2
double transition_matrix[state_num][state_num];
double transition_matrix2[state_num][state_num];
double state_transition[2][2];
double pi[state_num] = {0.5,0.5};



int main(int argc, char *argv[]){

    
    FILE *fp;
    int order,previous_state = 99,current_state = 0,next_state = 0;
    int prev_char = 0 ,current_char = 0,next_char = 0;// 0=a, 1=t, 2=c, 3=g     
    char ch;
    int char_num = 0;
    char sequence[MAX_CHAR] = {0};
    char *ptr_seq;
    char *fileName = "input2.txt";
    double probability = 0;

    fp = fopen(fileName,"r");
    if(fp == NULL){
        printf("Could not open file %s",fileName);
        exit(1);
    }
    
    // initial state probability    
    order = atoi(argv[1]);

    //state transition probability
    state_transition[0][0] = 0.6; // state1 to state1
    state_transition[0][1] = 0.4; // state1 to state2
    state_transition[1][0] = 0.3; // state2 to state1
    state_transition[1][1] = 0.7; // state2 to state2
    
    
    //{a,t,c,g} row 
    //{a,t,c,g} col
    // transition_matrix[0][0] means that from stateA_A to state_A_A
    // transition_matrix2[1][3] means that from stateB_T to state_B_G
    
    transition_matrix[0][0] = 0.2;  transition_matrix2[0][0] = 0.4;
    transition_matrix[0][1] = 0.3;  transition_matrix2[0][1] = 0.4;
    transition_matrix[0][2] = 0.3;  transition_matrix2[0][2] = 0.2;
    transition_matrix[0][3] = 0.2;  transition_matrix2[0][3] = 0.2;
    transition_matrix[1][0] = 0.2;  transition_matrix2[1][0] = 0.1;
    transition_matrix[1][1] = 0.3;  transition_matrix2[1][1] = 0.4;
    transition_matrix[1][2] = 0.3;  transition_matrix2[1][2] = 0.4;
    transition_matrix[1][3] = 0.2;  transition_matrix2[1][3] = 0.1;
    transition_matrix[2][0] = 0.2;  transition_matrix2[2][0] = 0.3;
    transition_matrix[2][1] = 0.3;  transition_matrix2[2][1] = 0.3;
    transition_matrix[2][2] = 0.3;  transition_matrix2[2][2] = 0.2;
    transition_matrix[2][3] = 0.2;  transition_matrix2[2][3] = 0.2;
    transition_matrix[3][0] = 0.2;  transition_matrix2[3][0] = 0.2;
    transition_matrix[3][1] = 0.3;  transition_matrix2[3][1] = 0.3;
    transition_matrix[3][2] = 0.3;  transition_matrix2[3][2] = 0.4;
    transition_matrix[3][3] = 0.2;  transition_matrix2[3][3] = 0.1;


    srand(time(NULL));
    //printf("%lf | %lf\n",pi[0],pi[1]);
    double random_num = (double)rand()/(RAND_MAX + 1.0);
    if(random_num >= 0 && random_num<= pi[0]){
        probability = log2(pi[0]);
        current_state = 0;
    }
    else{
        probability = log2(pi[1]);
        current_state = 1;
    }

    while((ch = fgetc(fp))!= EOF){        
        if(order == 0){
            printf("Order 0\n");
        }
        if(order == 1){
            //printf("Order 1\n");
            ch = tolower(ch);
            if(current_state == 0){ // in the state 0
                // determine need to change state or not
                random_num = (double)rand()/(RAND_MAX + 1.0);                
                if(random_num < pi[1])
                    next_state = 0;                
                else
                    next_state = 1;
            // determine the transite state and probability                
                probability += log2(state_transition[current_state][next_state]);
                previous_state = current_state;
                current_state = next_state;
                if(current_state == 0){
                    if(ch == 'a'){
                        probability += log2(transition_matrix[prev_char][0]);
                        current_char = 0;
                    }
                    else if(ch == 't'){
                        probability += log2(transition_matrix[prev_char][1]);
                        current_char = 1;
                    }
                    else if(ch == 'c'){
                        probability += log2(transition_matrix[prev_char][2]);
                        current_char = 2;
                    }
                    else if(ch == 'g'){
                        probability += log2(transition_matrix[prev_char][3]);
                        current_char = 3;
                    }
                }
                
            }
        }
        if(order == 2){
            printf("Order 2\n");
        }
        
        
    }
    
    //printf("\n");
    fclose(fp);    
    printf("The probability is:%f\n",probability);
    return 0;
}
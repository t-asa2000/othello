#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//turn black>white>black...

int cell[64];
int can_put_cell[];
int now_player,cpu,multiplay,exi = 0,can_put_cells;
//cell,now_player,cpu >>> black 1 white -1 no-stone("cell"only) 0
//cell[a] (x,y)...a(=(y-1)*8+(x-1)) >>> example: Top-left(1,1)... a = 0 Lower-right(8,8)... a = 63(=7*8+7)
//can_put_cell[b] = cell[a]



int cell_read(int x,int y){
    return cell[(y-1)*8+(x-1)];
}

void cell_write(int x,int y){
    cell[(y-1)*8+(x-1)] = now_player;
}

int cell_on_the_board(int x,int y){
    if((x > 0)||(x < 9)||(y > 0)||(y < 9)){
        return 1;
    }else{
        return 0;
    }
}

void can_put(){
    int i,x,y,i1 = 0;
    for(i = 0;i < 64;i++){
        if(cell[i] == now_player){
            //Top-left
            x = i % 8 + 1;
            y = i / 8 + 1;
            printf("%d,%d\n",x,y);
            do{
                x--;
                y--;
                i1++;
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player));
            if(!cell_read(x,y) && (i1 > 1)){
                can_put_cell[can_put_cells] = (y-1)*8+(x-1);
                can_put_cells++;
            }
            i1 = 0;
            //Top
            x = i % 8 + 1;
            y = i / 8 + 1;
            do{
                y--;
                i1++;
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player));
            if(!cell_read(x,y) && (i1 > 1)){
                can_put_cell[can_put_cells] = (y-1)*8+(x-1);
                can_put_cells++;
            }
            i1 = 0;
            //Top-right
            x = i % 8 + 1;
            y = i / 8 + 1;
            do{
                x++;
                y--;
                i1++;
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player));
            if(!cell_read(x,y) && (i1 > 1)){
                can_put_cell[can_put_cells] = (y-1)*8+(x-1);
                can_put_cells++;
            }
            i1 = 0;
            //Left
            x = i % 8 + 1;
            y = i / 8 + 1;
            do{
                x--;
                i1++;
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player));
            if(!cell_read(x,y) && (i1 > 1)){
                can_put_cell[can_put_cells] = (y-1)*8+(x-1);
                can_put_cells++;
            }
            i1 = 0;
            //Right
            x = i % 8 + 1;
            y = i / 8 + 1;
            do{
                x++;
                i1++;
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player));
            if(!cell_read(x,y) && (i1 > 1)){
                can_put_cell[can_put_cells] = (y-1)*8+(x-1);
                can_put_cells++;
            }
            i1 = 0;
            //Under-left
            x = i % 8 + 1;
            y = i / 8 + 1;
            do{
                x--;
                y++;
                i1++;
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player));
            if(!cell_read(x,y) && (i1 > 1)){
                can_put_cell[can_put_cells] = (y-1)*8+(x-1);
                can_put_cells++;
            }
            i1 = 0;
            //Under
            x = i % 8 + 1;
            y = i / 8 + 1;
            do{
                y++;
                i1++;
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player));
            if(!cell_read(x,y) && (i1 > 1)){
                can_put_cell[can_put_cells] = (y-1)*8+(x-1);
                can_put_cells++;
            }
            i1 = 0;
            //Under-right
            x = i % 8 + 1;
            y = i / 8 + 1;
            do{
                x++;
                y++;
                i1++;
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player));
            if(!cell_read(x,y) && (i1 > 1)){
                can_put_cell[can_put_cells] = (y-1)*8+(x-1);
                can_put_cells++;
            }
            i1 = 0;
        }
    }
    for(i = 0;i < can_put_cells;i++){
        x = can_put_cell[i] % 8 + 1;
        y = can_put_cell[i] / 8 + 1;
        printf("%d (%d,%d)\n",i,x,y);
    }
}

void two_byte_char(int a){
    switch(a){
        case 0:
            printf("０");
            break;
        case 1:
            printf("１");
            break;
        case 2:
            printf("２");
            break;
        case 3:
            printf("３");
            break;
        case 4:
            printf("４");
            break;
        case 5:
            printf("５");
            break;
        case 6:
            printf("６");
            break;
        case 7:
            printf("７");
            break;
        case 8:
            printf("８");
            break;
        case 9:
            printf("９");
            break;
        default:
            break;
    }
}

void board_print(){
    int x,y;
    printf("\n  １２３４５６７８\n");
    for(y = 1;y < 9;y++){
        two_byte_char(y);
        for(x = 1;x < 9;x++){
            switch(cell_read(x,y)){
                case 1:
                    printf("○");
                    break;
                case -1:
                    printf("●");
                    break;
                default:
                    printf("　");
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

int random(){ //return random number based on the time of now.
    srand((unsigned)time(NULL));
    return rand();
}

void user_turn(){
    board_print();
    can_put();
}

void cpu_turn(){

}

void game(){
    do{
        printf("0...一人で遊ぶ(CPUと遊ぶ),1...二人で遊ぶ>");
        scanf("%d",&multiplay);
    }while((multiplay < 0)||(multiplay > 1));
    if(!multiplay){
        if(random()%2){
            printf("\nあなたは先手です．\n");
        }else{
            cpu = 1;
            printf("\nあなたは後手です．\n");
        }
    }
    cell_write(5,4);
    cell_write(4,5);
    now_player *= -1;
    cell_write(4,4);
    cell_write(5,5);
    now_player *= -1;
    user_turn();
    /*while(1){
        now_player *= -1;
        if(now_player == cpu){
            cpu_turn();
        }else{
            user_turn();
        }
    }*/
}

int main(){
    while(!exi){
        int i;
        for(i = 0;i<64;i++){
            cell[i] = 0;
        }
        now_player = 1;
        cpu = -1;
        multiplay = 0;
        can_put_cells = 0;
        game();
        do{
            printf("0...もう一度遊ぶ,1...終了>");
            scanf("%d",&exi);
            printf("\n");
        }while((exi < 0)||(exi > 1));
    }
}
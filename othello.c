#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    【マスの位置の表現方法】
    座標形式：左上を(1,1)，右下を(8,8)とし(横(x),縦(y))の座標で表現
    要素番号形式：後述のcell配列の要素番号にも用いる．座標から求めるには
*/

//石（プレイヤー）
#define BLACK 1 //先手
#define WHITE -1 //後手
#define NO_STONE 0 //何も置かれていない
#define NOT_FOUND 2 //存在しないマス

//ゲームモード
#define SINGLE_PLAY 0 //CPU対戦
#define MULTI_PLAY 1 //人間同士での対戦

int cell[64]; //マスの状態を記録する配列
int can_put_cell[]; //現在のターンで石を置くことができるマスの位置をcell配列の要素番号で記録
int now_player,cpu,gamemode,can_put_cells;

int get_number(int x,int y){ //座標形式→要素番号変換
    return (y-1)*8+(x-1);
}

void get_position(int i,int *x,int *y){ //要素番号→座標形式変換
    *x = i % 8 + 1;
    *y = i / 8 + 1;
}

int cell_read(int x,int y){ //指定した座標のマスの状態を返す
    if((x > 0)&&(x < 9)&&(y > 0)&&(y < 9)) 
        return cell[get_number(x,y)];
    return NOT_FOUND;
}

void cell_write(int x,int y){ //指定した座標のマスに石を置く
    cell[get_number(x,y)] = now_player;
}

int cell_on_the_board(int x,int y){ //指定した座標のマスが存在するか返す
    if((x > 0)&&(x < 9)&&(y > 0)&&(y < 9)) 
        return 1;
    return 0;
}

void can_put_cell_delete(int no){
    if(no < can_put_cells-1){
        for(;no < can_put_cells-1;no++){
            can_put_cell[no] = can_put_cell[no+1];
        }
    }
    can_put_cells--;
}

void can_put(){ //石を置くことができるマスをスキャン
    int i,x,y,i1 = 0;
    int upper_left[64]={0};
    for(i = 0;i < 64;i++){
        if(cell[i] == now_player){ //自プレイヤーの石を検出
            get_position(i,&x,&y);
            printf("%d(%d,%d) %d\n",i,x,y,can_put_cells);
            //左上方向
            do{
                x--; 
                y--; //フォーカスするマスを一つ左上に移動
                i1++; //スキャン回数を増加
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player)); //フォーカス中のマスに相手の石がある場合スキャンを続行
            if(!cell_read(x,y) && (i1 > 1)){ //フォーカス中のマスに何も石が置いてなく，スキャン回数が2回以上
                can_put_cell[can_put_cells] = get_number(x,y); //位置を要素番号形式（上述）で記録
                upper_left[can_put_cells] = 
                can_put_cells++; //石が置くことができるマスの数を増加
            }
            i1 = 0; //スキャン回数のリセット
            get_position(i,&x,&y); //座標リセット
            //上方向
            do{
                y--; //フォーカスするマスを一つ上に移動
                i1++;
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player));
            if(!cell_read(x,y) && (i1 > 1)){
                can_put_cell[can_put_cells] = get_number(x,y);
                can_put_cells++;
            }
            i1 = 0;
            get_position(i,&x,&y);
            //右上方向
            do{
                x++;
                y--; //フォーカスするマスを一つ右上に移動
                i1++;
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player));
            if(!cell_read(x,y) && (i1 > 1)){
                can_put_cell[can_put_cells] = get_number(x,y);
                can_put_cells++;
            }
            i1 = 0;
            get_position(i,&x,&y);
            //左方向
            do{
                x--; //フォーカスするマスを一つ左に移動
                i1++;
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player));
            if(!cell_read(x,y) && (i1 > 1)){
                can_put_cell[can_put_cells] = get_number(x,y);
                can_put_cells++;
            }
            i1 = 0;
            get_position(i,&x,&y);
            //右方向
            do{
                x++; //フォーカスするマスを一つ右に移動
                i1++;
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player));
            if(!cell_read(x,y) && (i1 > 1)){
                can_put_cell[can_put_cells] = get_number(x,y);
                can_put_cells++;
            }
            i1 = 0;
            get_position(i,&x,&y);
            //左下方向
            do{
                x--;
                y++; //フォーカスするマスを一つ左下に移動
                i1++;
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player));
            if(!cell_read(x,y) && (i1 > 1)){
                can_put_cell[can_put_cells] = get_number(x,y);
                can_put_cells++;
            }
            i1 = 0;
            get_position(i,&x,&y);
            //下方向
            do{
                y++; //フォーカスするマスを一つ下に移動
                i1++;
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player));
            if(!cell_read(x,y) && (i1 > 1)){
                can_put_cell[can_put_cells] = get_number(x,y);
                can_put_cells++;
            }
            i1 = 0;
            get_position(i,&x,&y);
            //右下方向
            do{
                x++;
                y++; //フォーカスするマスを一つ右下に移動
                i1++;
            }while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player));
            if(!cell_read(x,y) && (i1 > 1)){
                can_put_cell[can_put_cells] = get_number(x,y);
                can_put_cells++;
            }
        }
    }
    //左上方向のスキャンの不具合が解決できないため，以下，応急措置．
    for(i=0;i<can_put_cells;i++){
        if(upper_left[i]){
            get_position(can_put_cell[i],&x,&y);
            if(cell_read(x+1,y+1)==now_player){
                printf("[Delete]%d,%d",x,y);
                can_put_cell_delete(i);
            }
        }
    }
    for(i=0;i<can_put_cells;i++){
        get_position(can_put_cell[i],&x,&y);
        int delete_flag = 1;
        for(i1=-1;i1<2;i1++){
            if(cell_read(x+i1,y)==-now_player){
                delete_flag = 0;
            }
        }     
        for(i1=-1;i1<2;i1++){
            if(cell_read(x,y+i1)==-now_player){
                delete_flag = 0;
            }
        }
        for(i1=-1;i1<2;i1++){
            if(cell_read(x+i1,y+i1)==-now_player){
                delete_flag = 0;
            }
        }
        for(i1=-1;i1<2;i1++){
            if(cell_read(x-i1,y+i1)==-now_player){
                delete_flag = 0;
            }
        }
        if(delete_flag){
            printf("[Delete]%d,%d",x,y);
            can_put_cell_delete(i);
            i--;
        }
    }
}

int attack(int i){ //攻撃(指定したマスに石を置き周りのマスも操作する)
    int x,y,i1 = 0;
    int x1[64]; //置き換えマスリスト(x座標)
    int y1[64]; //置き換えマスリスト(y座標)
    //要素数未定義ではコンパイルが通らなかったためマスの数である64に指定．
    if((i < 0)||(i >= can_put_cells)){
        return 1; //エラー
    }
    get_position(can_put_cell[i],&x,&y); //座標を取得
    //置けるかどうか確認する
    printf("%d(%d,%d) -> %d\n",i+1,x,y,cell[can_put_cell[i]]);
    if(cell[can_put_cell[i]]){
        return 1; //エラー
    }
    //指定マス
    cell[can_put_cell[i]] = now_player;
    //左上方向
    x--;
    y--; 
    while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player)){ //相手の石があるか
        x1[i1] = x;
        y1[i1] = y; //リスト追加
        i1++; //リスト個数を増加
        x--;
        y--;
    }
    if(cell_on_the_board(x,y)&&(cell_read(x,y) == now_player)){ //自分の石があるか(自分の石同士に挟まれているか)
        for(;i1;i1--){
            cell_write(x1[i1-1],y1[i1-1]);
        }
    }
    get_position(can_put_cell[i],&x,&y); //座標リセット
    i1 = 0; //リスト個数リセット
    //上方向
    y--; 
    while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player)){ //相手の石があるか
        x1[i1] = x;
        y1[i1] = y; //リスト追加
        i1++; //リスト個数を増加
        y--;
    }
    if(cell_on_the_board(x,y)&&(cell_read(x,y) == now_player)){ //自分の石があるか(自分の石同士に挟まれているか)
        for(;i1;i1--){
            cell_write(x1[i1-1],y1[i1-1]);
        }
    }
    get_position(can_put_cell[i],&x,&y); //座標リセット
    i1 = 0; //リスト個数リセット
    //右上方向
    x++;
    y--; 
    while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player)){ //相手の石があるか
        x1[i1] = x;
        y1[i1] = y; //リスト追加
        i1++; //リスト個数を増加
        x++;
        y--;
    }
    if(cell_on_the_board(x,y)&&(cell_read(x,y) == now_player)){ //自分の石があるか(自分の石同士に挟まれているか)
        for(;i1;i1--){
            cell_write(x1[i1-1],y1[i1-1]);
        }
    }
    get_position(can_put_cell[i],&x,&y); //座標リセット
    i1 = 0; //リスト個数リセット
    //左方向
    x--;
    while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player)){ //相手の石があるか
        x1[i1] = x;
        y1[i1] = y; //リスト追加
        i1++; //リスト個数を増加
        x--;
    }
    if(cell_on_the_board(x,y)&&(cell_read(x,y) == now_player)){ //自分の石があるか(自分の石同士に挟まれているか)
        for(;i1;i1--){
            cell_write(x1[i1-1],y1[i1-1]);
        }
    }
    get_position(can_put_cell[i],&x,&y); //座標リセット
    i1 = 0; //リスト個数リセット
    //右方向
    x++;
    while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player)){ //相手の石があるか
        x1[i1] = x;
        y1[i1] = y; //リスト追加
        i1++; //リスト個数を増加
        x++;
    }
    if(cell_on_the_board(x,y)&&(cell_read(x,y) == now_player)){ //自分の石があるか(自分の石同士に挟まれているか)
        for(;i1;i1--){
            cell_write(x1[i1-1],y1[i1-1]);
        }
    }
    get_position(can_put_cell[i],&x,&y); //座標リセット
    i1 = 0; //リスト個数リセット
    //左下方向
    x--;
    y++;
    while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player)){ //相手の石があるか
        x1[i1] = x;
        y1[i1] = y; //リスト追加
        i1++; //リスト個数を増加
        x--;
        y++;
    }
    if(cell_on_the_board(x,y)&&(cell_read(x,y) == now_player)){ //自分の石があるか(自分の石同士に挟まれているか)
        for(;i1;i1--){
            cell_write(x1[i1-1],y1[i1-1]);
        }
    }
    get_position(can_put_cell[i],&x,&y); //座標リセット
    i1 = 0; //リスト個数リセット
    //下方向
    y++;
    while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player)){ //相手の石があるか
        x1[i1] = x;
        y1[i1] = y; //リスト追加
        i1++; //リスト個数を増加
        y++;
    }
    if(cell_on_the_board(x,y)&&(cell_read(x,y) == now_player)){ //自分の石があるか(自分の石同士に挟まれているか)
        for(;i1;i1--){
            cell_write(x1[i1-1],y1[i1-1]);
        }
    }
    get_position(can_put_cell[i],&x,&y); //座標リセット
    i1 = 0; //リスト個数リセット
    //右下方向
    x++;
    y++;
    while(cell_on_the_board(x,y)&&(cell_read(x,y) == -now_player)){ //相手の石があるか
        x1[i1] = x;
        y1[i1] = y; //リスト追加
        i1++; //リスト個数を増加
        x++;
        y++;
    }
    if(cell_on_the_board(x,y)&&(cell_read(x,y) == now_player)){ //自分の石があるか(自分の石同士に挟まれているか)
        for(;i1;i1--){
            cell_write(x1[i1-1],y1[i1-1]);
        }
    }
    get_position(can_put_cell[i],&x,&y); //座標リセット
    i1 = 0; //リスト個数リセット
    return 0; //成功
}


void two_byte_char(int a){ //全角数字を出力
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

void board_print(){ //ターミナル上に盤面を出力
    int x,y,i;
    printf("\n  １２３４５６７８\n");
    for(y = 1;y < 9;y++){
        two_byte_char(y);
        for(x = 1;x < 9;x++){
            switch(cell_read(x,y)){
                case BLACK:
                    printf("○");
                    break;
                case WHITE:
                    printf("●");
                    break;
                default:
                    for(i = 0;i <= can_put_cells;i++){
                        if(i == can_put_cells){
                            printf("　");
                        }else if(can_put_cell[i] == get_number(x,y)){
                            if(i < 10){
                                two_byte_char(i+1); //0が紛らわしいので+1
                            }else{
                                printf("%d",i+1);
                            }
                            break;
                        }
                    }
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

int random(){ //乱数を返す
    srand((unsigned)time(NULL));
    return rand();
}

void user_turn(){ //ユーザー(人間)のターン
    int put,i=0;
    can_put();
    board_print();
    if(can_put_cells){
        do{
            printf("どこに石を置きますか?>");
            scanf("%d",&put);
            if(put < 1){
                return;
            }
        }while(attack(put-1)); //+1したのを元に戻す(347行目参照)．成功すれば0を返すためループ脱出．
        return;
    }else{
        printf("置けるマスがありません．\n");
    }   
}

void cpu_turn(){ //CPUのターン

}

void game(){
    do{
        printf("0...一人で遊ぶ(CPUと遊ぶ),1...二人で遊ぶ>");
        scanf("%d",&gamemode);
    }while((gamemode < 0)||(gamemode > 1)); //指定した選択肢以外の場合は再度質問
    if(gamemode == SINGLE_PLAY){
        if(random()%2){
            printf("\nあなたは先手です．\n");
        }else{
            cpu = BLACK;
            printf("\nあなたは後手です．\n");
        }
    }else{
        cpu = 0;
    }
    cell_write(5,4);
    cell_write(4,5);
    now_player *= -1; //プレイヤー交代
    cell_write(4,4);
    cell_write(5,5);
    while(1){
        now_player *= -1;
        switch (now_player){
            case BLACK:
                printf("○先手");
                break;
            case WHITE:
                printf("●後手");
                break;
            default:
                break;
        }
        if(now_player == cpu){
            printf("(CPU)の番です．\n");
            cpu_turn();
        }else{
            printf("の番です．\n");
            user_turn();
        }
        int i;
        for(i = 0;i < can_put_cells;i++){
            can_put_cell[i] = 64;
        }
        can_put_cells = 0; //置けるマスのリセット
    }
}

int main(){
    int exi = 0; //ゲームを終了するかどうか
    while(!exi){ 
        int i;
        for(i = 0;i<64;i++){
            cell[i] = 0;
        }
        //変数の初期化
        now_player = BLACK;
        cpu = WHITE;
        gamemode = SINGLE_PLAY;
        can_put_cells = 0;
        //新規ゲーム
        game();
        //ゲーム終了後
        do{
            printf("0...もう一度遊ぶ,1...終了>");
            scanf("%d",&exi);
            printf("\n");
        }while((exi < 0)||(exi > 1)); //指定された選択肢以外の場合は再度質問
    }
}
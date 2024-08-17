#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 7

void board(char board_grid[BOARD_SIZE][BOARD_SIZE]);
void print_board(char board_grid[7][7]);
int check_match(char board_grid[BOARD_SIZE][BOARD_SIZE],int,int,int);
void player_input(char board_grid[BOARD_SIZE][BOARD_SIZE], int*);
void findwinner(char board_grid[BOARD_SIZE][BOARD_SIZE],int);
void turnbit();

char current_player = 'O';
int bit = 0;
int played_position[9] = {0};
int position[] = {8,10,12,22,24,26,36,38,40};
int is_winner = 0;
char winner_player;

int main(){

  char board_grid[BOARD_SIZE][BOARD_SIZE];
  int move_count = 9;
 
  board(board_grid);
  while(move_count > 0){
    print_board(board_grid);
    player_input(board_grid, &move_count);
    system("clear");
    if(is_winner){
      print_board(board_grid);
      printf("Player %c is winner!\n",winner_player);
      return 0;
    }
  }
  print_board(board_grid);
  printf("Game is Draw!!\n");

  return 0;
}

void board(char board_grid[BOARD_SIZE][BOARD_SIZE]){

  for(int i = 0; i < BOARD_SIZE; i++){
    memset(board_grid[i],' ',BOARD_SIZE);
  }

  for(int i = 0; i < BOARD_SIZE; i++){
    board_grid[0][i] = '+';
    board_grid[i][BOARD_SIZE-1] = '+';
    board_grid[BOARD_SIZE-1][i] = '+';
    board_grid[i][0] = '+';
    board_grid[i][2] = '+';
    board_grid[i][4] = '+';
    board_grid[2][i] = '+';
    board_grid[4][i] = '+';

  }
}

void print_board(char board_grid[BOARD_SIZE][BOARD_SIZE]){
  for(int i = 0; i < BOARD_SIZE; i++){
    for(int j = 0; j < BOARD_SIZE; j++){
      printf("%c ",board_grid[i][j]);
    }
    printf("\n");
  }
}

void player_input(char board_grid[BOARD_SIZE][BOARD_SIZE], int* move_count){
  int pos;
  printf("Enter the positon you want to play 1-9\n");
  printf("Player Turn: %c\n",current_player);
  scanf("%d",&pos);
  
  if(pos < 1 || pos > 9 || played_position[pos-1] == 1){
    return ;
  }
  int index = position[pos - 1];
  played_position[pos - 1] = 1;
  board_grid[index/BOARD_SIZE][index%BOARD_SIZE] = current_player;
  findwinner(board_grid,pos - 1);
  *move_count++;
  turnbit();

}

void turnbit(){
  bit = bit ? 0 : 1;
  current_player = bit ? 'X' : 'O';
}

void findwinner(char board_grid[BOARD_SIZE][BOARD_SIZE],int index){

  // checking current position row
  
  if(index <= 2){
    if(check_match(board_grid,0,1,2)){
      is_winner = 1;
    }
  }else if(index <= 5){
    if(check_match(board_grid,3,4,5)){
      is_winner = 1;
    }
  }else if(index <= 8){
    if(check_match(board_grid,6,7,8)){
      is_winner = 1;
    }
  }

  // checking current position coloum

  if(index == 0 || index == 3 || index == 6){
    if(check_match(board_grid,0,3,6)){
      is_winner = 1;
    }
  }else if(index == 1 || index == 4 || index == 7){
    if(check_match(board_grid,1,4,6)){
      is_winner = 1;
    }
  }else if(index == 2 || index == 5 || index == 7){
    if(check_match(board_grid,2,5,8)){
      is_winner = 1;
    }
  }

  // checking diagonal of current position 

  if(index == 0 || index == 8){
    if(check_match(board_grid,0,4,8)){
      is_winner = 1;
    }
  }else if(index == 2 || index == 6){
    if(check_match(board_grid,2,4,6)){
      is_winner = 1;
    }
  }else if(index == 4){
    if(check_match(board_grid,0,4,8) || check_match(board_grid,2,4,6)){
      is_winner = 1;
    }
  }
  winner_player = current_player;
}


int check_match(char board_grid[BOARD_SIZE][BOARD_SIZE],int p1, int p2, int p3) {
    int pos1 = position[p1];
    int pos2 = position[p2];
    int pos3 = position[p3];
    char val1 = board_grid[pos1 / BOARD_SIZE][pos1 % BOARD_SIZE];
    char val2 = board_grid[pos2 / BOARD_SIZE][pos2 % BOARD_SIZE];
    char val3 = board_grid[pos3 / BOARD_SIZE][pos3 % BOARD_SIZE];
    return (val1 == val2 && val2 == val3);
}

#include <stdio.h>
#include <stdlib.h>

#define Board_size 3

void init(char board[Board_size][Board_size]);
void print_board(char board[Board_size][Board_size]);
int input_move(char board[Board_size][Board_size],char *players,int current_player);
int find_winner(char board[Board_size][Board_size],int current_player,int move);




int main(void){
  char board[Board_size][Board_size];
  char players[] = {'O','X'};
  int current_player = 0;
  int move_count = 0;
  int current_move;
  int is_winner;

  init(board);

  while(move_count < 9){
    print_board(board);
    current_move = input_move(board,players,current_player);
    is_winner = find_winner(board,current_player,current_move);

    if(is_winner != -1){
      break;
    }
    current_player = !current_player;
    move_count++;
    system("clear");
  }
  system("clear");
  print_board(board);

  if(is_winner == -1){
    printf("Game is Draw!!\n");
  }else{
    printf("Congraulation!! %c is winner\n",players[is_winner]);
  }

  return 0;
}

void init(char board[Board_size][Board_size]){
  for(int i = 0; i < Board_size; i++){
    for(int j = 0; j < Board_size; j++){
      board[i][j] = ' ';
    }
  }
}

void print_board(char board[Board_size][Board_size]){

  printf(" %c | %c | %c \n",board[0][0],board[0][1],board[0][2]);
  printf("------------\n");
  printf(" %c | %c | %c \n",board[1][0],board[1][1],board[1][2]);
  printf("------------\n");
  printf(" %c | %c | %c \n",board[2][0],board[2][1],board[2][2]);
}

int input_move(char board[Board_size][Board_size], char *players, int current_player ){
  int move;

  while(1){
    printf("Player %c Turn: Enter move (1-9)",players[current_player]);
    scanf("%d",&move);
    move -= 1;
    if(move >= 0 && move <= 8 && board[move/Board_size][move%Board_size] == ' '){
      board[move/Board_size][move%Board_size] = players[current_player];
      break;
    }
  }

  return move;
}

int find_winner(char board[Board_size][Board_size], int current_player, int move){

  if(board[move/Board_size][0] == board[move/Board_size][1] && board[move/Board_size][2] == board[move/Board_size][1] && board[move/Board_size][2] != ' '){
    return current_player;
  }
  
  if(board[0][move%Board_size] == board[1][move%Board_size] && board[1][move%Board_size] == board[2][move%Board_size] && board[2][move%Board_size] != ' '){
    return current_player;
  }

  if(move%2 == 0){
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] != ' '){
      return current_player;
    }

    if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] != ' '){
      return current_player;
    }
  }

  return -1;
}

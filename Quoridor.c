#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
//#include <ctime.h>
#include <time.h>
#include <string.h>

#define WallSize 15
#define BoardSize 31
char GameBoard[BoardSize][BoardSize];// THE MAIN BOARD GAME
char BoardCopy[BoardSize][BoardSize];// SOME THING LIKE GameBoard COPY OF MAIN BOARD
int PlayersPosition[4][2];// PLAYERS LOCATION IN MAIN BOARD
int PlayersWallCounter[4];// PlayersWallCounter: PLAYER WALL COUNTER
int WallsPosition[WallSize][WallSize]; // NUMBER OF WALLS IN THE SAME LOACTION // ARRAY START FROM 1
int IsBlockedTurn[4];// FOR SAVE THE NIMBER OF TURNS THAN PLAYER ARE BLOCKED
char player1[21];
char player2 [21];
char player3[21];
char player4[21];
bool IsRobot[4];// AN ARRAY TO SAVE THE NUMBER OF ROBOTS IN GAME // TRUE: ROBOT & FALSE: REAL PLAYER
int turn;
int n;// NUMBER OF DEMINSIONS
typedef enum {
  BLACK = 0,
  BLUE = 1,
  GREEN = 2,
  AQUA = 3,
  RED = 4,
  PURPLE = 5,
  YELLOW = 6,
  WHITE = 7,
  GRAY = 8,
  LIGHT_BLUE = 9,
  LIGHT_GREEN = 10,
  LIGHT_AQUA = 11,
  LIGHT_RED = 12,
  LIGHT_PURPLE = 13,
  LIGHT_YELLOW = 14,
  LIGHT_WHITE = 15
} ConsoleColors;

void setColor(const ConsoleColors foreground, const ConsoleColors background) {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  WORD color = (background << 4) + foreground;
  SetConsoleTextAttribute(consoleHandle, color);
}

void copy(char GameBoard[][BoardSize],char BoardCopy[][BoardSize], int UsedArray){
	int i,j    ;
	for (i=0;i<UsedArray;i++){
		for(j=0;j<UsedArray;j++){
			BoardCopy[i][j]=GameBoard[i][j];
		}
	}
	for(i=1;i<UsedArray;i+=2){
		for(j=1;j<UsedArray;j+=2){
			BoardCopy[i][j]='0';
		}
	}
}

/*void goxy(int x,int y){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorCoord;
	cursorCoord.x=y;
	cursorCoord.y=x;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);
}*/

void sleep(unsigned int mseconds){
	clock_t goal= mseconds +clock();
	while(goal>clock());
}

void clear(){
	system("cls");
}

void print(int UsedArray){
	int i,j;
	for(i=0;i<UsedArray;i++){
        for(j=0;j<UsedArray;j++){
            printf(" %c",GameBoard[i][j]);
        }
        printf("\n");
    }
}

void print2(int UsedArray){
	
	int i,j;
	for(i=0;i<UsedArray;i++){
        for(j=0;j<UsedArray;j++){
            printf(" %d",GameBoard[i][j]);
        }
        printf("\n");
    }
}

void winner(int *sw,int n){

	if(PlayersPosition[0][0]==2*n-1||PlayersPosition[1][1]==1||PlayersPosition[2][0]==1||PlayersPosition[3][1]==2*n-1){//2*n-1 baraye zoj va fard
		*sw=0;
		clear();
		printf("END OF THE LINE\n");
		sleep(5000);
		printf("HERE WE ARE...\n");
		sleep(3500);
		if(PlayersPosition[0][0]==2*n-1){
		printf("  **\n ****\n******\n %s WON THE MATCH\n",player1);
		}
		else if(PlayersPosition[1][1]==1){
		printf("  **\n ****\n******\n %s WON THE MATCH\n",player2);
		}
		else if(PlayersPosition[2][0]==1){
		printf("  **\n ****\n******\n %s WON THE MATCH\n",player3);
		}
		else{
		printf("  **\n ****\n******\n %s WON THE MATCH\n",player4);
		}
	}
}

void CanPlaceWall(char BoardCopy[][BoardSize], int r,int c ){// FOR one player
	
	if(BoardCopy[r][c]=='4'){
		return;
	}
	
	if(BoardCopy[r][c]=='0' ){// check TOP
		BoardCopy[r][c]='1';
		if(BoardCopy[r-1][c]!='*'){
			CanPlaceWall(BoardCopy,r-2,c);
		}
	}
	else if( BoardCopy[r][c]=='1'){ // check down
		BoardCopy[r][c]='2';
		if(BoardCopy[r+1][c]!='*'){
			CanPlaceWall(BoardCopy,r+2,c);
		}
	}
	else if( BoardCopy[r][c]=='2'){ // check RIGHT 
		BoardCopy[r][c]='3';
		if( BoardCopy[r][c+1]!='*'){
			CanPlaceWall(BoardCopy,r,c+2);
		}
	}
	else if( BoardCopy[r][c]=='3'){
		BoardCopy[r][c]='4';
		if(BoardCopy[r][c-1]!= '*'){
			CanPlaceWall(BoardCopy,r,c-2);
		}
	}
	
	CanPlaceWall(BoardCopy,r,c);
	
}

int CAN(char GameBoard[][BoardSize],char BoardCopy[][BoardSize]){
	
	int i,j;
	int UsedArray =2*n+1;
	int counter=0;
	bool can=false;
	
	copy(GameBoard,BoardCopy,UsedArray);
	CanPlaceWall(BoardCopy,PlayersPosition[0][0],PlayersPosition[0][1]);// FOR PLAYER 1
	for(j=1;j<UsedArray;j+=2){
		if(BoardCopy[2*n-1][j]=='4'){
			can =true;
		}
	}
	if(can){
		counter++;
		can=false;
	}
	
	
	copy(GameBoard,BoardCopy,UsedArray);// FOR PLAYER 2
	CanPlaceWall(BoardCopy,PlayersPosition[1][0],PlayersPosition[1][1]);
	for(i=1;i<UsedArray;i+=2){
		if(BoardCopy[i][1]=='4'){
			can=true;
		}
	}
	if(can){
		counter++;
		can=false;
	}
	
	copy(GameBoard,BoardCopy,UsedArray);// FOR PLAYER 3
	CanPlaceWall(BoardCopy,PlayersPosition[2][0],PlayersPosition[2][1]);
	for(j=1;j<UsedArray;j+=2){
		if(BoardCopy[1][j]=='4'){
			can=true;
		}
	}
	if(can){
		counter++;
		can= false;
	}
	
	copy(GameBoard,BoardCopy,UsedArray);// FOR PLAYER 4
	CanPlaceWall(BoardCopy,PlayersPosition[3][0],PlayersPosition[3][1]);
	for(i=1;i<UsedArray;i+=2){
		if(BoardCopy[i][2*n-1]=='4'){
			can=true;
		}
	}
	if(can){
		counter++;
		can=false;
	}
	
	if(counter==4){
		return 0; //SUCCESS
	}
	else {
		return 1; //OUT OF RULE
	}
}

int Wall(char GameBoard[][BoardSize],char BoardCopy[][BoardSize],int n,int wi,int wj, int hv){ //PLACE WALLS   . wi: WALL I & ... .hv: H OR V
	int i,j;
	int UsedArray=2*n+1;
	bool can = false ;
	if(wi>n-1|| wj >n-1){ // BEHINE SAZI SHAVAD
		return 1; //OUT OF RULE
	}
	if(wi<1||wj<1){
		return 1;//OUT OF RULE
	}
	if(hv!=1 && hv!=2){
		return 1;//OUT OF RULE
	}
	if(WallsPosition[wi][wj]==0){
		WallsPosition[wi][wj]=1;
	}
	else{// chahar raah por ast lotfan badan tamas begirid
		return 1; //OUT OF RULE
	}
	wi*=2;
	wj*=2;
	if(hv==1){// 1 mean: OFOGHI
		if(GameBoard[wi][wj-1]==42 ||GameBoard[wi][wj+1]==42){// CHAHAR RAH POR  AST LOTFAN BADAN TAMAS BEGIRID
			WallsPosition[wi/2][wj/2]=0;
			return 1; //OUT OF RULE
		}
		else{// build walls
			GameBoard[wi][wj-1]=42;
			GameBoard[wi][wj+1]=42;
			//return 0; //SUCCESS.
			if(CAN(GameBoard,BoardCopy)==0){
				return 0;//SUCCESS
			}
			else{
				GameBoard[wi][wj-1]='-';
				GameBoard[wi][wj+1]='-';
				WallsPosition[wi/2][wj/2]=0;
				return 1; // OUT OF RULE
			}
		}
	}
	else{// hv=2 AMOODI
		if(GameBoard[wi-1][wj]=='*' ||GameBoard[wi+1][wj]=='*' ){// CHAHAR RAH POR  AST LOTFAN BADAN TAMAS BEGIRID
			WallsPosition[wi/2][wj/2]=0;
			return 1;//OUT OF RULE
		}
		else{//build walls
			GameBoard[wi-1][wj]=42;
			GameBoard[wi+1][wj]=42;
			//return 0; //SUCCESS
			if(CAN(GameBoard,BoardCopy)==0){
				return 0;//SUCCESS
			}
			else{
				GameBoard[wi-1][wj]='|';
				GameBoard[wi+1][wj]='|';
				WallsPosition[wi/2][wj/2]=0;
				return 1; //OUT OF RULE
			}
		}
	}
}

int Move(char GameBoard[][BoardSize],int n,int nmove,int *I,int *J ){//li= last *I mean last location of player piece and n= number of Dimensions
	// Nmove : Where to move( number of move)
	int i,j;
	if(nmove==8|| nmove==2){
		if(nmove ==8){ // nmove =8 (up)
			if(GameBoard[*I-1][*J]== 205 || GameBoard[*I-1][*J]== 42){
				return 1; // OUT OF RULE
			}
			else{ // check the NEW LOCATION TO BE EMPTY
				if(GameBoard[*I-2][*J] =='0'){
					GameBoard[*I-2][*J] = GameBoard[*I][*J];
					GameBoard[*I][*J] = '0';
					*I-=2;
				}
				else{
					if(GameBoard[*I-3][*J]==42||GameBoard[*I-3][*J]== 205){
						return 1; //out of rule
					}
					else{
						if(GameBoard[*I-4][*J]=='0'){
						GameBoard[*I-4][*J]=GameBoard[*I][*J];
						GameBoard[*I][*J]='0';
						*I-=4;
						}
						else{
							if(GameBoard[*I-5][*J]=='*'){
								return 1;//OUT OF RULE 
							}
							else{
								if(GameBoard[*I-6][*J]=='0'){
									GameBoard[*I-6][*J]=GameBoard[*I][*J];
									GameBoard[*I][*J]='0';
									*I-=6;
								}
								else{
									if(GameBoard[*I-7][*J]=='*'){
										return 1;//OUT OF RULE
									}
									else{
										GameBoard[*I-8][*J]=GameBoard[*I][*J];
										GameBoard[*I][*J]='0';
										*I-=8;
									}
								}
							}
						}
					}
					//return 2;// MOHRE HARIF  (OUT OF RULE)
				}
			}
		}
		else{// nmove = 2 (down)
			if(GameBoard[*I+1][*J]== 205 || GameBoard[*I+1][*J] == 42){
				return 1;//OUT OF RULE
			}
			else{// check the NEW LOCATION TO BE EMPTY
				if(GameBoard[*I+2][*J] == '0'){
					GameBoard[*I+2][*J]= GameBoard[*I][*J];
					GameBoard[*I][*J] = '0';
					*I+=2;
				}
				else{
					i=*I+2;
					j=*J;
					if(GameBoard[*I+3][*J]==42||GameBoard[*I+3][*J]== 205){
						return 1; //out of rule
					}
					else{
						if(GameBoard[*I+4][*J]=='0'){
						GameBoard[*I+4][*J]=GameBoard[*I][*J];
						GameBoard[*I][*J]='0';
						*I+=4;
						}
						else{
							if(GameBoard[*I+5][*J]=='*'){
								return 1;//OUT OF RULE 
							}
							else{
								if(GameBoard[*I+6][*J]=='0'){
									GameBoard[*I+6][*J]=GameBoard[*I][*J];
									GameBoard[*I][*J]='0';
									*I+=6;
								}
								else{
									if(GameBoard[*I+7][*J]=='*'){
										return 1;//OUT OF RULE
									}
									else{
										GameBoard[*I+8][*J]=GameBoard[*I][*J];
										GameBoard[*I][*J]='0';
										*I+=8;
									}
								}
							}
						}
					}
					//return 2;// MOHRE HARIF (OUT OF RULE)
				}
			}
		}
		return 0;// SUCCESS MOVE.
	}
	else{
		if(nmove== 4){ // nmove = 4 (left)
			if(GameBoard[*I][*J-1]== 186 || GameBoard[*I][*J-1] == 42){
				return 1;//OUT OF RULE
			}
			else{ //check the NEW LOCATON TO BE EMPTY
				if(GameBoard[*I][*J-2] == '0'){
					GameBoard[*I][*J-2] = GameBoard[*I][*J];
					GameBoard[*I][*J] = '0';
					*J-=2;
				}
				else{
					i=*I;
					j=*J-2;
					if(GameBoard[*I][*J-3]== 42 || GameBoard[*I][*J-3]== 186 ){
						return 1;//out of rule
					}
					else{
						if(GameBoard[*I][*J-4]=='0'){
						GameBoard[*I][*J-4]=GameBoard[*I][*J];
						GameBoard[*I][*J]='0';
						*J-=4;
						}
						else{
							if(GameBoard[*I][*J-5]=='*'){
								return 1;//OUT OF RULE 
							}
							else{
								if(GameBoard[*I][*J-6]=='0'){
									GameBoard[*I][*J-6]=GameBoard[*I][*J];
									GameBoard[*I][*J]='0';
									*J-=6;
								}
								else{
									if(GameBoard[*I][*J-7]=='*'){
										return 1;//OUT OF RULE
									}
									else{
										GameBoard[*I][*J-8]=GameBoard[*I][*J];
										GameBoard[*I][*J]='0';
										*J-=8;
									}
								}
							}
						}
					}
					//return 2; // MOHRE HARIF (OUT OF RULE)
				}
			}
		}
		else{// nmove = 6 (right)
			if(GameBoard[*I][*J+1] == 186 || GameBoard[*I][*J+1] == 42){
				return 1; // OUT OF RULE
			}
			else{ // CHECK THE NEW LOACTION TO BE EMPTY
				if( GameBoard[*I][*J+2] == '0'){
					GameBoard[*I][*J+2] = GameBoard[*I][*J];
					GameBoard[*I][*J] = '0';
					*J+=2;
				}
				else{
					i=*I;
					j=*J+2;
					if(GameBoard[*I][*J+3]== 42 || GameBoard[*I][*J+3]== 186 ){
						return 1;//out of rule
					}
					else{
						if(GameBoard[*I][*J+4]=='0'){
						GameBoard[*I][*J+4]=GameBoard[*I][*J];
						GameBoard[*I][*J]='0';
						*J+=4;
						}
						else{
							if(GameBoard[*I][*J+5]=='*'){
								return 1;//OUT OF RULE 
							}
							else{
								if(GameBoard[*I][*J+6]=='0'){
									GameBoard[*I][*J+6]=GameBoard[*I][*J];
									GameBoard[*I][*J]='0';
									*J+=6;
								}
								else{
									if(GameBoard[*I][*J+7]=='*'){
										return 1;//OUT OF RULE
									}
									else{
										GameBoard[*I][*J+8]=GameBoard[*I][*J];
										GameBoard[*I][*J]='0';
										*J+=8;
									}
								}
							}
						}
					}
					//return 2; // MOHRE HARIF (OUT OF RULE)
				}
			}
		}
		return 0;
	}
}

void createboard(char GameBoard[][BoardSize],int UsedArray){
	int i,j;
    int rows=UsedArray;
    int cols=UsedArray;
    
    for ( i = 0; i < rows; i++) {
        for ( j = 0; j < cols; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
            	GameBoard[i][j]=42;
            }
            else{
            	GameBoard[i][j]='0';
			}
        }
    }
    for(i=1;i<UsedArray;i+=2){
    	for(j=2;j<UsedArray-1;j+=2){
    		GameBoard[i][j]='|';//amoodi
		}
	}
	for(j=1;j<UsedArray;j+=2){
    	for(i=2;i<UsedArray-1;i+=2){//ofoghi
    		GameBoard[i][j]='-';
		}
	}
	for(i=2;i<UsedArray-1;i+=2){
		for(j=2;j<UsedArray-1;j+=2){
			GameBoard[i][j]= '+';
		}
	}
}

void printb(int UsedArray){
	for(int i=0;i<UsedArray;i++){
		for(int j=0;j<UsedArray;j++){
			printf(" %c",BoardCopy[i][j]);
		}
		printf("\n");
	}
}

int Trip(int TripNumber){
	int UsedArray=2*n+1;
	if(TripNumber==1){// DELETE ALL THE WALLS
		createboard(GameBoard,UsedArray);
		for(int i=1;i<WallSize;i++){
			for(int j=1;j<WallSize;j++){
				WallsPosition[i][j]=0;
			}
		}
		GameBoard[PlayersPosition[0][0]][PlayersPosition[0][1]]='1';
		GameBoard[PlayersPosition[1][0]][PlayersPosition[1][1]]='2';
		GameBoard[PlayersPosition[2][0]][PlayersPosition[2][1]]='3';
		GameBoard[PlayersPosition[3][0]][PlayersPosition[3][1]]='4';
		printf("Bad NEWS! here we have an TRIP for you!\nAll The Walls Deleted!\a");
		sleep(6500);
		clear();
		print(UsedArray);
		return 0;
	}
	
	else if(TripNumber==2){ //  Decrease PLAYERS WALL
		int Number=rand()%3;
		if(Number==0) Number=2;
		else if(Number == 1) Number =3;
		else Number=5;
		if(turn%4==1){// player 1 turn
			PlayersWallCounter[0]-=Number;
			if(PlayersWallCounter[0]<0) PlayersWallCounter[0]=0;
			printf("Bad NEWS! here we have an TRIP for %s! Your walls DECREASED = -%d!\a\n",player1,Number);
		}
		else if(turn%4==2){//PLAYER 2 TURN
			PlayersWallCounter[1]-=Number;
			if(PlayersWallCounter[1]<0) PlayersWallCounter[1]=0;
			printf("Bad NEWS! here we have an TRIP for %s! Your walls DECREASED = -%d!\a\n",player2,Number);
		}
		else if(turn%4==3){ //PLAYER 3 TURN
			PlayersWallCounter[2]-=Number;
			if(PlayersWallCounter[2]<0) PlayersWallCounter[2]=0;
			printf("Bad NEWS! here we have an TRIP for %s! Your walls DECREASED = -%d!\a\n",player3,Number);
		}
		else{ // PLAYER 4 TURN
			PlayersWallCounter[3]-=Number;
			if(PlayersWallCounter[3]<0) PlayersWallCounter[3]=0;
			printf("Bad NEWS! here we have an TRIP for %s! Your walls DECREASED = -%d!\a\n",player4,Number);
		}
		sleep(6500);
		return 0;
	}
	
	else{ // BLOCK PLAYER FOR ONE OR TWO TURN
		int NumberOfBlock=rand()%2;
		if(NumberOfBlock==0) NumberOfBlock=2;
		
		if(turn%4==1){// player 1 turn
			IsBlockedTurn[0]=NumberOfBlock;
			if(IsBlockedTurn[0]>4) IsBlockedTurn[0]=4;
			printf("Bad NEWS! here we have an TRIP for %s! You have been BLOCKED for [%d] TURN!\a\n",player1,NumberOfBlock);
		}
		else if(turn%4==2){//PLAYER 2 TURN
			IsBlockedTurn[1]=NumberOfBlock;
			if(IsBlockedTurn[1]>4) IsBlockedTurn[1]=4;
			printf("Bad NEWS! here we have an TRIP for %s! You have been BLOCKED for [%d] TURN!\a\n",player2,NumberOfBlock);
		}
		else if(turn%4==3){ //PLAYER 3 TURN
			IsBlockedTurn[2]=NumberOfBlock;
			if(IsBlockedTurn[2]>4) IsBlockedTurn[2]=4;
			printf("Bad NEWS! here we have an TRIP for %s! You have been BLOCKED for [%d] TURN!\a\n",player3,NumberOfBlock);
		}
		else{ // PLAYER 4 TURN
			IsBlockedTurn[3]=NumberOfBlock;
			if(IsBlockedTurn[3]>4) IsBlockedTurn[3]=4;
			printf("Bad NEWS! here we have an TRIP for %s! You have been BLOCKED for [%d] TURN!\a\n",player4,NumberOfBlock);
		}
		turn++;
		sleep(7000);
		clear();
		return 0;
	}
}

int Gift(int GiftNumber){
	if(GiftNumber==1){
		int Number=rand()%3;
		if(Number==1) Number=3;
		else if(Number==0) Number=5;
		
		if(turn%4==1){// player 1 turn
			PlayersWallCounter[0]+=Number;
			if(PlayersWallCounter[0]>WallSize) PlayersWallCounter[0]=WallSize;
			printf("Good NEWS! Oww It's a GIFT for %s! Your walls +=%d!\a\n",player1,Number);
		}
		else if(turn%4==2){//PLAYER 2 TURN
			PlayersWallCounter[1]+=Number;
			if(PlayersWallCounter[1]>WallSize) PlayersWallCounter[1]=WallSize;
			printf("Good NEWS! Oww It's a GIFT for %s! Your walls +=%d!\a\n",player2,Number);
		}
		else if(turn%4==3){ //PLAYER 3 TURN
			PlayersWallCounter[2]+=Number;
			if(PlayersWallCounter[2]>WallSize) PlayersWallCounter[2]=WallSize;
			printf("Good NEWS! Oww It's a GIFT for %s! Your walls +=%d!\a\n",player3,Number);
		}
		else{ // PLAYER 4 TURN
			PlayersWallCounter[3]+=Number;
			if(PlayersWallCounter[3]>WallSize) PlayersWallCounter[3]=WallSize;
			printf("Good NEWS! Oww It's a GIFT for %s! Your walls +=%d!\a\n",player4,Number);
		}
		sleep(5500);
		return 0;
	}
	else{ // GIFTNUMBER 2
		int Number=rand()%2,counter=0;
		if(Number==0) Number =2;
		
		if(turn%4==1){// player 1 turn
			if(PlayersWallCounter[1]>0) {
				PlayersWallCounter[1]--;
				counter++;
			}
			if(PlayersWallCounter[2]>0) {
				PlayersWallCounter[2]--;
				counter++;
			}
			if(PlayersWallCounter[3]>0) {
				PlayersWallCounter[3]--;
				counter++;
			}
			PlayersWallCounter[0]+=counter;
			printf("Bad NEWS for All EXEPT %s! other Players gift you %d! Your walls +=%d!\a\n",player1,Number,counter);
		}
		else if(turn%4==2){//PLAYER 2 TURN
			if(PlayersWallCounter[0]>0) {
				PlayersWallCounter[0]--;
				counter++;
			}
			if(PlayersWallCounter[2]>0) {
				PlayersWallCounter[2]--;
				counter++;
			}
			if(PlayersWallCounter[3]>0) {
				PlayersWallCounter[3]--;
				counter++;
			}
			PlayersWallCounter[1]+=counter;
			printf("Bad NEWS for All EXEPT %s! other Players gift you %d! Your walls +=%d!\a\n",player2,Number,counter);
		}
		else if(turn%4==3){ //PLAYER 3 TURN
			if(PlayersWallCounter[1]>0) {
				PlayersWallCounter[1]--;
				counter++;
			}
			if(PlayersWallCounter[0]>0) {
				PlayersWallCounter[0]--;
				counter++;
			}
			if(PlayersWallCounter[3]>0) {
				PlayersWallCounter[3]--;
				counter++;
			}
			PlayersWallCounter[2]+=counter;
			printf("Bad NEWS for All EXEPT %s! other Players gift you %d! Your walls +=%d!\a\n",player3,Number,counter);
		}
		else{ // PLAYER 4 TURN
			if(PlayersWallCounter[1]>0) {
				PlayersWallCounter[1]--;
				counter++;
			}
			if(PlayersWallCounter[2]>0) {
				PlayersWallCounter[2]--;
				counter++;
			}
			if(PlayersWallCounter[0]>0) {
				PlayersWallCounter[0]--;
				counter++;
			}
			PlayersWallCounter[3]+=counter;
			printf("Bad NEWS for All EXEPT %s! other Players gift you %d! Your walls +=%d!\a\n",player4,Number,counter);
		}
		sleep(7000);
		return 0;
	}
}

void Spells(){
	if(rand()%2==1){ //  TIME TO USE TRIP
		Trip(rand()%3);
	}
	else{ // OWWW! ITS A GIFT
		Gift(rand()%2);
	}
}

int SaveGame(){
	int i,j;
	FILE *save;
	save= fopen("SAVE.dat","w+b");
	if(!save){
		perror("Can't Create File!\a\n");
		return 1;
	}
	int turn_n[2];// turn_n array is just for saving variebles in same array
	turn_n[0]=turn;
	turn_n[1]=n;
	
	size_t written=fwrite(PlayersWallCounter,sizeof(int),4,save);// PlayersWallCounter: PLAYERS WALL COUNTER
	if(written !=4){
		printf("eror writing PlayersWallCounter");
		return 1;
	}
	
	written=fwrite(turn_n,sizeof(int),2,save);
	if(written !=2){
		printf("eror writing PlayersWallCounter");
		return 1;
	}
	
	for(i=0;i<4;i++){//4 is rows of PlayersPosition
		written=fwrite(PlayersPosition[i],sizeof(int),2,save);
		if(written!=2){
			printf("eror writing PlayersPosition");
			return 1;
		}
	}
	
	written =fwrite(IsRobot,sizeof(bool),4,save);
	if(written!=4){
		printf("eror writing IsRobot");
		return 1;
	}
	
	written = fwrite(IsBlockedTurn,sizeof(int),4,save);
	if(written!=4){
		printf("eror writing IsBlockedTurn");
		return 1;
	}
	
	for(i=0;i<WallSize;i++){
		written=fwrite(WallsPosition[i],sizeof(int),WallSize,save);
		if(written!=WallSize){
			printf("eror writing WallsPosition");
			return 1;
		}
	}
	
	for(i=0;i<BoardSize;i++){
		written=fwrite(GameBoard[i],sizeof(char),BoardSize,save);
		if(written!=BoardSize){
			printf("eror writing GameBoard[][]");
			return 1;
		}
	}
	
	fputs(player1,save);
	fputc('\n',save);
	fputs(player2,save);
	fputc('\n',save);
	fputs(player3,save);
	fputc('\n',save);
	fputs(player4,save);
	fputc('\n',save);
	
	if(fclose(save)==EOF){
		perror("Can't Close File!\a\n");
		return 1;
	}
	return 0;
}

int LoadGame(){
	int i,j,len;
	FILE *load;
	load= fopen("SAVE.dat","r+b");
	if(!load){
		perror("Cant't open File!\a\n");
		return 1;
	}
	int turn_n[2];
	
	size_t readed=fread(PlayersWallCounter,sizeof(int),4,load);
	if(readed!=4){
		printf("eror reading PlayersWallCounter");
		return 1;
	}
	
	readed=fread(turn_n,sizeof(int),2,load);
	if(readed!=2){
		printf("eror reading tunr_n");
		return 1;
	}

	for(i=0;i<4;i++){// 4 is rows of PlayersPosition
		readed=fread(PlayersPosition[i],sizeof(int),2,load);
		if(readed!=2){
			printf("eror reading PlayersPosition");
			return 1;
		}
	}
	
	readed=fread(IsRobot,sizeof(bool),4,load);
	if(readed!=4){
		printf("eror reading IsRobot");
		return 1;
	}
	
	readed=fread(IsBlockedTurn,sizeof(int),4,load);
	if(readed!=4){
		printf("eror reading IsBlockedTurn");
		return 1;
	}
	
	for(i=0;i<WallSize;i++){
		readed=fread(WallsPosition[i],sizeof(int),WallSize,load);
		if(readed!=WallSize){
			printf("eror reading WallsPosition");
			return 1;
		}
	}
	
	for(i=0;i<BoardSize;i++){
		readed=fread(GameBoard[i],sizeof(char),BoardSize,load);
		if(readed!=BoardSize){
			printf("eror reading GameBoard[][]");
			return 1;
		}
	}
	
	fgets(player1,21,load);
	len=strlen(player1);
	player1[len-1]='\0';
	fgets(player2,21,load);
	len=strlen(player2);
	player2[len-1]='\0';
	fgets(player3,21,load);
	len=strlen(player3);
	player3[len-1]='\0';
	fgets(player4,21,load);
	len=strlen(player4);
	player4[len-1]='\0';
	
	turn= turn_n[0];
	n=turn_n[1];
	
	if(fclose(load)==EOF){
		perror("Cant't Close File!\a\n");
		return 1;
	}
	return 0;
}

int StartNewGame(int *wall){
	int UsedArray,Wall,i;
	if(IsRobot[0]==false){ //REAL PLAYER
		printf("Player 1 name: ");
		scanf("%s",player1);
	}
	else{
		strcpy(player1,"Alex");
	}
	
	if(IsRobot[1]==false){ //REAL PLAYER
		printf("Player 2 name: ");
		scanf("%s",player2);
	}	
	else{
		strcpy(player2,"Charlotte");
	}
		
	if(IsRobot[2]==false){ //REAL PLAYER
		printf("Player 3 name: ");
		scanf("%s",player3);
	}
	else{
		strcpy(player3,"Jia");
	}
	
	if(IsRobot[3]==false){ //REAL PLAYER
		printf("Player 4 name: ");
		scanf("%s",player4);
	}
	else{
		strcpy(player4,"Gabriel");
	}
	
	while(1){
		printf("Please enter number of Dimensions:\n");
		scanf("%d",&n);
		if(n>=3 && n<=25) break;
	}
	UsedArray=2*n+1;
	createboard(GameBoard,UsedArray);
	clear();
	print(UsedArray);
	
	// FIRST PLAYER	S POSITION	
	//zoj ya fard	
	if(n%2!=0){// fard
		GameBoard[1][n]='1';
		GameBoard[n][UsedArray-2]='2';
		GameBoard[UsedArray-2][n]='3';
		GameBoard[n][1]='4';
		PlayersPosition[0][0]=1;//row of player 1
		PlayersPosition[0][1]=n;//colms of player 1
		PlayersPosition[1][0]=n;//row of player 2
		PlayersPosition[1][1]=2*n-1;//PlayersPosition[1][1]
		PlayersPosition[2][0]=2*n-1;//row of player 3
		PlayersPosition[2][1]=n;//PlayersPosition[2][1]
		PlayersPosition[3][0]=n;//Rows player4
		PlayersPosition[3][1]=1;//PlayersPosition[3][1]
	}
	else{
		GameBoard[1][n-1]='1';
		GameBoard[n-1][UsedArray-2]='2';
		GameBoard[UsedArray-2][n-1]='3';
		GameBoard[n-1][1]='4';
		PlayersPosition[0][0]=1;//PlayersPosition[0][0]
		PlayersPosition[0][1]=n-1;//PlayersPosition[0][1]
		PlayersPosition[1][0]=n-1;//PlayersPosition[1][0]
		PlayersPosition[1][1]=2*n-1;//PlayersPosition[1][1]
		PlayersPosition[2][0]=2*n-1;//PlayersPosition[2][0]
		PlayersPosition[2][1]=n-1;//PlayersPosition[2][1]
		PlayersPosition[3][0]=n-1;//PlayersPosition[3][0]
		PlayersPosition[3][1]=1;//PlayersPosition[3][1]
	}
	for(i=0;i<WallSize;i++){// baraye por kardan satr va sotoone 0 om.
		WallsPosition[i][0]=1;
		WallsPosition[0][i]=1;
	}
	// i=0;
	while(1){
		printf("Please enter Number of Walls:");
		scanf("%d",&Wall);
		if(Wall>=1&&Wall<=20) break;
		else{
			printf("WRONG ANSWER!\n Enter again:\a ");
		}
	}
	*wall=Wall;
	PlayersWallCounter[0]=PlayersWallCounter[1]=PlayersWallCounter[2]=PlayersWallCounter[3]=Wall;// PLAYERS WALL COUNTER
	return 0;
}

/*int MainMenu(char){
	
}*/

void Loading(){
	int i,j;
	for(i=0;i<10;i++){
		printf("LOADING...[]");
	}
}

int main()
{   
	srand(time(NULL));
	printf("Welcome to Iran\n");
	//printf("%d",rand());
	//printf("\n%d",rand());

    int UsedArray,i,j,rows,cols;
    int wall, wmove, plan, random,random2, random3;
    int swWIN=1,swWall=1,sw=1, swBlocked=1,sw2, swRobot=0,swSucs;
	int r,c;
	int NewGame, BotGame;
	int wi,wj,hv; // wall location & ofoghi ya amoodi
	bool CanSave=false;
	IsRobot[0]=IsRobot[1]=IsRobot[2]=IsRobot[3]=false;
	IsBlockedTurn[0]=IsBlockedTurn[1]=IsBlockedTurn[2]=IsBlockedTurn[3]=0;
	turn=1;
	// LOADING ...

	clear();
	printf("\n   MAIN MENU\n\n\n   *New Game: 1\n\n   *Load Game: 2\n    : ");
	scanf("%d",&NewGame);
	while(1){
		if(NewGame==1) {// NEW GAME
			clear();
			
			printf("\n   *Play With ROBOTS: 1\n\n   *PLAY UR OWN: 2\n    : ");
			scanf("%d",&BotGame);
			while(1){
				if(BotGame==1){// YES, PLAY WITH ROBOTS
					IsRobot[1]=true;
					IsRobot[2]=true;
					IsRobot[3]=true;
					clear();
					break;
				}
				else if(BotGame==2){ // NO, PLAY WITHOUT ROBOTS
					
					// EXCEPT 2PLAYER MODE
					break;
				}
				printf("WORNG\aENTER 1 FOR PLAY WITH BOTS or ENTER 2 FOR PLAY YOUR OWN\nPLEASE ENTER AGAIN:\n");
				scanf("%d",&BotGame);
			}			
			break;
		}
		else if(NewGame==2){// LOAD GAME
			clear();
			if(LoadGame()==0){
				UsedArray=2*n+1;
				printf("Loaded Successfully!\n");
				sleep(3000);
				clear();
			}
			else{
				printf("File Did'n open Successfully!\a\n");
			}
			
			break;
		}
		printf("Worng!\a \nEnter 1 for New Game or 2 for Load Game:\n");
		scanf("%d",&NewGame);
	}

	if(NewGame==1){
		if(IsRobot[0]==false){ //REAL PLAYER
			printf("Player 1 name: ");
			scanf("%s",player1);
		}
		else{
			strcpy(player1,"Alex");
		}
		
		if(IsRobot[1]==false){ //REAL PLAYER
			printf("Player 2 name: ");
			scanf("%s",player2);
		}	
		else{
			strcpy(player2,"Charlotte");
		}
			
		if(IsRobot[2]==false){ //REAL PLAYER
			printf("Player 3 name: ");
			scanf("%s",player3);
		}
		else{
			strcpy(player3,"Jia");
			}
		
		if(IsRobot[3]==false){ //REAL PLAYER
			printf("Player 4 name: ");
			scanf("%s",player4);
		}
		else{
			strcpy(player4,"Gabriel");
		}
		
		while(1){
			printf("Please enter number of Dimensions:\n");
			scanf("%d",&n);
			if(n>=3 && n<=25) break;
		}
		UsedArray=2*n+1;
		createboard(GameBoard,UsedArray);
		clear();
		print(UsedArray);
		
		// FIRST PLAYER	S POSITION	
		//zoj ya fard	
		if(n%2!=0){// fard
			GameBoard[1][n]='1';
			GameBoard[n][UsedArray-2]='2';
			GameBoard[UsedArray-2][n]='3';
			GameBoard[n][1]='4';
			PlayersPosition[0][0]=1;//row of player 1
			PlayersPosition[0][1]=n;//colms of player 1
			PlayersPosition[1][0]=n;//row of player 2
			PlayersPosition[1][1]=2*n-1;//PlayersPosition[1][1]
			PlayersPosition[2][0]=2*n-1;//row of player 3
			PlayersPosition[2][1]=n;//PlayersPosition[2][1]
			PlayersPosition[3][0]=n;//Rows player4
			PlayersPosition[3][1]=1;//PlayersPosition[3][1]
		}
		else{
			GameBoard[1][n-1]='1';
			GameBoard[n-1][UsedArray-2]='2';
			GameBoard[UsedArray-2][n-1]='3';
			GameBoard[n-1][1]='4';
			PlayersPosition[0][0]=1;//PlayersPosition[0][0]
			PlayersPosition[0][1]=n-1;//PlayersPosition[0][1]
			PlayersPosition[1][0]=n-1;//PlayersPosition[1][0]
			PlayersPosition[1][1]=2*n-1;//PlayersPosition[1][1]
			PlayersPosition[2][0]=2*n-1;//PlayersPosition[2][0]
			PlayersPosition[2][1]=n-1;//PlayersPosition[2][1]
			PlayersPosition[3][0]=n-1;//PlayersPosition[3][0]
			PlayersPosition[3][1]=1;//PlayersPosition[3][1]
		}
		for(i=0;i<WallSize;i++){// baraye por kardan satr va sotoone 0 om.
			WallsPosition[i][0]=1;
			WallsPosition[0][i]=1;
		}
		// i=0;
		while(1){
			printf("Please enter Number of Walls:");
			scanf("%d",&wall);
			if(wall>=1&&wall<=20) break;
			else{
				printf("WRONG ANSWER!\n Enter again:\a ");
			}
		}
		PlayersWallCounter[0]=PlayersWallCounter[1]=PlayersWallCounter[2]=PlayersWallCounter[3]=wall;// PLAYERS WALL COUNTER
	}
	
	while(swWIN==1){
		clear();
		while(swBlocked){// WHILE find a UnBLOCKED PLAYER
			if(turn%4==1){// player 1 turn
				if(IsBlockedTurn[0]!=0){// PLAYER IS BLOCKED
					turn++;
					IsBlockedTurn[0]--;
				}
				else{
					r=PlayersPosition[0][0];
					c=PlayersPosition[0][1];
					setColor(3,0);
					printf("%s's turn / Walls: %d / TURN:[%d]\n",player1,PlayersWallCounter[0],turn);
					if(turn%7==0){
						Spells();
					}
					if(IsRobot[0]){
						swRobot=1;
					}
					swBlocked=0;
				}
			}
			if(turn%4==2){//PLAYER 2 TURN
				if(IsBlockedTurn[1]!=0){// PLAYER IS BLOCKED
					turn++;
					IsBlockedTurn[1]--;
					}
				else{
					r=PlayersPosition[1][0];
					c=PlayersPosition[1][1];
					setColor(5,0);
					printf("%s's turn / Walls: %d / TURN:[%d]\n",player2,PlayersWallCounter[1],turn);
					if(turn%7==0){
						Spells();
					}
					if(IsRobot[1]){
						swRobot=1;
					}
					swBlocked=0;
				}
			}
			if(turn%4==3){ //PLAYER 3 TURN
				if(IsBlockedTurn[2]!=0){// PLAYER IS BLOCKED
					turn++;
					IsBlockedTurn[2]--;
				}
				else{
					r=PlayersPosition[2][0];
					c=PlayersPosition[2][1];
					setColor(8,0);
					printf("%s's turn / Walls: %d / TURN:[%d]\n",player3,PlayersWallCounter[2],turn);
					if(turn%7==0){
						Spells();
					}
					if(IsRobot[2]){
						swRobot=1;
					}
					swBlocked=0;
				}
			}
			if(turn%4==0){ // PLAYER 4 TURN
				if(IsBlockedTurn[3]!=0){// PLAYER IS BLOCKED
					turn++;
					IsBlockedTurn[3]--;
				}
				else{
					r=PlayersPosition[3][0];
					c=PlayersPosition[3][1];
					setColor(2,0);
					printf("%s's turn / Walls: %d / TURN:[%d]\n",player4,PlayersWallCounter[3],turn);
					if(turn%7==0){
						Spells();
					}
					if(IsRobot[3]){
						swRobot=1;
					}
					swBlocked=0;
				}
			}
		}
		print(UsedArray);
		
		if(swRobot==0){// real player's turn
			printf("What's the plan?\nMOVE (1) Or WALL (2)? (10) For SAVE & QUIT: ");
			while(1){
				scanf("%d",&plan);
				if(plan==10){
						SaveGame();
						exit(0);
					}
				if(plan==1||plan==2) break;
				else{printf("Wrong plan\a Enter again. 10 For SAVE & QUIT:\n");
				}
			}
			if(plan==1){ // move
				printf("Enter number of move up(8) Or down(2) Or left(4) Or right(6):\n10 For SAVE & QUIT: ");
				while(1){
					scanf("%d",&wmove);
					if(wmove==10){
						SaveGame();
						exit(0);
					}
					if(wmove==8||wmove==2||wmove==4||wmove==6) break;
					printf("Wrong MOVE\a enter again. 10 For SAVE & QUIT:\n");
				}
				while(1){
					if(Move( GameBoard ,n,wmove,&r,&c)==1){// "1" mean: can't move to that location (OUT OF RULE)
						printf("out of rule\a Enter another:");
						scanf("%d",&wmove);
					}
					else {// SUCCESS MOVE
						if(turn%4==1){ // LAYER 1 TURN
							PlayersPosition[0][0]=r;
							PlayersPosition[0][1]=c;
						}
						else if(turn%4==2){// PLAYER 2 TURN
							PlayersPosition[1][0]=r;
							PlayersPosition[1][1]=c;
						}
						else if(turn%4==3){//PLAYER 3 TURN
							PlayersPosition[2][0]=r;
							PlayersPosition[2][1]=c;
						}
						else{// PLAYER 4 TURN
							PlayersPosition[3][0]=r;
							PlayersPosition[3][1]=c;
						}
						clear();
						print(UsedArray);
						break;
					}
				}
				
				winner(&swWIN,n);
			}
			else if(plan==2){// wall
				while(swWall){// baraye break bad az gozashtan wall
					if(PlayersWallCounter[0]==0||PlayersWallCounter[1]==0){// one of players have no wall...
						if(turn%4==1&& PlayersWallCounter[0]==0){
							printf("you have not enogh wall\a\nplease move\n");
							turn--;
							break;
						}
						else if(turn%4==2&& PlayersWallCounter[1]==0){
							printf("U have not enogh wall\a\nplease move\n");
							turn--;
							break;
						}
					}
					else if(PlayersWallCounter[2]==0||PlayersWallCounter[3]==0){
						if(turn%4==3&&PlayersWallCounter[2]==0){
							printf("YOU HAVE NOT ENOGH WALL\a\nPLEASE MOVE\n");
							turn--;
							break;
						}
						else if(turn%4==0&&PlayersWallCounter[3]==0){
							printf("U HAVE NOT ENOGH WALL\a\nPLEASE MOVE\n");
							turn--;
							break;
						}
					}
					printf("Please enter location of FORWAY (4 raah) :)\nenter i,j\nAND h (1) OR v (2) OR 10 For SAVE & QUIT: ");
					scanf("%d %d %d",&wi,&wj,&hv);
					if(hv==10){
						SaveGame();
						exit(0);
					}
					while(1){
						if( Wall(GameBoard,BoardCopy,n,wi,wj,hv)==1){
							printf("out of RULE, enter again:\a\nEnteri,j AND h(1) or v(2) Or 10 for SAVE & QUIT");
							scanf("%d %d %d",&wi,&wj,&hv);
							if(hv==10){
								SaveGame();
								exit(0);
							}
						}
						else{// SUCCESS
							if(turn%4==1){
								PlayersWallCounter[0]--;
							}
							else if(turn%4==2){
								PlayersWallCounter[1]--;
							}
							else if(turn%4==3){
								PlayersWallCounter[2]--;
							}
							else{
								PlayersWallCounter[3]--;
							}
								//setColor(4,0);
							swWall=0;//
							break;
						}
					}
				}
				//swWall=1;
			}
		}
		else{//   ROBOT'S TURN
			sleep(2000);
			// random plan
			if(rand()%2==1){// MOVE
				plan=1;
				while(1){
					random=rand()%4;
					if(random==1) wmove=8;
					else if(random==2) wmove=2;
					else if(random==3) wmove=4;
					else if(random==0)wmove=6;
					if(Move( GameBoard ,n,wmove,&r,&c)==0){ // SUCCESS MOVED.
						if(turn%4==1){
							PlayersPosition[0][0]=r;
							PlayersPosition[0][1]=c;
						}
						else if(turn%4==2){
							PlayersPosition[1][0]=r;
							PlayersPosition[1][1]=c;
						}
						else if(turn%4==3){
							PlayersPosition[2][0]=r;
							PlayersPosition[2][1]=c;
						}
						else {
							PlayersPosition[3][0]=r;
							PlayersPosition[3][1]=c;
						}
						break;
					}
				}
				// BASTE BE TURN PlayersPosition[0][0] PlayersPosition[0][1] .....
				
				winner(&swWIN,n);
			}
			else{// WALL
				plan=2;
				if(turn%4==1&&PlayersWallCounter[0]==0){
					turn--;
					swSucs=0;
				}
				else if(turn%4==2&&PlayersWallCounter[1]==0){
					turn --;
					swSucs=0;
				}
				else if(turn%4==3&&PlayersWallCounter[2]==0){
					turn--;
					swSucs=0;
				}
				else if(PlayersWallCounter[3]==0){
					turn--;
					swSucs=0;
				}
				while(swSucs){
					random=rand()%n;
					random2=rand()%n;
					if(WallsPosition[random][random2]==0){
						while(1){
							random3=rand()%3;
							if(random3==0)random3++;
							if( Wall(GameBoard,BoardCopy,n,random,random2,random3)==0){
								if(turn%4==1) PlayersWallCounter[0]--;
								else if(turn%4==2) PlayersWallCounter[1]--;
								else if( turn%4==3) PlayersWallCounter[2]--;
								else PlayersWallCounter[3]--;
								swSucs=0;
								break;
							}
						}
					}
				}
			}
		}
		turn++;// PLAYERS TURN
		swWall=1;
		swSucs=1;
		swRobot=0;
		swBlocked=1;
	}
	
	return 0;
}
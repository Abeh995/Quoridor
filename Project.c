#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
//#include <ctime.h>
#include <time.h>
#include <string.h>

#define wallsize 15 

char A[100][100];
char B[100][100];
int playloc[2][4];
int walloc[wallsize][wallsize]; // jahat zakhire charRah ha // ARRAY START FROM 1

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

void print(int m){
	int i,j;
	for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            printf(" %c",A[i][j]);
        }
        printf("\n");
    }
}

void print2(int m){
	
	int i,j;
	for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            printf(" %d",A[i][j]);
        }
        printf("\n");
    }
}

void winner(int *sw,int n,char player1,char player2,char player3,char player4,int r1,int c2,int r3,int c4){

	if(r1==2*n-1||c2==1||r3==1||c4==2*n-1){//2*n-1 baraye zoj va fard
		*sw=0;
		clear();
		printf("END OF THE LINE\n");
		sleep(5000);
		printf("HERE WE ARE...\n");
		sleep(3500);
		if(r1==2*n-1){
		printf("  **\n ****\n******\n %s WON THE MATCH\n",player1);
		}
		else if(c2==1){
		printf("  **\n ****\n******\n %s WON THE MATCH\n",player2);
		}
		else if(r3==1){
		printf("  **\n ****\n******\n %s WON THE MATCH\n",player3);
		}
		else{
		printf("  **\n ****\n******\n %s WON THE MATCH\n",player4);
		}
	}
}

void canwall(char B[][100], int n, int r,int c ){// FOR PLAYER 1
	
	if(B[r][c]=='4'){
		return;
	}
	
	if(B[r][c]=='0' ){// check TOP
		B[r][c]='1';
		if(B[r-1][c]!='*'){
			canwall(B,n,r-2,c);
		}
	}
	else if( B[r][c]=='1'){ // check down
		B[r][c]='2';
		if(B[r+1][c]!='*'){
			canwall(B,n,r+2,c);
		}
	}
	else if( B[r][c]=='2'){ // check RIGHT 
		B[r][c]='3';
		if( B[r][c+1]!='*'){
			canwall(B,n,r,c+2);
		}
	}
	else if( B[r][c]=='3'){
		B[r][c]='4';
		if(B[r][c-1]!= '*'){
			canwall(B,n,r,c-2);
		}
	}
	
	canwall(B,n,r,c);
	
}

int CAN(char A[][100],char B[][100],int n,int r1,int c1,int r2,int c2,int r3,int c3,int r4,int c4){
	
	int i,j;
	int m =2*n+1;
	int counter=0;
	bool can=false;
	
	copy(A,B,m);
	canwall(B,n,r1,c1);// FOR PLAYER 1
	for(j=1;j<m;j+=2){
		if(B[2*n-1][j]=='4'){
			can =true;
		}
	}
	if(can){
		counter++;
		can=false;
	}
	
	copy(A,B,m);// FOR PLAYER 2
	canwall(B,n,r2,c2);
	for(i=1;i<m;i+=2){
		if(B[i][1]=='4'){
			can=true;
		}
	}
	if(can){
		counter++;
		can=false;
	}
	
	copy(A,B,m);// FOR PLAYER 3
	canwall(B,n,r3,c3);
	for(j=1;j<m;j+=2){
		if(B[1][j]=='4'){
			can=true;
		}
	}
	if(can){
		counter++;
		can= false;
	}
	
	copy(A,B,m);// FOR PLAYER 4
	canwall(B,n,r4,c4);
	for(i=1;i<m;i+=2){
		if(B[i][2*n-1]=='4'){
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

int Wall(char A[][100],char B[][100],int n,int wi,int wj, int hv,int r1,int c1,int r2,int c2,int r3,int c3,int r4,int c4){ //PLACE WALLS   . wi: WALL I & ... .hv: H OR V
	int i,j;
	int m=2*n+1;
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
	if(walloc[wi][wj]==0){
		walloc[wi][wj]=1;
	}
	else{// chahar raah por ast lotfan badan tamas begirid
		return 1; //OUT OF RULE
	}
	wi*=2;
	wj*=2;
	if(hv==1){// 1 mean: OFOGHI
		if(A[wi][wj-1]==42 ||A[wi][wj+1]==42){// CHAHAR RAH POR  AST LOTFAN BADAN TAMAS BEGIRID
			walloc[wi/2][wj/2]=0;
			return 1; //OUT OF RULE
		}
		else{// build walls
			A[wi][wj-1]=42;
			A[wi][wj+1]=42;
			//return 0; //SUCCESS.
			if(CAN(A,B,n,r1,c1,r2,c2,r3,c3,r4,c4)==0){
				return 0;//SUCCESS
			}
			else{
				A[wi][wj-1]='-';
				A[wi][wj+1]='-';
				walloc[wi/2][wj/2]=0;
				return 1; // OUT OF RULE
			}
		}
	}
	else{// hv=2 AMOODI
		if(A[wi-1][wj]=='*' ||A[wi+1][wj]=='*' ){// CHAHAR RAH POR  AST LOTFAN BADAN TAMAS BEGIRID
			walloc[wi/2][wj/2]=0;
			return 1;//OUT OF RULE
		}
		else{//build walls
			A[wi-1][wj]=42;
			A[wi+1][wj]=42;
			//return 0; //SUCCESS
			if(CAN(A,B,n,r1,c1,r2,c2,r3,c3,r4,c4)==0){
				return 0;//SUCCESS
			}
			else{
				A[wi-1][wj]='|';
				A[wi+1][wj]='|';
				walloc[wi/2][wj/2]=0;
				return 1; //OUT OF RULE
			}
		}
	}
}

int Move(char A[][100],int n,int nmove,int *I,int *J ){//li= last *I mean last location of player piece and n= number of Dimensions
	// Nmove : Where to move( number of move)
	int i,j;
	if(nmove==8|| nmove==2){
		if(nmove ==8){ // nmove =8 (up)
			if(A[*I-1][*J]== 205 || A[*I-1][*J]== 42){
				return 1; // OUT OF RULE
			}
			else{ // check the NEW LOCATION TO BE EMPTY
				if(A[*I-2][*J] =='0'){
					A[*I-2][*J] = A[*I][*J];
					A[*I][*J] = '0';
					*I-=2;
				}
				else{
					if(A[*I-3][*J]==42||A[*I-3][*J]== 205){
						return 1; //out of rule
					}
					else{
						if(A[*I-4][*J]=='0'){
						A[*I-4][*J]=A[*I][*J];
						A[*I][*J]='0';
						*I-=4;
						}
						else{
							if(A[*I-5][*J]=='*'){
								return 1;//OUT OF RULE 
							}
							else{
								if(A[*I-6][*J]=='0'){
									A[*I-6][*J]=A[*I][*J];
									A[*I][*J]='0';
									*I-=6;
								}
								else{
									if(A[*I-7][*J]=='*'){
										return 1;//OUT OF RULE
									}
									else{
										A[*I-8][*J]=A[*I][*J];
										A[*I][*J]='0';
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
			if(A[*I+1][*J]== 205 || A[*I+1][*J] == 42){
				return 1;//OUT OF RULE
			}
			else{// check the NEW LOCATION TO BE EMPTY
				if(A[*I+2][*J] == '0'){
					A[*I+2][*J]= A[*I][*J];
					A[*I][*J] = '0';
					*I+=2;
				}
				else{
					i=*I+2;
					j=*J;
					if(A[*I+3][*J]==42||A[*I+3][*J]== 205){
						return 1; //out of rule
					}
					else{
						if(A[*I+4][*J]=='0'){
						A[*I+4][*J]=A[*I][*J];
						A[*I][*J]='0';
						*I+=4;
						}
						else{
							if(A[*I+5][*J]=='*'){
								return 1;//OUT OF RULE 
							}
							else{
								if(A[*I+6][*J]=='0'){
									A[*I+6][*J]=A[*I][*J];
									A[*I][*J]='0';
									*I+=6;
								}
								else{
									if(A[*I+7][*J]=='*'){
										return 1;//OUT OF RULE
									}
									else{
										A[*I+8][*J]=A[*I][*J];
										A[*I][*J]='0';
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
			if(A[*I][*J-1]== 186 || A[*I][*J-1] == 42){
				return 1;//OUT OF RULE
			}
			else{ //check the NEW LOCATON TO BE EMPTY
				if(A[*I][*J-2] == '0'){
					A[*I][*J-2] = A[*I][*J];
					A[*I][*J] = '0';
					*J-=2;
				}
				else{
					i=*I;
					j=*J-2;
					if(A[*I][*J-3]== 42 || A[*I][*J-3]== 186 ){
						return 1;//out of rule
					}
					else{
						if(A[*I][*J-4]=='0'){
						A[*I][*J-4]=A[*I][*J];
						A[*I][*J]='0';
						*J-=4;
						}
						else{
							if(A[*I][*J-5]=='*'){
								return 1;//OUT OF RULE 
							}
							else{
								if(A[*I][*J-6]=='0'){
									A[*I][*J-6]=A[*I][*J];
									A[*I][*J]='0';
									*J-=6;
								}
								else{
									if(A[*I][*J-7]=='*'){
										return 1;//OUT OF RULE
									}
									else{
										A[*I][*J-8]=A[*I][*J];
										A[*I][*J]='0';
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
			if(A[*I][*J+1] == 186 || A[*I][*J+1] == 42){
				return 1; // OUT OF RULE
			}
			else{ // CHECK THE NEW LOACTION TO BE EMPTY
				if( A[*I][*J+2] == '0'){
					A[*I][*J+2] = A[*I][*J];
					A[*I][*J] = '0';
					*J+=2;
				}
				else{
					i=*I;
					j=*J+2;
					if(A[*I][*J+3]== 42 || A[*I][*J+3]== 186 ){
						return 1;//out of rule
					}
					else{
						if(A[*I][*J+4]=='0'){
						A[*I][*J+4]=A[*I][*J];
						A[*I][*J]='0';
						*J+=4;
						}
						else{
							if(A[*I][*J+5]=='*'){
								return 1;//OUT OF RULE 
							}
							else{
								if(A[*I][*J+6]=='0'){
									A[*I][*J+6]=A[*I][*J];
									A[*I][*J]='0';
									*J+=6;
								}
								else{
									if(A[*I][*J+7]=='*'){
										return 1;//OUT OF RULE
									}
									else{
										A[*I][*J+8]=A[*I][*J];
										A[*I][*J]='0';
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

void createboard(char A[][100],int m){
	int i,j;
    int rows=m;
    int cols=m;
    
    for ( i = 0; i < rows; i++) {
        for ( j = 0; j < cols; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
            	A[i][j]=42;
            }
            else{
            	A[i][j]='0';
			}
        }
    }
    for(i=1;i<m;){
    	for(j=2;j<m-1;){
    		A[i][j]='|';//amoodi
    		j+=2;
		}
    	i+=2;
	}
	for(j=1;j<m;){
    	for(i=2;i<m-1;){//ofoghi
    		A[i][j]='-';
    		i+=2;
		}
    	j+=2;
	}
	for(i=2;i<m-1;){
		for(j=2;j<m-1;){
			A[i][j]= '+';
			j+=2;
		}
		i+=2;
	}
}

void copy(char A[][100],char B[][100], int m){
	int i,j    ;
	for (i=0;i<m;i++){
		for(j=0;j<m;j++){
			B[i][j]=A[i][j];
		}
	}
	for(i=1;i<m;i+=2){
		for(j=1;j<m;j+=2){
			B[i][j]='0';
		}
	}
}

void printb(int m){
	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++){
			printf(" %c",B[i][j]);
		}
		printf("\n");
	}
}

int main()
{   
	srand(time(NULL));
	printf("Welcome to Iran\n");
	//printf("%d",rand());
	//printf("\n%d",rand());

	char player1[21];
	char player2 [21];
	char player3[21];
	char player4[21];
	
    int n,m,i,j,rows,cols;
    int k  ,r1,c1,r2,c2,r3,c3,r4,c4  ;// r1: PLayer 1 row & .... 
    int wall, wmove, plan, random,random2, random3;
    int swWIN=1,swWall=1,sw=1, sw1,sw2, swRobot=0,swSucs;
	int turn=1;
	int r,c;
	int NewGame, BotGame;
	int wi,wj,hv; // wall location & ofoghi ya amoodi
	int p1wc,p2wc,p3wc,p4wc;// players wall counter: number of available wall of each player
	bool P1_is_bot,P2_is_bot,P3_is_bot,P4_is_bot;
	P1_is_bot=P2_is_bot=P3_is_bot=P4_is_bot=false;
	// LOADING ...

	clear();
	printf("\n   MAIN MENU\n\n\n   *New Game: 1\n\n   *Load Game: 2\n    : ");
	scanf("%d",&NewGame);
	while(1){
		if(NewGame==1) {
			clear();
			
			printf("\n   *Play With ROBOTS: 1\n\n   *PLAY UR OWN: 2\n    : ");
			scanf("%d",&BotGame);
			while(1){
				if(BotGame==1){// YES, PLAY WITH ROBOTS
					P2_is_bot=true;
					P3_is_bot=true;
					P4_is_bot=true;
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
			sw=1;
			
			break;
		}
		else if(NewGame==2){// LOAD GAME
			sw=0;
			clear();
			
			break;
		}
		printf("Worng!\a \nEnter 1 for New Game or 2 for Load Game: ");
		scanf("%d",&NewGame);
	}
	// 4 ta string and 4 ta int (wall) AND int(n*n) AND 8 ta int( loaction r1 c1)
	//  (n-1 * n-1)AND (HV) ta  int (wall location)  AND  TURNNNNNN
	
	if(P1_is_bot==false){ //REAL PLAYER
		printf("Player 1 name: ");
		scanf("%s",player1);
	}
	else{
		player1[5]="Alex";
	}
	
	if(P2_is_bot==false){ //REAL PLAYER
		printf("Player 2 name: ");
		scanf("%s",player2);
	}
	else{
		strcpy(player2,"Charlotte");
	}
	
	if(P3_is_bot==false){ //REAL PLAYER
		printf("Player 3 name: ");
		scanf("%s",player3);
	}
	else{
		strcpy(player3,"Jia");
	}
	
	if(P4_is_bot==false){ //REAL PLAYER
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
    m=2*n+1;
    k=2*n;
    //char A[100][100];//2*n +1
    createboard(A,m);
    

	print(m);
	
	// FIRST PLAYERS POSITION	
	//zoj ya fard
	if(n%2!=0){// fard
		A[1][n]='1';
		A[n][m-2]='2';
		A[m-2][n]='3';
		A[n][1]='4';
		r1=1;
    	c1=n;
    	r2=n;
    	c2=2*n-1;
    	r3=2*n-1;
    	c3=n;
    	r4=n;
    	c4=1;
	}
	else{
		A[1][n-1]='1';
		A[n-1][m-2]='2';
		A[m-2][n-1]='3';
		A[n-1][1]='4';
		r1=1;
		c1=n-1;
		r2=n-1;
		c2=2*n-1;
		r3=2*n-1;
		c3=n-1;
		r4=n-1;
		c4=1;
	}
	// 
	for(i=0;i<wallsize;i++){
		walloc[i][0]=1;
	}
	for(j=0;j<wallsize;j++){
		walloc[0][j]=1;
	}
	// i=0;j=0;
	while(1){
		printf("Please enter Number of Walls:");
		scanf("%d",&wall);
		if(wall>=1&&wall<=20) break;
		else{
			printf("WRONG ANSWER\n Enter again\a");
		}
	}
	p1wc=p2wc=p3wc=p4wc=wall;// PLAYERS WALL COUNTER
	print(m);	
	
	while(swWIN==1){
		clear();
		if(turn%4==1){// player 1 turn
			r=r1;
			c=c1;
			setColor(3,0);
			printf("%s's turn.TURN:[%d]\n",player1,turn);
			if(P1_is_bot){
				swRobot=1;
			}
		}
		else if(turn%4==2){//PLAYER 2 TURN
			r=r2;
			c=c2;
			setColor(5,0);
			printf("%s's turn.TURN:[%d]\n",player2,turn);
			if(P2_is_bot){
				swRobot=1;
			}
		}
		else if(turn%4==3){ //PLAYER 3 TURN
			r=r3;
			c=c3;
			setColor(8,0);
			printf("%s's turn.TURN:[%d]\n",player3,turn);
			if(P3_is_bot){
				swRobot=1;
			}
		}
		else{ // PLAYER 4 TURN
			r=r4;
			c=c4;
			setColor(2,0);
			printf("%s's turn.TURN:[%d]\n",player4,turn);
			if(P4_is_bot){
				swRobot=1;
			}
		}
		print(m);
		
		if(swRobot==0){// real player's turn
			printf("What's the plan?\nMOVE (1) Or WALL (2)? ( Enter num (1) or (2) ) :");
			while(1){
				scanf("%d",&plan);
				if(plan==1||plan==2) break;
				else{printf("Wrong plan\a Enter again:");
				}
			}
			if(plan==1){ // move
				printf("Enter number of move up(8) Or down(2) Or left(4) Or right(6):");
				while(1){
					scanf("%d",&wmove);
					if(wmove==8||wmove==2||wmove==4||wmove==6) break;
					printf("Wrong MOVE\a enter again:");
				}
				while(1){
					if(Move( A ,n,wmove,&r,&c)==1){// "1" mean: can't move to that location (OUT OF RULE)
						printf("out of rule\a Enter another:");
						scanf("%d",&wmove);
					}
					else {// SUCCESS MOVE
						if(turn%4==1){ // LAYER 1 TURN
							r1=r;
							c1=c;
						}
						else if(turn%4==2){// PLAYER 2 TURN
							r2=r;
							c2=c;
						}
						else if(turn%4==3){//PLAYER 3 TURN
							r3=r;
							c3=c;
						}
						else{// PLAYER 4 TURN
							r4=r;
							c4=c;
						}
						clear();
						print(m);
						break;
					}
				}
				
				winner(&swWIN,n,player1,player2,player3,player4,r1,c2,r3,c4);
			}
			else if(plan==2){// wall
				while(swWall){// baraye break bad az gozashtan wall
					if(p1wc==0||p2wc==0){// one of players have no wall...
						if(turn%4==1&& p1wc==0){
							printf("you have not enogh wall\a\nplease move\n");
							turn--;
							break;
						}
						else if(turn%4==2&& p2wc==0){
							printf("U have not enogh wall\a\nplease move\n");
							turn--;
							break;
						}
					}
					else if(p3wc==0||p4wc==0){
						if(turn%4==3&&p3wc==0){
							printf("YOU HAVE NOT ENOGH WALL\a\nPLEASE MOVE\n");
							turn--;
							break;
						}
						else if(turn%4==0&&p4wc==0){
							printf("U HAVE NOT ENOGH WALL\a\nPLEASE MOVE\n");
							turn--;
							break;
						}
					}
					printf("Please enter location of FORWAY (4 raah) :)\nenter i,j,h (1) OR v (2): ");
					scanf("%d %d %d",&wi,&wj,&hv);
					while(1){
						if( Wall(A,B,n,wi,wj,hv,r1,c1,r2,c2,r3,c3,r4,c4)==1){
							printf("out of RULE, enter again:\a\n ");
							scanf("%d %d %d",&wi,&wj,&hv);
						}
						else{// SUCCESS
							if(turn%4==1){
								p1wc--;
							}
							else if(turn%4==2){
								p2wc--;
							}
							else if(turn%4==3){
								p3wc--;
							}
							else{
								p4wc--;
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
					if(Move( A ,n,wmove,&r,&c)==0){ // SUCCESS MOVED.
						if(turn%4==1){
							r1=r;
							c1=c;
						}
						else if(turn%4==2){
							r2=r;
							c2=c;
						}
						else if(turn%4==3){
							r3=r;
							c3=c;
						}
						else {
							r4=r;
							c4=c;
						}
						break;
					}
				}
				// BASTE BE TURN R1 C1 .....
				
				winner(&swWIN,n,player1,player2,player3,player4,r1,c2,r3,c4);
			}
			else{// WALL
				plan=2;
				if(turn%4==1&&p1wc==0){
					turn--;
					swSucs=0;
				}
				else if(turn%4==2&&p2wc==0){
					turn --;
					swSucs=0;
				}
				else if(turn%4==3&&p3wc==0){
					turn--;
					swSucs=0;
				}
				else if(p4wc==0){
					turn--;
					swSucs=0;
				}
				while(swSucs){
					random=rand()%n;
					random2=rand()%n;
					if(walloc[random][random2]==0){
						while(1){
							random3=rand()%3;
							if(random3==0)random3++;
							if( Wall(A,B,n,random,random2,random3,r1,c1,r2,c2,r3,c3,r4,c4)==0){
								if(turn%4==1) p1wc--;
								else if(turn%4==2) p2wc--;
								else if( turn%4==3) p3wc--;
								else p4wc--;
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
	}
	
	return 0;
}
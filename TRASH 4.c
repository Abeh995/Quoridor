#include <stdio.h>
#include <windows.h>

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



char A[100][100];
int playloc[2][4];

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

int Wall(char A[][100],int n,int wi,int wj, int hv){ //PLACE WALLS   . wi: WALL I & ... .hv: H OR V
	
	if(wi>n-1|| wj >n-1){
		return 1; //OUT OF RULE
	}
	if(hv!=1 && hv!=2){
		return 1;//OUT OF RULE
	}
	wi*=2;
	wj*=2;
	if(hv==1){// 1 mean: OFOGHI
		if(A[wi][wj-1]==42 && A[wi][wj+1]==42){// CHAHAR RAH POR  AST LOTFAN BADAN TAMAS BEGIRID
			return 1; //OUT OF RULE
		}
		else{
			A[wi][wj-1]=42;
			A[wi][wj+1]=42;
			return 0; //SUCCESS.
		}
	}
	else{// hv=2 AMOODI
		if(A[wi-1][wj]==42  && A[wi+1][wj]==42 ){// CHAHAR RAH POR  AST LOTFAN BADAN TAMAS BEGIRID
			return 1;//OUT OF RULE
		}
		else{
			A[wi-1][wj]=42;
			A[wi+1][wj]=42;
			return 0; //SUCCESS
		}
	}
	
	
}

int Move(char A[][100],int n,int nmove,int *I,int *J ){//li= last *I mean last location of player piece and n= number of Dimensions
	// Nmove : Where to move( number of move)
	int i,j;
	if(nmove==1|| nmove==2){
		if(nmove ==1){ // nmove =1 (up)
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
					i=*I-2;
					j=*J;
					if(A[*I-3][*J]==42||A[*I-3][*J]== 205){
						return 1; //out of rule
					}
					else{
						A[*I-4][*J]=A[*I][*J];
						A[*I][*J]='0';
						*I-=4;
					}
					return 2;// MOHRE HARIF  (OUT OF RULE)
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
						A[*I+4][*J]=A[*I][*J];
						A[*I][*J]='0';
						*I+=4;
					}
					return 2;// MOHRE HARIF (OUT OF RULE)
				}
			}
		}
		return 0;// SUCCESS MOVE.
	}
	else{
		if(nmove== 3){ // nmove = 3 (left)
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
						A[*I][*J-4]= A[*I][*J];
						A[*I][*J]='0';
						*J-=4;
					}
					return 2; // MOHRE HARIF (OUT OF RULE)
				}
			}
		}
		else{// nmove = 4 (right)
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
						A[*I][*J+4]= A[*I][*J];
						A[*I][*J]='0';
						*J+=4;
					}
					return 2; // MOHRE HARIF (OUT OF RULE)
				}
			}
		}
		return 0;
	}
}




int main()
{   
	printf("Welcome to Iran\n");
    int n,m,i,j,rows,cols;
    int k  ,r1,c1,r2,c2  ;// r1: PLayer 1 row & .... 
    int wall, wmove, plan;
    int swWIN=1,swWALL=1,sw, sw1,sw2;
	int turn=1;
	int r,c;
	int wi,wj,hv; // wall location & ofoghi ya amoodi
	int p1wc,p2wc;// number of available wall of each player
	
	
	char player1[21];
	char player2 [21];
	printf("Player 1 name: ");
	scanf("%s",player1);
	printf("Player 2 name: ");
	scanf("%s",player2);
	
    printf("please enter number of Dimensions:\n");
    scanf("%d",&n);
    m=2*n+1;
    k=2*n;
    //char A[100][100];//2*n +1
    rows=m;
    cols=m;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
            	A[i][j]=42;
            }
            else{
            	A[i][j]='0';
			}
        }
    }
    for(i=1;i<m;){
    	for(j=2;j<m-1;){////////17
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
	print(m);
	print2(m);
	
	
	
		/*
		printf("please enter location of PLyer1:\n");
    	scanf("%d %d",&r1,&c1);
    	printf("please enter location of PLyer2:\n");
		scanf("%d %d",&r2,&c2);
	    int sw1=0,sw2=0;

		while(sw1==0||sw2==0){
		
			if(r1>n|| c1>n){
				sw1=0;
				printf("Dadash dari eshteb mizani\n\aPlease enter location of player 1 again:\n");
				scanf("%d %d",&r1,&c1);
			}
			else{sw1=1;
			}
			if(r2>n||c2>n){
				sw2=0;
				printf("Dadash dari eshteb mizani\n\aPlease enter location of player 2 again:\n");
				scanf("%d %d",&r2,&c2);
			}
			else{sw2=1;
			}
		}
		R1=r1 * 2 ;R2=r2 * 2;C1=c1 * 2 ; C2=c2 * 2;
		A[(r1*2)-1][(c1*2)-1]='1';
		A[(r2*2)-1][(c2*2)-1]='2';
		*/
		
	//zoj ya fard	
	if(n%2!=0){// fard
		A[1][n]='1';
		A[m-2][n]='2';
		r1=1;
    	c1=n;
    	r2=2*n-1;
    	c2=n;
	}
	else{
		A[1][n-1]='1';
		A[m-2][n-1]='2';
		r1=1;
		c1=n-1;
		r2=2*n-2;
		c2=n-1;
	}
	printf("Please enter Number of Walls:");
	scanf("%d",&wall);
	p1wc=p2wc=wall;
	print(m);
	
	while(swWIN==1){
		sw=1;// LINE 386
		if(turn%2==1){// player 1 turn
			r=r1;
			c=c1;
			printf("%s's turn",player1);
			

		}
		else{
			r=r2;
			c=c2;
			printf("%s's turn",player2);
			

		}
		printf("What's the plan?\nMOVE(1) Or WALL(2)? (enter num (1) or (2)) :");
		sw=0;
		while(sw==0){
			scanf("%d",&plan);
			if(plan==1||plan==2)sw=1;
			else{printf("Wrong plan\a Enter again:");
			}
		}
		if(plan==1){
			printf("Enter number of move up(1) Or down(2) Or left(3) Or right(4):");
			while(1){
				scanf("%d",&wmove);
				if(wmove==1||wmove==2||wmove==3||wmove==4) break;
				printf("Wrong MOVE\a enter again:");
			}
			while(1){
				if(Move( A ,n,wmove,&r,&c)==1){// "1" mean: can't move to that location (OUT OF RULE)
					printf("out of rule\a Enter another:");
					scanf("%d",&wmove);
				}
				else {
					if(turn%2==1){
						r1=r;
						c1=c;
					}
					else{
						r2=r;
						c2=c;
					}
					print(m);
					print2(m);
					
					break;
				}
			}
			
			/*if(1){// PAYANE BAAZI
				swWIN=0;
			}*/
		}
		else{// wall
			while(swWALL==1&& sw==1){
				if(p1wc==0||p2wc==0){// one of players have no wall...
					if(turn%2==1&& p1wc==0){
						printf("you have not enogh wall\a\nplease move ");
						turn--;
						break;
					}
					else if(turn%2==0&& p2wc==0){
						printf("U have not enogh wall\a\nplease move ");
						turn--;
						break;
					}
				}
				printf("Please enter location of FORWAY (4 raah) :)\nenter i,j,h(1) OR v(2): ");
				scanf("%d %d %d",&wi,&wj,&hv);
				while(1){
					if( Wall(A,n,wi,wj,hv)==1){
						printf("out of RULE, enter again:\a\n ");
						scanf("%d %d %d",&wi,&wj,&hv);
					}
					else{// SUCCESS
						if(turn%2==1){
							p1wc--;
						}
						else{
							p2wc--;
						}
						//setColor(4,0);
						print(m);
						sw=0;
						break;
					}
				}
			}
		}
		turn++;// PLAYERS TURN
	}
	//print 
    
    return 0;
}

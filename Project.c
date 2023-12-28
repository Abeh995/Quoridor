#include <stdio.h>

int main()
{   
printf("Welcome to iran\n");
    int n,m,i,j,rows,cols;
    int k  ,r1,c1,r2,c2  ;// r1: PLayer 1 row & .... 
    
    
    
    printf("please enter number of Dimensions:\n");
    scanf("%d",&n);
    m=2*n+1;
    k=2*n;
    char A[m][m];//2*n +1
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
    		A[i][j]=179;
    		j+=2;

		}
    	i+=2;
	}
	for(j=1;j<m;){
    	
    	for(i=2;i<m-1;){//17
    		A[i][j]=196;
    		i+=2;

		}
    	j+=2;
	}
	for(i=2;i<m-1;){
		for(j=2;j<m-1;){
			A[i][j]=197;
			j+=2;
		}
		i+=2;
	}
	
	
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
	
	/*
    i=0;
    while(j<19){
    	A[i][j]= '*';
    	j++;
	}
	j--;
	i=18;
    while(j>=0){
    	A[i][j]='*';
    	j--;
	}
	
	j=0;
    i=0;
    while(i<19){
    	A[i][j]= '*';
    	i++;
	}
	i--;
	j=18;
    while(i>=0){
    	A[i][j]='*';
    	i--;
	}
    
    for(i=0;i<19;i++){
        for(j=0;j<19;j++){
            A[i][j] = '*';
            A[j][i] = '*';
        }
    }*/
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            printf(" %c",A[i][j]);
        }
        printf("\n");
    }
    return 0;
}

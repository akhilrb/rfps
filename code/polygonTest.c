#include <stdio.h>
#include <math.h>
int circle[64][64];

void circleplotpt(int x,int y,int x1,int y1)
{
    //change 3rd parameter ie.15 to any other valid color number
    //like 2 for green
    circle[x+x1][y+y1]=1;
    circle[x-x1][y+y1]=1;
    circle[x+x1][y-y1]=1;
    circle[x-x1][y-y1]=1;
    circle[x+y1][y+x1]=1;
    circle[x-y1][y+x1]=1;
    circle[x+y1][y-x1]=1;
    circle[x-y1][y-x1]=1;
}
 
void circlemidpt(int x,int y,int r)
{
    int x1=0,y1=r,p=1-r;
    circleplotpt(x,y,x1,y1);
    while(x1<y1)
    {
        x1++;
        if(p<0)
            p+=2*x1+1;
        else
        {
            y1--;
            p+=2*(x1-y1)+1;
        }
        circleplotpt(x,y,x1,y1);
    }
}


int main()
{
	int x=32, y=32, r;
	while(1)
	{
		for(int i=0; i<2*x;i++)
			for(int j=0; j<2*x;j++)
				circle[i][j]=0;

		scanf("%d",&r);
		circlemidpt(x,y,r);
		for(int i=0; i<2*x;i++)
		{
			for(int j=0; j<2*x;j++)
				printf("%d", circle[i][j]);
			printf("\n");
		}
	}
	return 0;
}
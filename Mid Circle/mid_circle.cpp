#include<graphics.h>
#include<conio.h>

// Implementing Mid-Point Circle Drawing Algorithm
void midPointCircleDraw(int x_c, int y_c, int r, int c)
{
 int x,y,p;
 x=0;y=r;
 putpixel(x_c,y_c,15); 
 putpixel(x+x_c,y+y_c,c);
 putpixel(x+x_c,-y+y_c,c);
 putpixel(y+x_c,x+y_c,c);
 putpixel(-y+x_c,x+y_c,c);
 p=1-r;
 
 while(x<y)
 {
  if(p<0)
   p=p+2*x+2+1;
  else
  {
   p=p+2*x+2+1-2*y-2;
   y=y-1;
  }
  x=x+1;
//  delay(100);
  putpixel(x+x_c,y+y_c,c);    
  putpixel(x+x_c,-y+y_c,c);   
  putpixel(-x+x_c,y+y_c,c);   
  putpixel(-x+x_c,-y+y_c,c);  
  putpixel(y+x_c,x+y_c,c);    
  putpixel(y+x_c,-x+y_c,c);   
  putpixel(-y+x_c,x+y_c,c);   
  putpixel(-y+x_c,-x+y_c,c);  
 }
}

// Driver code
int main()
{
    int gd=DETECT,gm,r,x_c,y_c,i,j,c1=1,c2=0;

    printf("Enter the co-ordinate of Centre of Circle::");
    scanf("%d %d",&x_c,&y_c);
    printf("Enter the radius of the circle::");
    scanf("%d",&r);

    initgraph(&gd,&gm,NULL);    

    midPointCircleDraw(x_c,y_c,r,2);
    getch();
    closegraph();
    return 0;
}

#include<stdio.h> 
#include<GL/glut.h> 
#include<math.h> 
#define pi 3.142857 
#define ROUND(x) ( (int)(x+0.5) )
int p[2] = {-100, -100};
int q[2] = {150, 130};
int n=0;          
int *pixels=NULL; 
void Export2SVG_HTML(int *p, int n, int width, int height)
{
  int i; 
  FILE *fp = fopen("html.html", "w");
  fprintf(fp, "<!DOCTYPE html>\n<html>\n<body>\n"); 
  fprintf(fp, "<svg width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\"  version=\"1.1\">",width,height,width,height);
  for(i=0; i<n; i++)
  {
   fprintf(fp, "\n<rect x=\"%d\" y=\"%d\" width=\"10\" height=\"10\" style=\"fill:yellow;stroke:red;stroke-width:1.0;fill-opacity:0.8;stroke-opacity:1.0\"/>", p[2*i+0], p[2*i+1]);
   }
   fprintf(fp, "\n </svg>\n");
   fprintf(fp, "\n</body>\n</html>\n");
   fclose(fp);
   return;
}


void Export2SVG(int *p, int n, int width, int height)
{
  int i;
  FILE *fp = fopen("svg.svg", "w");
  fprintf(fp, "<svg width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\"  version=\"1.1\">",width,height,width,height);
  for(i=0; i<n; i++)
  {
   fprintf(fp, "\n<rect x=\"%d\" y=\"%d\" width=\"10\" height=\"10\" style=\"fill:yellow;stroke:red;stroke-width:1.0;fill-opacity:0.8;stroke-opacity:1.0\"/>", p[2*i+0], p[2*i+1]);

 }
  fprintf(fp, "\n </svg>\n");
  fclose(fp);
  return;
}
int *LineDDA(int xa, int ya, int xb, int yb, int *n)
{
   int dx = xb - xa;
   int dy = yb - ya;
   int steps, k,m;
   float xIncr, yIncr, x=xa, y=ya;

   if( abs(dx) > abs(dy) ) steps = abs(dx);
   else steps = abs(dy);
   int *pixels = (int*)malloc(2*(steps+1)*sizeof(int));
   if(!pixels){ printf("\n\nError: malloc failed in LineDDA()...\n\n"); return pixels;}   
   xIncr = dx/(float)steps;
   yIncr = dy/(float)steps;
   m=0;
   pixels[2*m+0]=(int)ROUND(x);
   pixels[2*m+1]=(int)ROUND(y);
   m++;
   for(k=0; k<steps; k++)
   {
        x += xIncr;
        y += yIncr;
        pixels[2*m+0]=(int)ROUND(x);
        pixels[2*m+1]=(int)ROUND(y);
        m++;
   }
   *n=m;
   printf("\nNumber of DDA Line pixels = %d\n", *n);
   return pixels;
}
void myInit (void) 
{ 
    glClearColor(0.0, 0.0, 0.0, 1.0);       
    glPointSize(2.0); 
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
    gluOrtho2D(-780, 780, -420, 420); 
} 
void onScreendisplay (void)  
{ 
    glClear(GL_COLOR_BUFFER_BIT); 
    glPointSize(2.0);
    glBegin(GL_POINTS); 
    float x, y;
    int i; 
    glColor3f( 1, 1, 1 );
    if(pixels)
    for ( i = 1; i < n-1; i++) 
    {
       glVertex2i( (float)pixels[2*i+0], (float)pixels[2*i+1]); 
    }
    glEnd(); 
    Export2SVG(pixels, n, 1000, 1000);  
    Export2SVG_HTML(pixels, n, 1000, 1000);
    glPointSize(8.0);
    glBegin(GL_POINTS);
    glColor3f( 1, 0, 0 );
    glVertex2i( (float)pixels[0], (float)pixels[1]); 
    glVertex2i( (float)pixels[2*(n-1)+0], (float)pixels[2*(n-1)+1]); 
    glEnd(); 
    glFlush(); 

} 
  
int main (int argc, char** argv) 
{ 
    int i=0;
    pixels = LineDDA(p[0], p[1], q[0], q[1], &n);
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    glutInitWindowSize(1366, 768); 
    glutInitWindowPosition(0, 0); 
    glutCreateWindow("DDA Line Deawing with OpenGL: "); 
    myInit(); 
    glutDisplayFunc(onScreendisplay); 
    glutMainLoop(); 
    return 1;
} 

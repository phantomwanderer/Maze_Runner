#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;


int locationY , locationX ;
int x = locationX, y = locationY;
int X[3], Y[3];


char maze[35][74]={  
{"#######################################################"},
{"#  #           #           #        #              #  #"},
{"#  #           #           #        #              #  #"},
{"#  #  #######  #  ####  #######  ####  ####  ####  #  #"},
{"#           #     #  #        #        #  #  #     #  #"},
{"#           #     #  #        #        #  #  #     #  #"},
{"#######  #  #######  #######  ####  #  #  #  #######  #"},
{"#     #  #           #        #  #  #  #  #        #  #"},
{"#     #  #           #        #  #  #  #  #        #  #"},
{"#  #  ##########  #  #  #######  ####  #  #######  #  #"},
{"#  #           #  #  #     #        #        #     #  #"},
{"#  #           #  #  #     #        #        #     #  #"},
{"#  ##########  ####  ####  #  ####  #######  #  ####  #"},
{"#        #     #  #     #  #     #        #  #        #"},
{"#        #     #  #     #  #     #        #  #        #"},
{"#  ####  ####  #  ####  #  #######  #  #  #  ##########"},
{"#     #     #  #  #     #     #     #  #  #     #     #"},
{"#     #     #  #  #     #     #     #  #  #     #     #"},
{"##########  #  #  #  #######  #  ####  #  ####  ####  #"},
{"#        #  #        #     #  #     #  #     #        #"},
{"#        #  #        #     #  #     #  #     #        #"},
{"#  ####  #  #######  ####  #  ####  ####  ##########  #"},
{"#  #     #        #        #     #  #  #           #  #"},
{"#  #     #        #        #     #  #  #           #  #"},
{"#  #  #######  #  ####  #######  #  #  ##########  #  #"},
{"#  #        #  #  #  #  #        #           #  #     #"},
{"#  #        #  #  #  #  #        #           #  #     #"},
{"#  #######  #  #  #  ####  #######  #######  #  #######"},
{"#  #     #  #  #        #        #  #     #           #"},
{"#  #     #  #  #        #        #  #     #           #"},
{"#  #  ####  ####  ####  #######  ####  #  #######  #  #"},
{"#  #              #        #           #           #  #"},
{"#  #              #        #           #           #  #"},
{"#XX####################################################"} };  

//maze[2][2] = '*';
//maze [10][10] = '*';
//maze [30][20] = '*';

void initGL() 
{
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
}

int setup()
{
    for(; maze[locationY][locationX] != ' ';)
    {
        locationX = rand()%55;
        locationY = rand()%34;  
    }
    for(;maze[Y[0]][X[0]] != ' ';)
    {
        X[0] = rand()%55;
        Y[0] = rand()%34;
    }
    maze[Y[0]][X[0]] = '*';
    for(;maze[Y[1]][X[1]] != ' ';)
    {
        X[1] = rand()%55;
        Y[1] = rand()%34;
    }
    maze[Y[1]][X[1]] = '*';
    for(;maze[Y[2]][X[2]] != ' ';)
    {
        X[2] = rand()%55;
        Y[2] = rand()%34;
    }
    maze[Y[2]][X[2]] = '*';
    return 0;
}


void troll(){
    int i,j,k=0;
    while(k<3){
	    i=X[k];
	    j=Y[k];
            //Check if the troll is next to the player
	    if(maze[Y[k]-1][X[k]]=='@')    Y[k]=Y[k]-1;
	    else if(maze[Y[k]+1][X[k]]=='@')    Y[k]=Y[k]+1;
	    else if(maze[Y[k]][X[k]+1]=='@')    X[k]=X[k]+1;
	    else if(maze[Y[k]][X[k]-1]=='@')    X[k]=X[k]-1;
	    else if(maze[Y[k]][X[k]]=='@')  continue; 
	    else{
		int p=1,q=1;
                //Assign p and q values to in according to the position(left, top, bottom, right) of the troll w.r.t. player
		if(X[k]>x)   p=-1;
		if(Y[k]>y)   q=-1;
                //Check if the troll and the player are in same line
                if(X[k]==x){     
                    if(maze[Y[k]+q][X[k]]==' ')  Y[k]=Y[k]+q; 
		    else if(maze[Y[k]-q][X[k]]==' ')  Y[k]=Y[k]-q; 
		    else if(maze[Y[k]][X[k]+p]==' ')  X[k]=X[k]+p;
		    else if(maze[Y[k]][X[k]-p]==' ')  X[k]=X[k]-p; 
                }
                else if(Y[k]==y){    
                        if(maze[Y[k]][X[k]+p]==' ')  X[k]=X[k]+p;  
		        else if(maze[Y[k]][X[k]-p]==' ')  X[k]=X[k]-p;
		        else if(maze[Y[k]+q][X[k]]==' ')  Y[k]=Y[k]+q;
		        else if(maze[Y[k]-q][X[k]]==' ')  Y[k]=Y[k]-q;
                }
                //Check in which direction is the troll near to the player
                else if(abs(X[k]-x)<abs(Y[k]-y)){   
                       /* If the troll is near to the player in x-direction, first see if the troll could be moved to that position.
                       If no, then try in y-direction. If both does not satisify, then find for x and y direction in opposite side. 
                       */
			if(maze[Y[k]][X[k]+p]==' ')  X[k]=X[k]+p;   //Check for the most feasible move
			else if(maze[Y[k]+q][X[k]]==' ')  Y[k]=Y[k]+q;
			else if(maze[Y[k]][X[k]-p]==' ')  X[k]=X[k]-p;
			else if(maze[Y[k]-q][X[k]]==' ')  Y[k]=Y[k]-q;
		}
		else{
                       /* If the troll is near to the player in y-direction, first see if the troll could be moved to that position.
                       If no, then try in x-direction. If both does not satisify, then find for x and y direction in opposite side. 
                       */
		    if(maze[Y[k]+q][X[k]]==' ') Y[k]=Y[k]+q; 
		    else if(maze[Y[k]][X[k]+p]==' ')  X[k]=X[k]+p;
		    else if(maze[Y[k]-q][X[k]]==' ')  Y[k]=Y[k]-q; 
		    else if(maze[Y[k]][X[k]-p]==' ')  X[k]=X[k]-p;
		}
	  } 
	  maze[j][i]=' ';
	  maze[Y[k]][X[k]]='*';
	  k++;
    }
}

void display_maze()
{
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  
    glClear(GL_COLOR_BUFFER_BIT);
    glutFullScreen();
    
    //int mazeWidth = glutGet(GLUT_WINDOW_WIDTH) - 250;
    //int mazeHeight = glutGet(GLUT_WINDOW_HEIGHT) - 150;
    
    double blockWidth = 2.0 / 61.0 ;   
    double blockHeight = 1.5 / 34.0 ;  
    float beginX = -0.9f;
    float beginY = 0.725f;
   
    for(int i = 0; i < 34; i++)
    {
        for(int j = 0; j < 65; j++)
        {
            if(maze[i][j] == '#')
            {
                glBegin(GL_QUADS);
                   glColor3f(1.0f, 1.0f, 1.0f); 
                   glVertex2f(beginX + blockWidth , beginY);
                   glVertex2f(beginX , beginY);
                   glVertex2f(beginX , beginY - blockHeight);
                   glVertex2f(beginX + blockWidth , beginY - blockHeight);                 
                glEnd();
            }


            else if(maze[i][j] == '@')
            {
                glBegin(GL_TRIANGLES);          
                    glColor3f(0.0f, 1.0f, 1.0f); 
                    glVertex2f(beginX + (1.0/61.0), beginY - (0.05/15.0));
                    glColor3f(0.0f, 1.0f, 1.0f);         
                    glVertex2f(beginX + (0.65 / 305.0), beginY -blockHeight + (0.3/34.0));
                    glColor3f(0.0f, 1.0f, 1.0f); 
                    glVertex2f(beginX + (8.0 / 305.0), beginY -blockHeight + (0.3/34.0));
                    glColor3f(0.0f, 1.0f, 0.0f);
                    glVertex2f(beginX + (0.65 / 305.0), beginY - (0.3/34.0));
                    glColor3f(0.0f, 0.0f, 1.0f);
                    glVertex2f(beginX + (1.0/61.0), beginY -blockHeight + (0.05/15.0));
                    glColor3f(0.f, 1.0f, 1.0f);
                    glVertex2f(beginX + (8.0 / 305.0), beginY - (0.3/34.0));
                glEnd();
                
            } 

            else if(maze[i][j] == '*')
            {
                glBegin(GL_TRIANGLES);          
                    glColor3f(1.0f, 0.0f, 0.0f); 
                    glVertex2f(beginX + (0.65 / 305.0), beginY - (0.3/34.0));
                    glVertex2f(beginX + (1.0/61.0), beginY -blockHeight + (0.05/15.0));
                    glVertex2f(beginX + (8.0 / 305.0), beginY - (0.3/34.0));
                glEnd();


            }

            //else if(maze[i][j] == '&')
            //{



            //}

            //else if(maze[i][j] == 's')
            //{


            //}

            beginX += blockWidth;
        }
        beginY -= blockHeight;
        beginX = -0.9f;
    }
    glFlush();
    //troll();
   
}


/*void specialkey(int key, int x, int y)
{
    
    switch(key) {
        case GLUT_KEY_UP:
                if(maze[locationY][locationX - 1] == ' ')
                {
                    maze[locationY][locationX] == ' ';
                    maze[locationY][locationX - 1] == '@';
                    locationX--;
                }
                else
                {
                    printf("Not possible %d %d",locationY, locationX);
                }               
                printf("locationY = %d %d\n",locationY,locationX);
                glutPostRedisplay();
              break;
        case GLUT_KEY_DOWN:
            if(maze[locationY][locationX + 1] == ' ')
                {
                    maze[locationY][locationX] == ' ';
                    maze[locationY][locationX + 1] == '@';
                    locationX++;
                }
                else
                {
                    printf("Not possible %d %d",locationY, locationX);
                }
                printf("locationY = %d %d\n",locationY,locationX);
                glutPostRedisplay();
              break;
        case GLUT_KEY_LEFT:
            if(maze[locationY - 1][locationX] == ' ')
                {
                    maze[locationY][locationX] == ' ';
                    maze[locationY - 1][locationX] == '@';
                    locationY--;
                }
                else
                {
                    printf("Not possible %d %d",locationY, locationX);
                }
                printf("locationY = %d %d\n",locationY,locationX);
                glutPostRedisplay();
              break;
        case GLUT_KEY_RIGHT:
            if(maze[locationY + 1][locationX] == ' ')
                {
                    maze[locationY][locationX] == ' ';
                    maze[locationY + 1][locationX] == '@';
                    locationY++;
                }
                else
                {
                    printf("Not possible %d %d",locationY, locationX);
                }
                printf("locationY = %d %d \n",locationY,locationX);
                glutPostRedisplay();
              break;
    }
    glutPostRedisplay();
    glFlush();

    
}
*/

void specialkey_playing(int key, int x, int y)
{
    
    switch(key) 
    {
        case GLUT_KEY_UP: 
        if(maze[locationY-1][locationX] == ' ')
            {
                maze[locationY][locationX] = ' ';
                locationY -= 1;
                maze[locationY][locationX] = '@';
            }
        break;
        case GLUT_KEY_DOWN:
        if(maze[locationY + 1][locationX] == 'X')
        {
            maze[locationY][locationX] = ' ';
            locationY += 1;
            maze[locationY][locationX] = '@';
            //FinalPage With YOUWON Function Call;
        } 
        else if(maze[locationY+1][locationX] == ' ')
            {
                maze[locationY][locationX] = ' ';
                locationY += 1;
                maze[locationY][locationX] = '@';
            }
        break;
        case GLUT_KEY_LEFT: 
        if(maze[locationY][locationX - 1] == 'X')
        {
            maze[locationY][locationX] = ' ';
            locationX -= 1;
            maze[locationY][locationX] = '@';
            //FinalPage With YOUWON Function Call;
        } 
        else if(maze[locationY][locationX-1] == ' ')
            {
                maze[locationY][locationX] = ' ';
                locationX -= 1;
                maze[locationY][locationX] = '@';
            }
        break;
        case GLUT_KEY_RIGHT:
        if(maze[locationY][locationX + 1] == 'X')
        {
            maze[locationY][locationX] = ' ';
            locationX += 1;
            maze[locationY][locationX] = '@';
            //FinalPage With YOUWON Function Call;
        } 
        else if(maze[locationY][locationX+1] == ' ')
            {
                maze[locationY][locationX] = ' ';
                locationX += 1;
                maze[locationY][locationX] = '@';
            }
        break;
    }
    glutPostRedisplay();
    glFlush();
    troll();
}

/*
void reshape(GLsizei width, GLsizei height) {  
   if (height == 0) height = 1;                
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
    glViewport(0, 0, width, height);
 
   glMatrixMode(GL_PROJECTION);  
   glLoadIdentity();             
   if (width >= height) {
      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {
     gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
}
*/

int main(int argc, char** argv)
{
    srand(time(NULL));
    setup();
    glutInit(&argc, argv); 
    //glutInitWindowSize(1000, 1000);   
    //glutInitWindowPosition(400,100);
    glutCreateWindow("Maze Runner");
    glutDisplayFunc(display_maze);    
    //glutReshapeFunc(reshape);
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutIdleFunc(display_maze);
    glutSpecialFunc(specialkey_playing);
    initGL();
    glutMainLoop();                 
    
    return 0; 

}


#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Keyboard and mouse input
 b- begin recording
 e- end recording
 s- save the playback file
 l- load the playback file
 p- play the recording
 r- reset the transformation
 
 middle mouse click- pick an object
 right amd left click- rotate the object
 */



#define TORSO_HEIGHT 4.0
#define UPPER_ARM_HEIGHT 2.0
#define LOWER_ARM_HEIGHT 2.0
#define UPPER_LEG_RADIUS  0.7
#define LOWER_LEG_RADIUS  0.3
#define LOWER_LEG_HEIGHT 2.0
#define UPPER_LEG_HEIGHT 2.0
#define UPPER_LEG_RADIUS  0.5
#define TORSO_RADIUS 1.2
#define UPPER_ARM_RADIUS  0.5
#define LOWER_ARM_RADIUS  0.3
#define HEAD_HEIGHT 1.0
#define HEAD_RADIUS 1.0

#define MAXEVENTS 1000
#define RECORDSIZE 2


int event_buffer[MAXEVENTS*RECORDSIZE];

int event_ptr = 0;


int playback_ptr=0;


int recordMode = 0;
int playbackMode = 0;


FILE *jFile = NULL;
char *fileName = "malavikai.txt";


int obj_id=1;

typedef float point[3];
static GLfloat thetadup[23]= {0.0,0.0,0.0,0.0,0.0,0.0,0.0,180.0,0.0,180.0,0.0 , 0.0,0.0,0.0,0.0,0.0,0.0,0.0,180.0,0.0,180.0,0.0, 0.0};

static GLfloat theta[23] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,180.0,0.0,180.0,0.0 , 0.0,0.0,0.0,0.0,0.0,0.0,0.0,180.0,0.0,180.0,0.0, 0.0};
static GLint angle = 2;

GLUquadricObj *t, *h, *lua, *lla, *rua, *rla, *lll, *rll, *rul, *lul, *ball, *p, *t1, *h1, *lua1, *lla1, *rua1, *rla1, *lll1, *rll1, *rul1, *lul1;



int wwidth = 500;
int wheight = 500;

double size=1.0;

int currentButton;



void torso()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(t,TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT,10,10);
    glPopMatrix();
}

void head()
{
    glPushMatrix();
    glTranslatef(0.0, 1.0,0.0);
    glScalef(HEAD_RADIUS, HEAD_HEIGHT, HEAD_RADIUS);
    gluSphere(h,1.0,10,20);
    glPopMatrix();
}

void left_upper_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lua,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
    glPopMatrix();
}

void left_lower_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lla,LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
    glPopMatrix();
}

void right_upper_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rua,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
    glPopMatrix();
}

void right_lower_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rla,LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
    glPopMatrix();
}

void left_upper_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lul,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
    glPopMatrix();
}

void left_lower_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lll,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT,10,10);
    glPopMatrix();
}

void right_upper_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rul,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
    glPopMatrix();
}

void right_lower_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rll,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT,10,10);
    glPopMatrix();
}




void torso1()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(t1,TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT,10,10);
    glPopMatrix();
}

void head1()
{
    glPushMatrix();
    glTranslatef(0.0, 1.0,0.0);
    glScalef(HEAD_RADIUS, HEAD_HEIGHT, HEAD_RADIUS);
    gluSphere(h1,1.0,10,20);
    glPopMatrix();
}

void left_upper_arm1()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lua1,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
    glPopMatrix();
}

void left_lower_arm1()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lla1,LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
    glPopMatrix();
}

void right_upper_arm1()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rua1,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
    glPopMatrix();
}

void right_lower_arm1()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rla1,LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
    glPopMatrix();
}

void left_upper_leg1()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lul1,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
    glPopMatrix();
}

void left_lower_leg1()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lll1,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT,10,10);
    glPopMatrix();
}

void right_upper_leg1()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rul1,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
    glPopMatrix();
}

void right_lower_leg1()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rll1,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT,10,10);
    glPopMatrix();
}



void draw_ball()
{
    glPushMatrix();
    glTranslatef(5.0, 3.0,0.0);
    glScalef(1.7, 1.5, 1.0);
    gluSphere(ball, 0.6, 10, 20);
    glPopMatrix();
}


void drawObjects(GLenum mode)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    
    //Robot 1
    glTranslatef(-6.0, -2.0, 0.0);
    if(mode == GL_SELECT) glLoadName(1);
   
    
        glColor3f(1.0, 0.0, 0.0);
    
    glRotatef(theta[0], 0.0, 1.0, 0.0);
    torso();
    glPushMatrix();
    
    if(mode == GL_SELECT) glLoadName(2);
    
        glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.0, TORSO_HEIGHT+0.5*HEAD_HEIGHT, 0.0);
    glRotatef(theta[1], 1.0, 0.0, 0.0);
    glRotatef(theta[2], 0.0, 1.0, 0.0);
    glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);
    head();
    
    glPopMatrix();
    glPushMatrix();
    
   
    
        glColor3f(1.0, 0.0, 0.0);
    if(mode == GL_SELECT) glLoadName(4);
    glTranslatef(-(TORSO_RADIUS+UPPER_ARM_RADIUS), 0.9*TORSO_HEIGHT, 0.0);
    glRotatef(theta[3], 1.0, 0.0, 0.0);
    left_upper_arm();
    
   
    
        glColor3f(1.0, 0.0, 0.0);
    if(mode == GL_SELECT) glLoadName(5);
    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[4], 1.0, 0.0, 0.0);
    left_lower_arm();
    
    glPopMatrix();
    glPushMatrix();
    
   
        glColor3f(1.0, 0.0, 0.0);
    
    if(mode == GL_SELECT) glLoadName(6);
    glTranslatef(TORSO_RADIUS+UPPER_ARM_RADIUS, 0.9*TORSO_HEIGHT, 0.0);
    glRotatef(theta[5], 1.0, 0.0, 0.0);
    right_upper_arm();
    
    
        glColor3f(1.0, 0.0, 0.0);
    
    if(mode == GL_SELECT) glLoadName(7);
    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[6], 1.0, 0.0, 0.0);
    right_lower_arm();
    
    
        glColor3f(1.0, 0.0, 0.0);
    
    glPopMatrix();
    glPushMatrix();
    if(mode == GL_SELECT) glLoadName(8);
    glTranslatef(-(TORSO_RADIUS+UPPER_LEG_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[7], 1.0, 0.0, 0.0);
    left_upper_leg();
    
    
        glColor3f(1.0, 0.0, 0.0);
    
    if(mode == GL_SELECT) glLoadName(9);
    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[8], 1.0, 0.0, 0.0);
    left_lower_leg();
    
    
        glColor3f(1.0, 0.0, 0.0);
    
    glPopMatrix();
    glPushMatrix();
    if(mode == GL_SELECT) glLoadName(10);
    glTranslatef(TORSO_RADIUS+UPPER_LEG_RADIUS, 0.1*UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[9], 1.0, 0.0, 0.0);
    right_upper_leg();
    
    
        glColor3f(1.0, 0.0, 0.0);
    
    if(mode == GL_SELECT) glLoadName(11);
    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[10], 1.0, 0.0, 0.0);
    right_lower_leg();
    
    glPopMatrix();
    
    
   
    //Ball
    
    glPushMatrix();
    
    if (angle==22)
        glColor3f(1.0, 1.0, 0.0);
    else
        glColor3f(0.0, 1.0, 0.0);
    if(mode== GL_SELECT) glLoadName(23);
    glTranslatef(0.0, -6.0, 0.0);
    glRotatef(theta[22], 0.0, 1.0, 0.0);
    draw_ball();
    glPopMatrix();
    
    
    
    
    //Robot 2
    
    
    glTranslatef(9.5, 0.0, 0.0);
   
    if(mode == GL_SELECT) glLoadName(12);
    
        glColor3f(0.0, 0.0, 1.0);
    
    glRotatef(theta[11], 0.0, 1.0, 0.0);
    torso1();
    glPushMatrix();
    
    if(mode == GL_SELECT) glLoadName(13);
    
        glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0.0, TORSO_HEIGHT+0.5*HEAD_HEIGHT, 0.0);
    glRotatef(theta[12], 1.0, 0.0, 0.0);
    glRotatef(theta[13], 0.0, 1.0, 0.0);
    glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);
    head1();
    
    glPopMatrix();
    glPushMatrix();
    
    // Color in blue if the object is selected
    
        glColor3f(0.0, 0.0, 1.0);
    if(mode == GL_SELECT) glLoadName(15);
    glTranslatef(-(TORSO_RADIUS+UPPER_ARM_RADIUS), 0.9*TORSO_HEIGHT, 0.0);
    glRotatef(theta[14], 1.0, 0.0, 0.0);
    left_upper_arm1();
    
    // Color in blue if the object is selected
    
        glColor3f(0.0, 0.0, 1.0);
    if(mode == GL_SELECT) glLoadName(16);
    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[15], 1.0, 0.0, 0.0);
    left_lower_arm1();
    
    glPopMatrix();
    glPushMatrix();
   
        glColor3f(0.0, 0.0, 1.0);
    
    if(mode == GL_SELECT) glLoadName(17);
    glTranslatef(TORSO_RADIUS+UPPER_ARM_RADIUS, 0.9*TORSO_HEIGHT, 0.0);
    glRotatef(theta[16], 1.0, 0.0, 0.0);
    right_upper_arm1();
    
   
        glColor3f(0.0, 0.0, 1.0);
    
    if(mode == GL_SELECT) glLoadName(18);
    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[17], 1.0, 0.0, 0.0);
    right_lower_arm1();
    
    
        glColor3f(0.0, 0.0, 1.0);
    glPopMatrix();
    glPushMatrix();
    if(mode == GL_SELECT) glLoadName(19);
    glTranslatef(-(TORSO_RADIUS+UPPER_LEG_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[18], 1.0, 0.0, 0.0);
    left_upper_leg1();
   
        glColor3f(0.0, 0.0, 1.0);
    
    if(mode == GL_SELECT) glLoadName(20);
    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[19], 1.0, 0.0, 0.0);
    left_lower_leg1();
    
    
        glColor3f(0.0, 0.0, 1.0);
    
    glPopMatrix();
    glPushMatrix();
    if(mode == GL_SELECT) glLoadName(21);
    glTranslatef(TORSO_RADIUS+UPPER_LEG_RADIUS, 0.1*UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[20], 1.0, 0.0, 0.0);
    right_upper_leg1();
    
    
        glColor3f(0.0, 0.0, 1.0);
    
    
    if(mode == GL_SELECT) glLoadName(22);
    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[21], 1.0, 0.0, 0.0);
    right_lower_leg1();
    
    glPopMatrix();
    
    
    glFlush();
    glutSwapBuffers();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
   
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    if (wwidth <= wheight)
        glOrtho(-10.0, 10.0, -10.0 * (GLfloat) wheight / (GLfloat) wwidth,
                10.0 * (GLfloat) wheight / (GLfloat) wwidth, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat) wwidth / (GLfloat) wheight,
                10.0 * (GLfloat) wwidth / (GLfloat) wheight, -10.0, 10.0, -10.0, 10.0);
    //
    glMatrixMode (GL_MODELVIEW);
    
    drawObjects(GL_RENDER);
    glFlush();
    
}
void reset()
{
    for (int i=0; i<12; i++)
    {
        theta[i]=thetadup[i];
    }
    display();
}



void timerFunc(int val)
{
   
    if(playback_ptr<event_ptr)
    {
        obj_id = event_buffer[playback_ptr++];
        angle = event_buffer[playback_ptr++];
        
      
        switch(obj_id)
        {
            case 1:
                theta[0] = angle;
                break;
            case 2:
                theta[1] = angle;
                theta[2] = angle;
                break;
            case 3:
                theta[3] = angle;
                break;
            case 4:
                theta[4] = angle;
                break;
            case 5:
                theta[5] = angle;
                break;
            case 6:
                theta[6] = angle;
                break;
            case 7:
                theta[7] = angle;
                break;
            case 8:
                theta[8] = angle;
                 break;
            case 9:
                theta[9] = angle;
                break;
            case 10:
                theta[10] = angle;
                break;
            case 11:
                theta[11] = angle;
                break;
            case 12:
                theta[12] = angle;
                theta[13] = angle;
                break;
            case 14:
                theta[14] = angle;
                break;
            case 15:
                theta[15] = angle;
                break;
            case 16:
                theta[16] = angle;
                break;
            case 17:
                theta[17] = angle;
                break;
            case 18:
                theta[18] = angle;
                break;
            case 19:
                theta[19] = angle;
                break;
            case 20:
                theta[20] = angle;
                break;
            case 21:
                theta[21] = angle;
                break;
            case 22:
                theta[22] = angle;
                break;
        }
        
        
        display();
        
        
        glutTimerFunc(50, timerFunc, 1);
    }
    else
    {
        playback_ptr=0;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'b':
            recordMode = 1;
            playbackMode = 0;
            printf("Recording...  Press 'e' to end\n");
            event_ptr=0;
            break;
            
        case 'e':
            if(recordMode == 1)
            {
                recordMode = 0;
                printf("Recording stopped.  Press 's' to save to playback file.\n");
            }
            break;
            
        case 'l':
            recordMode = 0;
            playbackMode = 0;
            
            event_ptr=0;
            playback_ptr=0;
            reset();
            
            printf("Loading file %s\n", fileName);
            
            jFile = fopen(fileName, "r");
            if ( jFile == NULL ) {
                printf("Warning: Could not open %s\n", fileName);
                playbackMode = 0;
            }
            else {
                
                while((fscanf(jFile, "%d ", &event_buffer[event_ptr])) != EOF)
                {
                    event_ptr++;
                }
                fclose(jFile);
                playbackMode = 1;
            }
            break;
            
        case 'r':
            recordMode = 0;
            playbackMode = 0;
            
            event_ptr=0;
            playback_ptr=0;
            reset();
            break;
            
        case 'p':
            if(playbackMode==1)
            {
                reset();
                glutTimerFunc(4,timerFunc,1);
            }
            break;
            
        case 's':
            recordMode = 0;
            playbackMode = 0;
            
            jFile = fopen(fileName, "w");
            if (jFile == NULL)
            {
                printf("Warning: Could not open %s\n", fileName);
            }
            else {
                for(int j=0;j<event_ptr;j++)
                    fprintf(jFile, "%d ", event_buffer[j]);
                fclose(jFile);
                printf("\nEvents saved in %s\n", fileName);
            }
            playback_ptr=0;
            break;
    }
}

void menu(int id)
{
    if(id <23 )
    {
        angle = id;
        obj_id = id;
    }
    if(id == 23) exit(0);
}


void processHits (GLint hits, GLuint buffer[])
{
    unsigned int i, j;
    GLuint ii, jj, names, *ptr;
    
    printf ("hits = %d\n", hits);
    ptr = (GLuint *) buffer;
    for (i = 0; i < hits; i++)
    {
        names = *ptr;
        ptr+=3;
        for (j = 0; j < names; j++)
        {
            printf("object name: %d\n", *ptr);
            angle = *ptr - 1;
            ptr++;
        }
    }
}

#define SIZE 512


void mouse(int btn, int state, int x, int y)
{
    GLuint selectBuf[SIZE];
    GLint hits;
    GLint viewport[4];
    
    
    if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
        currentButton = GLUT_MIDDLE_BUTTON;
        glGetIntegerv (GL_VIEWPORT, viewport);
        
        glSelectBuffer (SIZE, selectBuf);
        glRenderMode(GL_SELECT);
        
        glInitNames();
        glPushName(0);
        
        glMatrixMode (GL_PROJECTION);
        glPushMatrix ();
        glLoadIdentity ();
        
       
        
        gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),
                       10.0, 10.0, viewport);
        if (wwidth <= wheight)
            glOrtho(-10.0, 10.0, -10.0 * (GLfloat) wheight / (GLfloat) wwidth,
                    10.0 * (GLfloat) wheight / (GLfloat) wwidth, -10.0, 10.0);
        else
            glOrtho(-10.0 * (GLfloat) wwidth / (GLfloat) wheight,
                    10.0 * (GLfloat) wwidth / (GLfloat) wheight, -10.0, 10.0, -10.0, 10.0);
        
        drawObjects(GL_SELECT);
        
        glMatrixMode (GL_PROJECTION);
        glPopMatrix ();
        glFlush ();
        
        
        hits = glRenderMode (GL_RENDER);
        processHits (hits, selectBuf);
        
        glutPostRedisplay();
    }
    else if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        currentButton = GLUT_LEFT_BUTTON;
        theta[angle] += 5.0;
        if( theta[angle] > 360.0 ) theta[angle] -= 360.0;
        if(recordMode ==1)
        {
            event_buffer[event_ptr++]=angle;
            event_buffer[event_ptr++]=theta[angle];
          
            
        }
        display();
    }
    else if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        currentButton = GLUT_RIGHT_BUTTON;
        theta[angle] -= 5.0;
        if( theta[angle] < 360.0 ) theta[angle] += 360.0;
        
        
        if(recordMode ==1)
        {
            event_buffer[event_ptr++]=angle;
            event_buffer[event_ptr++]=theta[angle];
        }
        
        display();
    }
}

void myReshape(int w, int h)
{
    wheight = h;
    wwidth = w;
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-10.0, 10.0, -10.0 * (GLfloat) h / (GLfloat) w,
                10.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat) w / (GLfloat) h,
                10.0 * (GLfloat) w / (GLfloat) h, 0.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myinit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    
    
    h=gluNewQuadric();
    gluQuadricDrawStyle(h, GLU_LINE);
    t=gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_LINE);
    lua=gluNewQuadric();
    gluQuadricDrawStyle(lua, GLU_LINE);
    lla=gluNewQuadric();
    gluQuadricDrawStyle(lla, GLU_LINE);
    rua=gluNewQuadric();
    gluQuadricDrawStyle(rua, GLU_LINE);
    rla=gluNewQuadric();
    gluQuadricDrawStyle(rla, GLU_LINE);
    lul=gluNewQuadric();
    gluQuadricDrawStyle(lul, GLU_LINE);
    lll=gluNewQuadric();
    gluQuadricDrawStyle(lll, GLU_LINE);
    rul=gluNewQuadric();
    gluQuadricDrawStyle(rul, GLU_LINE);
    rll=gluNewQuadric();
    gluQuadricDrawStyle(rll, GLU_LINE);
    
    ball=gluNewQuadric();
    gluQuadricDrawStyle(ball, GLU_LINE);
    p=gluNewQuadric();
    gluQuadricDrawStyle(p, GLU_LINE);
    
    t1=gluNewQuadric();
    gluQuadricDrawStyle(t1, GLU_LINE);
    h1=gluNewQuadric();
    gluQuadricDrawStyle(h1, GLU_LINE);
    lua1=gluNewQuadric();
    gluQuadricDrawStyle(lua1, GLU_LINE);
    lla1=gluNewQuadric();
    gluQuadricDrawStyle(lla1, GLU_LINE);
    rua1=gluNewQuadric();
    gluQuadricDrawStyle(rua1, GLU_LINE);
    rla1=gluNewQuadric();
    gluQuadricDrawStyle(rla1, GLU_LINE);
    lul1=gluNewQuadric();
    gluQuadricDrawStyle(lul1, GLU_LINE);
    lll1=gluNewQuadric();
    gluQuadricDrawStyle(lll1, GLU_LINE);
    rul1=gluNewQuadric();
    gluQuadricDrawStyle(rul1, GLU_LINE);
    rll1=gluNewQuadric();
    gluQuadricDrawStyle(rll1, GLU_LINE);

    
}


void moveObject(int x, int y)
{
    
    if(currentButton == GLUT_LEFT_BUTTON )
    {
        theta[angle] += 5.0;
        if( theta[angle] > 360.0 ) theta[angle] -= 360.0;
        display();
    }
   
    else if(currentButton == GLUT_RIGHT_BUTTON)
    {
        theta[angle] -= 5.0;
        if( theta[angle] < 360.0 ) theta[angle] += 360.0;
        display();
    }
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Robot Playing Sport");
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(moveObject);
    
    glutMainLoop();
    return 0;
}


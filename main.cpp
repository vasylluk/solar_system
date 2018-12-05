#include <iostream>
#include <stdio.h>
#include <memory.h>

#include <GL/glut.h>

#define ILUT_USE_OPENGL
#include <IL/il.h>
#include <IL/ilut.h>
#include <IL/ilu.h>

GLubyte *g_pImage;
int g_width, g_height;
GLenum g_format, g_type;

GLuint backTex, moonTex, sunTex, earthTex, marsTex, mercuryTex, jupiterTex, saturnTex, uranusTex, neptuneTex, venusTex;
const char moon[] = "moon.jpg";
const char sun[] = "sun.jpg";
const char earth[] = "earth.jpg";
const char mercury[] = "mercury.jpg";
const char venus[] = "venus.jpg";
const char mars[] = "mars.jpg";
const char jupiter[] = "jupiter.jpg";
const char saturn[] = "saturn.jpg";
const char neptune[] = "neptune.jpg";
const char uranus[] = "uranus.jpg";
const char background[] = "back.jpg";

void resize(int w,int h)
{
if (h == 0) h = 1;
float ratio=w*1.0/h;
glViewport(0,0,w,h);
glMatrixMode( GL_PROJECTION );
glLoadIdentity();
gluPerspective(45.0, ratio, 0.1,100);
gluLookAt( 10,10,10, 0,0,0, 0,1,0 );
glMatrixMode( GL_MODELVIEW );
}
float digit = 1;
int r = 100;
float cx=0.0, cy=0.0, tap = 0.1;
float spin1=0,spin2=45,spin3=90,spin4=135,spin5=180,spin6=225,spin7=270,spin8=315;


void LoadImage(const char *sTextureName)
{
	ILuint img;
	ilGenImages(1, &img);
	ilBindImage(img);
	if (!ilLoad(IL_TYPE_UNKNOWN, sTextureName))
	{
		printf("ERROR: Cann't load image %s\n", sTextureName);
		exit(-1);
	}

	g_width = ilGetInteger(IL_IMAGE_WIDTH);
	g_height = ilGetInteger(IL_IMAGE_HEIGHT);
	g_format = ilGetInteger(IL_IMAGE_FORMAT);
	g_type = ilGetInteger(IL_IMAGE_TYPE);

	size_t size = ilGetInteger(IL_IMAGE_SIZE_OF_DATA);

	g_pImage = new GLubyte[size];

	memcpy(g_pImage, ilGetData(), size);
}

int DevILInit()
{
   if ( ilGetInteger ( IL_VERSION_NUM ) < IL_VERSION )
   {
       fprintf ( stderr, "Incorrect devil.dll version\n" );
       return 0;
   }
   if ( iluGetInteger ( ILU_VERSION_NUM ) < ILU_VERSION )
   {
       fprintf ( stderr, "Incorrect ilu.dll version\n" );
       return 0;
   }
   if ( ilutGetInteger ( ILUT_VERSION_NUM ) < ILUT_VERSION )
   {
       fprintf ( stderr, "Incorrect ilut.dll version\n" );
       return 0;
   }
   ilInit();
   iluInit();
   ilutInit();
   ilutRenderer(ILUT_OPENGL);
}

void initTexture()
{
	glGenTextures(1,&backTex);
	glBindTexture(GL_TEXTURE_2D,backTex);

	LoadImage(background);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,g_format,g_width,g_height,
	0,g_format,g_type,g_pImage);

	sunTex = ilutGLLoadImage((char*)sun);
	moonTex = ilutGLLoadImage((char*)moon);
	earthTex = ilutGLLoadImage((char*)earth);
	marsTex = ilutGLLoadImage((char*)mars);
	venusTex = ilutGLLoadImage((char*)venus);
	mercuryTex = ilutGLLoadImage((char*)mercury);
	jupiterTex = ilutGLLoadImage((char*)jupiter);
	saturnTex = ilutGLLoadImage((char*)saturn);
	uranusTex = ilutGLLoadImage((char*)uranus);
    neptuneTex = ilutGLLoadImage((char*)neptune);
	backTex = ilutGLLoadImage((char*)background);

	GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
	GLfloat mat_shininess[]={50.0};
	GLfloat light_position[]={1.0,1.0,1.0,0.0};
	GLfloat white_light[]={1.0,1.0,1.0,1.0};

	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
	glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
}

void display(void)
{
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

glPushMatrix();
    glTranslatef(cx,0.0,cy);
    //сонце
    glPushMatrix();
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTranslatef(0.0,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D,sunTex);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glutSolidSphere(digit*1,100,100);
    glPopMatrix();
    //меркурій
    glPushMatrix();
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glRotatef(spin1,0.0,1.0,0.0);
    glTranslatef(r*0.01289,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D,mercuryTex);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glutSolidSphere(digit*0.03427,10,10);
    glPopMatrix();
    //венера
    glPushMatrix();
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glRotatef(spin2,0.0,1.0,0.0);
    glTranslatef(r*0.024,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D,moonTex);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glutSolidSphere(digit*0.08462,10,10);
    glPopMatrix();
    //земля
    glPushMatrix();
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glRotatef(spin3,0.0,1.0,0.0);
    glTranslatef(r*0.033,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D,earthTex);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glutSolidSphere(digit*0.08951,10,10);
    glPopMatrix();
    //марс
    glPushMatrix();
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glRotatef(spin4,0.0,1.0,0.0);
    glTranslatef(r*0.05,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D,marsTex);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glutSolidSphere(digit*0.04755,10,10);
    glPopMatrix();
    //Юпітер
    glPushMatrix();
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glRotatef(spin5,0.0,1.0,0.0);
    glTranslatef(r*0.17,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D,jupiterTex);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glutSolidSphere(digit*1,100,100);
    glPopMatrix();
    //Сатурн
    glPushMatrix();
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glRotatef(spin6,0.0,1.0,0.0);
    glTranslatef(r*0.31,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D,saturnTex);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glutSolidSphere(digit*0.8392,10,10);
    glPopMatrix();
    //Уран
    glPushMatrix();
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glRotatef(spin7,0.0,1.0,0.0);
    glTranslatef(r*0.64,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D,uranusTex);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glutSolidSphere(digit*0.3566,10,10);
    glPopMatrix();
    //Нептун
    glPushMatrix();
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glRotatef(spin8,0.0,1.0,0.0);
    glTranslatef(r*1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D,neptuneTex);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glutSolidSphere(digit*0.3357,10,10);
    glPopMatrix();

glPopMatrix();

glDisable(GL_TEXTURE_GEN_S);
glDisable(GL_TEXTURE_GEN_T);
glDisable(GL_TEXTURE_2D);

glutSwapBuffers();
}

void moving(void)
{
    spin1+=(360.0/88);
    if(spin1>=360){
            spin1=0;
        }
    spin2+=(360.0/225);
    if(spin2>=360){
            spin2=0;
        }
    spin3+=(360.0/365);
    if(spin3>=360){
            spin3=0;
        }
    spin4+=(360.0/686);
    if(spin4>=360){
            spin4=0;
        }
    spin5+=(360.0/4329);
    if(spin5>=360){
            spin5=0;
        }
    spin6+=(360.0/10753);
    if(spin6>=360){
            spin6=0;
        }
    spin7+=(360.0/30667);
    if(spin7>=360){
            spin7=0;
        }
    spin8+=(360.0/60145);
    if(spin8>=360){
            spin8=0;
        }


glutPostRedisplay();
}

void mouse(int button,int state,int x,int y)
{
if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){glutIdleFunc(NULL);}
if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){glutIdleFunc(moving);}
}

void keyboard(unsigned char key, int x,int y)
{
switch(key){
    case 'a': cx=cx-tap; break;
    case 'd': cx=cx+tap; break;
    case 'w': cy=cy+tap; break;
    case 's': cy=cy-tap; break;
    }
}

void arrow_keys (int keys,int x,int y)
{
    switch(keys){
    case GLUT_KEY_UP: glutFullScreen(); break;
    case GLUT_KEY_DOWN :glutReshapeWindow(800,600); break;
    }
}

int main(int argc, char **argv) {
glutInit(&argc, argv);
glutInitWindowPosition(50, 50);
glutInitWindowSize(640, 480);
glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
DevILInit();
initTexture();
glutCreateWindow("SOLLAR SYSTEM");
glutIdleFunc(display);
glutDisplayFunc(display);
glutReshapeFunc(resize);
glutMouseFunc(mouse);
glutKeyboardFunc(keyboard);
glutSpecialFunc(arrow_keys);

glEnable(GL_DEPTH_TEST);
glEnable(GL_COLOR_MATERIAL);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);

glutIdleFunc(moving);

glutMainLoop();
}

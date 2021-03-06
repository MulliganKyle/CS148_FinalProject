#include "main.h"
#include "createTexture.h"

#ifdef WIN32
#define ssize_t SSIZE_T
#endif

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cmath>

// file locations
std::string vertexShader;
std::string fragmentShader;

SimpleShaderProgram *shader;


#define TRUE 1
#define FALSE 0

int mouseDown = FALSE;

float x_rot= 0.0;
float y_rot= 0.0;

float x_diff= 0.0;
float y_diff= 0.0;

float depth= 0.0;


float minX, minY, minZ, maxX, maxY, maxZ;


GLuint texId;

struct point
{
   float x, y, z;
   point() { x=0; y=0; z=0;}
   point(float _x, float _y, float _z) { x=_x; y=_y; z=_z;}
};

struct texturePoint
{
   float x, y;
   texturePoint() { x=0; y=0;}
   texturePoint(float _x, float _y) { x=_x; y=_y;}
};

struct normal
{
   float x, y, z;

   normal() { x=0; y=0; z=0;}
   normal(float _x, float _y, float _z) { x=_x; y=_y; z=_z;}
};

struct vertex
{
   point p;
   texturePoint t;
   normal n;
};

struct triangle
{
   vertex v0, v1, v2;
   triangle(vertex _v0, vertex _v1, vertex _v2) { v0=_v0; v1=_v1; v2=_v2;}
};

std::vector<triangle> triangles;


void DrawWithShader(){
   glPolygonMode(GL_FRONT, GL_FILL);
   glEnable(GL_TEXTURE_2D);
   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
   glDisable(GL_LIGHTING);
   glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
   glBindTexture(GL_TEXTURE_2D, texId);
   shader->Bind();


   for(triangle someTriangles: triangles)
   {
      glBegin(GL_TRIANGLES);
      glTexCoord2f(someTriangles.v0.t.x, -1*someTriangles.v0.t.y);
      glNormal3f(someTriangles.v0.n.x, someTriangles.v0.n.y, someTriangles.v0.n.z);
      glVertex3f(someTriangles.v0.p.x, someTriangles.v0.p.y, someTriangles.v0.p.z);

      glTexCoord2f(someTriangles.v1.t.x, -1*someTriangles.v1.t.y);
      glNormal3f(someTriangles.v1.n.x, someTriangles.v1.n.y, someTriangles.v1.n.z);
      glVertex3f(someTriangles.v1.p.x, someTriangles.v1.p.y, someTriangles.v1.p.z);

      glTexCoord2f(someTriangles.v2.t.x, -1*someTriangles.v2.t.y);
      glNormal3f(someTriangles.v2.n.x, someTriangles.v2.n.y, someTriangles.v2.n.z);
      glVertex3f(someTriangles.v2.p.x, someTriangles.v2.p.y, someTriangles.v2.p.z);
      glEnd();
   }

   shader->UnBind();
}

void DisplayCallback(){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(-(maxX + minX)/2.0f,-(maxY + minY)/2.0f,-((maxZ + minZ)/2.0f)-((std::abs(maxZ-minZ))*2.0));

   glRotatef(x_rot, 1.0, 0.0, 0.0);
   glRotatef(y_rot, 0.0, 1.0, 0.0);
   glMatrixMode(GL_PROJECTION);
   glTranslatef(0.0, 0.0, depth);
   glMatrixMode(GL_MODELVIEW);

   DrawWithShader();

   depth=0;

   glutSwapBuffers();
}

void ReshapeCallback(int w, int h){
   glViewport(0, 0, w, h);

   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   gluPerspective(30.0f, (float)w/(float)h, 0.1f, 100000.f);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void KeyCallback(unsigned char key, int x, int y)
{
   switch(key) {
      case '-':
	 depth-=10;
	 break;
      case '=':
	 depth+=10;
	 break;
      case 'q':
	 exit(0);
      default:
	 break;
   }

   glutPostRedisplay();
}
void loadTexture(const std::string& texFilename){
   glShadeModel(GL_FLAT);
   SimpleImage texPNG(texFilename);
   int w = texPNG.width();
   int h = texPNG.height();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(1, &texId);
   glBindTexture(GL_TEXTURE_2D, texId);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_FLOAT, texPNG.data());
}
void Setup()
{
   shader = new SimpleShaderProgram();
   shader->LoadVertexShader(vertexShader);
   shader->LoadFragmentShader(fragmentShader);
   glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
   glEnable(GL_DEPTH_TEST);


}


void mouseButton(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {
      mouseDown = true;

      x_diff = (x/10) - y_rot;
      y_diff = (-y/10) + x_rot;
   }
   else
      mouseDown = false;
}

void mouseMotion(int x, int y)
{
   if (mouseDown)
   {
      y_rot = (x/10) - x_diff;
      x_rot = (y/10) + y_diff;

      glutPostRedisplay();
   }
}




void load_obj(const std::string& filename)
{
   std::ifstream ifs(filename.c_str());
   std::string mode;
   std::vector<point> points;
   std::vector<texturePoint> texturePoints;
   std::vector<normal> normals;

   std::string tempVertex;
   vertex Va, Vb, Vc;

   if(ifs.is_open())
   {
      float x, y, z;
      float x1, y1;
      float x2, y2, z2;

      while(ifs >> mode)
      {


	 if(mode == "#")
	 {
	    ifs.ignore(256, '\n');
	 }
	 else if (mode == "v")
	 {
	    ifs >> x;
	    if(minX > x ){
	       minX = x;
	    }if(maxX < x ){
	       maxX = x;
	    }
	    ifs >> y;
	    if(minY > y){
	       minY = y;
	    }if(maxY < y){
	       maxY = y;
	    }
	    ifs >> z;
	    if(minZ > z ){
	       minZ = z;
	    }if(maxZ < z){
	       maxZ = z;
	    }
	    points.push_back(point(x,y,z));
	 }
	 else if (mode == "vt")
	 {
	    ifs >> x1;
	    ifs >> y1;
	    texturePoints.push_back(texturePoint(x1,y1));
	 }
	 else if (mode == "vn")
	 {
	    ifs >> x2;
	    ifs >> y2;
	    ifs >> z2;
	    normals.push_back(normal(x2,y2,z2));
	 }
	 else if (mode == "f")
	 {

	    char temp1[20];
	    ifs>>temp1;
	    int x=0;
	    int y=0;
	    int z=0;
	    point a, b, n;


	    sscanf(temp1, "%d/%d/%d", &x, &y, &z);
	    if(z==0)
	    {
	       sscanf(temp1, "%d//%d", &x, &z);
	    }

	    Va.p=points[x-1];
	    if(y!=0)
	    {
	       Va.t=texturePoints[y-1];
	    }
	    if(z!=0)
	    {
	       Va.n=normals[z-1];
	    }


	    ifs>>temp1;
	    x=0;
	    y=0;
	    z=0;


	    sscanf(temp1, "%d/%d/%d", &x, &y, &z);
	    if(z==0)
	    {
	       sscanf(temp1, "%d//%d", &x, &z);
	    }

	    Vb.p=points[x-1];
	    if(y!=0)
	    {
	       Vb.t=texturePoints[y-1];
	    }
	    if(z!=0)
	    {
	       Vb.n=normals[z-1];
	    }


	    ifs>>temp1;
	    x=0;
	    y=0;
	    z=0;


	    sscanf(temp1, "%d/%d/%d", &x, &y, &z);
	    if(z==0)
	    {
	       sscanf(temp1, "%d//%d", &x, &z);
	    }

	    Vc.p=points[x-1];

	    if(y!=0)
	    {
	       Vc.t=texturePoints[y-1];
	    }
	    if(z!=0)
	    {
	       Vc.n=normals[z-1];
	    }
	    else
	    {
	       //compute normal
	       a.x=Va.p.x-Vc.p.x;
	       a.y=Va.p.y-Vc.p.y;
	       a.z=Va.p.z-Vc.p.z;

	       b.x=Va.p.x-Vb.p.x;
	       b.y=Va.p.y-Vb.p.y;
	       b.z=Va.p.z-Vb.p.z;

	       n.x=(a.y*b.z)-(a.z*b.y);
	       n.y=(a.z*b.x)-(a.x*b.z);
	       n.z=(a.x*b.y)-(a.y*b.x);

	       Va.n.x=-n.x;
	       Va.n.y=-n.y;
	       Va.n.z=-n.z;

	       Vb.n.x=-n.x;
	       Vb.n.y=-n.y;
	       Vb.n.z=-n.z;

	       Vc.n.x=-n.x;
	       Vc.n.y=-n.y;
	       Vc.n.z=-n.z;
	    }
	    //add the face to the vector	    
	    triangles.push_back(triangle(Va, Vb, Vc));
	 }
      }
   }
}

int main(int argc, char** argv){
   if(!(argc == 3)){
      printf("usage: ./project <vertex shader> <fragment shader> \n");
      return 0;
   }

   vertexShader   = std::string(argv[1]);
   fragmentShader = std::string(argv[2]);

   load_obj("meshes/apple.obj");


   // Initialize GLUT.
   glutInit(&argc, argv);
   glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowPosition(20, 20);
   glutInitWindowSize(640, 480);
   glutCreateWindow("CS148 Final Project");

   //
   // Initialize GLEW.
   //
#if !defined(__APPLE__) && !defined(__linux__)
   glewInit();
   if(!GLEW_VERSION_2_0) {
      printf("Your graphics card or graphics driver does\n"
	    "\tnot support OpenGL 2.0, trying ARB extensions\n");

      if(!GLEW_ARB_vertex_shader || !GLEW_ARB_fragment_shader) {
	 printf("ARB extensions don't work either.\n");
	 printf("\tYou can try updating your graphics drivers.\n"
	       "\tIf that does not work, you will have to find\n");
	 printf("\ta machine with a newer graphics card.\n");
	 exit(1);
      }
   }
#endif

   Setup();
   createTexture();
   loadTexture("./textures/paintTexture.png");
   glutDisplayFunc(DisplayCallback);
   glutReshapeFunc(ReshapeCallback);
   glutMouseFunc(mouseButton);
   glutMotionFunc(mouseMotion);
   glutKeyboardFunc(KeyCallback);
   glutIdleFunc(DisplayCallback);

   glutMainLoop();
   return 0;
}

//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "Arbol.h"
#include "InputManagement.h"
#include "Player.h"
#include "Cola.h"

//-----------------------------------------------------------------------------




class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader;
   GLuint ProgramObject;
   clock_t time0,time1;
   float timer010;  // timer counting 0->1->0
   bool bUp;        // flag if counting up or down.
   Arbol* arbol;
   Player* player;
   Cola* cola;
   float delta; //tiempo transcurrido desde el ultimo frame

public:
	myWindow(){}

	virtual void OnRender(void)
	{
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.09; //for screenshot!
      glPushMatrix();
      if (shader) shader->begin();
         glTranslatef(3, -3, -8);
         cola->dibujarCola(30, 6, 0, 0, 0);
         //glRotatef(timer010 * 3600, 500 * timer010, timer010*1.0f, 0.1f);
         
         //Jugador
/*
         player->Move(InputManagement::GetAxisX()*delta, InputManagement::GetAxisY()*delta);
         player->Dibujar();


         //TRIANGULO EQUILATERO
         glBegin(GL_TRIANGLES);
         glVertex3f(-1.5, 0+3, -3);
         glVertex3f(0, 2.12+3, -3);
         glVertex3f(1.5, 0+3, -3);
         glEnd();

         glPushMatrix(); //cubo 1
             
             glTranslatef(-2.598076211, 3.0f, 0.0f);
             glRotatef(-45, -1, 0.5, 1);
             glutSolidCube(0.5f);
         glPopMatrix();

         glPushMatrix(); //cubo 2
             
             glTranslatef(2.598076211, 3.0f, 0.0f);
             glRotatef(45, 1, -1, 1);
             glutSolidCube(0.5f);
         glPopMatrix();


         glPushMatrix(); //tetera 1
             glRotatef(180, 0, 1, 0);
             glTranslatef(-3, 0.0f, 0.0f);
             glutSolidTeapot(0.5);
         glPopMatrix();
            
         glPushMatrix(); //tetera 2
             glRotatef(180, 0, 1, 0);
             glTranslatef(3, 0.0f, 0.0f);
             glutSolidTeapot(0.5);
         glPopMatrix();

         glPushMatrix(); //tetera 3
             glRotatef(180, 0, 1, 0);
             glTranslatef(0, -3, 0.0f);
             glutSolidTeapot(0.5);
         glPopMatrix();

         glPopMatrix();
         */
      if (shader) shader->end();



      glutSwapBuffers();
      glPopMatrix();

      UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
        arbol = new Arbol();
        player = new Player();

		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		if (shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";
      else
      {
         ProgramObject = shader->GetProgramObject();
      }

      time0 = clock();
      timer010 = 0.0f;
      bUp = true;

      DemoLight();

	}

	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(45,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,0.0f,4.0f, 
		          0.0,0.0,-1.0,
			       0.0f,1.0f,0.0f);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		} 

        if (cAscii >= 'A' && cAscii <= 'Z') // si esta en mayuscula
            cAscii -= ('A' - 'a'); //pasar a minuscula

        if (cAscii == 'w')
        {
            std::cout << "Presionando w" << std::endl;
            InputManagement::SetKey('w', true);
        }
        if (cAscii == 'a')
        {
            std::cout << "Presionando a" << std::endl;
            InputManagement::SetKey('a', true);
        }
        if (cAscii == 's')
        {
            std::cout << "Presionando s" << std::endl;
            InputManagement::SetKey('s', true);
        }
        if (cAscii == 'd')
        {
            std::cout << "Presionando d" << std::endl;
            InputManagement::SetKey('d', true);
        }
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
      /*if (cAscii == 's')      // s: Shader
         shader->enable();
      else if (cAscii == 'f') // f: Fixed Function
         shader->disable();
      */
      if (cAscii >= 'A' && cAscii <= 'Z') // si esta en mayuscula
         cAscii -= ('A' - 'a'); //pasar a minuscula

      if (cAscii == 'w')
      {
          std::cout << "Soltando w" << std::endl;
          InputManagement::SetKey('w', false);
      }
      if (cAscii == 'a')
      {
          std::cout << "Soltando a" << std::endl;
          InputManagement::SetKey('a', false);
      }
      if (cAscii == 's')
      {
          std::cout << "Soltando s" << std::endl;
          InputManagement::SetKey('s', false);
      }
      if (cAscii == 'd')
      {
          std::cout << "Soltando d" << std::endl;
          InputManagement::SetKey('d', false);
      }
	}

   void UpdateTimer()
   {
      time1 = clock();

      //globalizamos esta variable para usarla en input
      delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
     
     // Light model parameters:
     // -------------------------------------------
     
     GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
     
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
     
     // -------------------------------------------
     // Spotlight Attenuation
     
     GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
     GLint spot_exponent = 30;
     GLint spot_cutoff = 180;
     
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
     glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
     glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    
     GLfloat Kc = 1.0;
     GLfloat Kl = 0.0;
     GLfloat Kq = 0.0;
     
     glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
     glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);
     
     
     // ------------------------------------------- 
     // Lighting parameters:

     GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
     GLfloat light_Ka[]  = {1.0f, 0.5f, 0.5f, 1.0f};
     GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
     GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};

     glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
     glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

     // -------------------------------------------
     // Material parameters:

     GLfloat material_Ka[] = {0.5f, 0.0f, 0.0f, 1.0f};
     GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
     GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
     GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
     GLfloat material_Se = 20.0f;

     //GLfloat material_Ka[] = { 1.0f, 1.0f, 0.0f, 1.0f };
     //GLfloat material_Kd[] = { 1.0f, 1.0f, 0.0f, 1.0f };
     //GLfloat material_Ks[] = { 1.0f, 1.0f, 0.0f, 1.0f };
     //GLfloat material_Ke[] = { 1.0f, 1.0f, 0.0f, 0.0f };
     //GLfloat material_Se = 0.0f;

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
   }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------


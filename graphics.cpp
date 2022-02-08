// OpenGL/GLUT starter kit for Windows 7 and Visual Studio 2010
// Created spring, 2011
//
// This is a starting point for OpenGl applications.
// Add code to the "display" function below, or otherwise
// modify this file to get your desired results.
//
// For the first assignment, add this file to an empty Windows Console project
//		and then compile and run it as is.
// NOTE: You should also have glut.h,
// glut32.dll, and glut32.lib in the directory of your project.
// OR, see GlutDirectories.txt for a better place to put them.

#include <cmath>
#include <cstring>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glut.h"
#include "maze.h"
#include "rat.h"
#include "graphics.h"


// Global Variables (Only what you need!)
viewType current_view = top_view;
double screen_x = 700;
double screen_y = 500;
Maze gMaze;
Rat gRat;

const int num_textures = 3;
unsigned int texName[num_textures];


// 
// Functions that draw basic primitives
//
void DrawCircle(double x1, double y1, double radius)
{
	glBegin(GL_POLYGON);
	for(int i=0; i<32; i++)
	{
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

void DrawRectangle(double x1, double y1, double x2, double y2)
{
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex2d(x1, y1);
	glTexCoord2f(1, 1); glVertex2d(x2,y1);
	glTexCoord2f(1, 0); glVertex2d(x2,y2);
	glTexCoord2f(0, 0); glVertex2d(x1,y2);
	glEnd();
}

void DrawLine(double x1, double y1, double x2, double y2)
{
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glEnd();
}

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glVertex2d(x3,y3);
	glEnd();
}

void DrawCube(double x1, double y1, double z1, double x2, double y2, double z2, bool column)
{
	if (column) {
		glBindTexture(GL_TEXTURE_2D, texName[2]);
		glEnable(GL_TEXTURE_2D);

		glBegin(GL_QUADS);

		// left wall
		glTexCoord2f(0, 5); glVertex3d(x1, y1, z1);
		glTexCoord2f(1, 5); glVertex3d(x1, y2, z1);
		glTexCoord2f(1, 0); glVertex3d(x1, y2, z2);
		glTexCoord2f(0, 0); glVertex3d(x1, y1, z2);

		// right wall
		glTexCoord2f(0, 5); glVertex3d(x2, y1, z1);
		glTexCoord2f(1, 5); glVertex3d(x2, y2, z1);
		glTexCoord2f(1, 0); glVertex3d(x2, y2, z2);
		glTexCoord2f(0, 0); glVertex3d(x2, y1, z2);

		// celing
		glTexCoord2f(0, 1); glVertex3d(x1, y1, z2);
		glTexCoord2f(1, 1); glVertex3d(x1, y2, z2);
		glTexCoord2f(1, 0); glVertex3d(x2, y2, z2);
		glTexCoord2f(0, 0); glVertex3d(x2, y1, z2);

		// floor
		glVertex3d(x1, y1, z1);
		glVertex3d(x1, y2, z1);
		glVertex3d(x2, y2, z1);
		glVertex3d(x2, y1, z1);

		// top wall
		glTexCoord2f(0, 5); glVertex3d(x1, y2, z1);
		glTexCoord2f(1, 5); glVertex3d(x2, y2, z1);
		glTexCoord2f(1, 0); glVertex3d(x2, y2, z2);
		glTexCoord2f(0, 0); glVertex3d(x1, y2, z2);

		// bottom wall
		glTexCoord2f(0, 5); glVertex3d(x1, y1, z1);
		glTexCoord2f(1, 5); glVertex3d(x2, y1, z1);
		glTexCoord2f(1, 0); glVertex3d(x2, y1, z2);
		glTexCoord2f(0, 0); glVertex3d(x1, y1, z2);
		glEnd();
	}
	else {
		glBindTexture(GL_TEXTURE_2D, texName[1]);
		glEnable(GL_TEXTURE_2D);

		glBegin(GL_QUADS);

		// left wall
		glTexCoord2f(0, 1); glVertex3d(x1, y1, z1);
		glTexCoord2f(1, 1); glVertex3d(x1, y2, z1);
		glTexCoord2f(1, 0); glVertex3d(x1, y2, z2);
		glTexCoord2f(0, 0); glVertex3d(x1, y1, z2);

		// right wall
		glTexCoord2f(0, 1); glVertex3d(x2, y1, z1);
		glTexCoord2f(1, 1); glVertex3d(x2, y2, z1);
		glTexCoord2f(1, 0); glVertex3d(x2, y2, z2);
		glTexCoord2f(0, 0); glVertex3d(x2, y1, z2);

		// celing
		glTexCoord2f(0, 1); glVertex3d(x1, y1, z2);
		glTexCoord2f(1, 1); glVertex3d(x1, y2, z2);
		glTexCoord2f(1, 0); glVertex3d(x2, y2, z2);
		glTexCoord2f(0, 0); glVertex3d(x2, y1, z2);

		// floor
		glVertex3d(x1, y1, z1);
		glVertex3d(x1, y2, z1);
		glVertex3d(x2, y2, z1);
		glVertex3d(x2, y1, z1);

		// top wall
		glTexCoord2f(0, 1); glVertex3d(x1, y2, z1);
		glTexCoord2f(1, 1); glVertex3d(x2, y2, z1);
		glTexCoord2f(1, 0); glVertex3d(x2, y2, z2);
		glTexCoord2f(0, 0); glVertex3d(x1, y2, z2);

		// bottom wall
		glTexCoord2f(0, 1); glVertex3d(x1, y1, z1);
		glTexCoord2f(1, 1); glVertex3d(x2, y1, z1);
		glTexCoord2f(1, 0); glVertex3d(x2, y1, z2);
		glTexCoord2f(0, 0); glVertex3d(x1, y1, z2);
		glEnd();
	}
}

// Outputs a string of text at the specified location.
void DrawText(double x, double y, const char *string)
{
	void *font = GLUT_BITMAP_9_BY_15;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	
	int len, i;
	glRasterPos2d(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) 
	{
		glutBitmapCharacter(font, string[i]);
	}

    glDisable(GL_BLEND);
}


//
// GLUT callback functions
//

void SetTopView(int w, int h)
{
	// go into 2d mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double world_margin_x = 0.5;
	double world_margin_y = 0.5;
	gluOrtho2D(-world_margin_x, W + world_margin_x,
		-world_margin_y, H + world_margin_y);
	glMatrixMode(GL_MODELVIEW);
}

void SetPerspectiveView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (GLdouble)w / (GLdouble)h;
	gluPerspective(
		/* field of view in degree */ 38.0,
		/* aspect ratio */ aspectRatio,
		/* Z near */ .1, /* Z far */ 30.0);
	glMatrixMode(GL_MODELVIEW);
}

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (current_view == perspective_view) {
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		gluLookAt(-3,-3,7, 3,3,0, 0,0,1);
	}
	else if (current_view == top_view) {
		glDisable(GL_DEPTH_TEST);
		glLoadIdentity();
	}
	else { // rat view
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		double z = .25;
		double x = gRat.GetX();
		double y = gRat.GetY();
		double dx = gRat.GetDX();
		double dy = gRat.GetDY();
		double at_x = x + dx;
		double at_y = y + dy;
		double at_z = z;
		gluLookAt(x,y,z, at_x,at_y,at_z, 0,0,1);
	}

	glColor3d(0, 0, 1);
	if (IsKeyPressed('w')) {
		gRat.MoveForward(gMaze, GetDeltaTime());
		/*if (!gMaze.OnWall(gRat.GetNextX(), gRat.GetNextY(), gRat.GetRadius()))
			gRat.MoveForward();
		else if (!gMaze.OnWall(gRat.GetNextX(), gRat.GetY(), gRat.GetRadius()))
			gRat.SetX(gRat.GetNextX());
		else if (!gMaze.OnWall(gRat.GetX(), gRat.GetNextY(), gRat.GetRadius()))
			gRat.SetY(gRat.GetNextY());*/
	}
	/*else if (IsKeyPressed('s')) {
		if (gMaze.IsSafe(gRat.GetNextX(), gRat.GetNextY(), gRat.GetRadius()))
			gRat.MoveBackward();
		else if (gMaze.IsSafe(gRat.GetNextX(), gRat.GetY(), gRat.GetRadius()))
			gRat.SetX(gRat.GetNextX());
		else if (gMaze.IsSafe(gRat.GetX(), gRat.GetNextY(), gRat.GetRadius()))
			gRat.SetY(gRat.GetNextY());
	}*/
	if (IsKeyPressed('c'))
		gRat.MoveRight(gMaze, GetDeltaTime());
	if (IsKeyPressed('z'))
		gRat.MoveLeft(gMaze, GetDeltaTime());

	if (IsKeyPressed('a'))
		gRat.RotateLeft(GetDeltaTime());
	if (IsKeyPressed('d'))
		gRat.RotateRight(GetDeltaTime());
	if (IsKeyPressed('q'))
		exit(0);
	if (IsKeyPressed('r')) {
		current_view = rat_view;
		SetPerspectiveView(screen_x, screen_y);
	}
	if (IsKeyPressed('t')) {
		current_view = top_view;
		SetTopView(screen_x, screen_y);
	}
	if (IsKeyPressed('p')) {
		current_view = perspective_view;
		SetPerspectiveView(screen_x, screen_y);
	}

	gMaze.Draw();
	gRat.Draw();
	

	glutSwapBuffers();
	glutPostRedisplay();
}


// reshape:
void reshape(int w, int h)
{
	screen_x = w;
	screen_y = h;
	glViewport(0, 0, w, h);

	if (current_view == top_view)
	{
		SetTopView(w, h);
	}
	else if (current_view == perspective_view)
	{
		SetPerspectiveView(w, h);
	}
	else // current_view == rat_view
	{
		SetPerspectiveView(w, h);
	}
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
	switch (c) 
	{
		case 27: // escape character means to quit the program
			std::exit(0);
			break;
		case 'b':
			// do something when 'b' character is hit.
			break;
		case 'w':
			gRat.MoveForward(gMaze, GetDeltaTime());
			break;
		case 's':
			gRat.MoveBackward();
		case 'a':
			gRat.RotateLeft(GetDeltaTime());
			break;
		case 'd':
			gRat.RotateRight(GetDeltaTime());
			break;
		default:
			return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever the window is resized by the user.

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
	}
	glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
	gMaze.RemoveWalls();

	// texture init
	const char max_file_size = 100;
	char imageFiles[num_textures][max_file_size] = {"grate.jpg", "maze_wall.jpg", "column.jpg"};

	glGenTextures(num_textures, texName);

	for (int i = 0; i < num_textures; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texName[i]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(imageFiles[i], &width, &height, &nrChannels, 0);
		if (data)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
			// NOTE: If the above command doesn't work, try it this way:
				//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				//glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(50, 50);

	int fullscreen = 0;
	if (fullscreen) 
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	} 
	else 
	{
		glutCreateWindow("This appears in the title bar");
	}

	glutDisplayFunc(display);
	//glutKeyboardFunc(keyboard);
	InitKeyboard();
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glColor3d(0,0,0); // forground color
	glClearColor(1, 1, 1, 0); // background color
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
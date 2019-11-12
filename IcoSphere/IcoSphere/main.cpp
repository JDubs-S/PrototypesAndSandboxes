/* *****************************************************************************
 *
 * Copyright (C) 2014 Jason William Staiert. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, see <https://www.gnu.org/licenses>.
 *
 * Chagne Date        Description
 * -----------------------------------------------------------------------------
 * Aug 19, 2019 |---| added license notice
 *
 * ****************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// Main for macOS builds.
//
////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <OpenGL/OpenGL.h>   // OpenGL Library
#include <GLUT/glut.h>       // GLUT Library

////////////////////////////////////////////////////////////////////////////////
//
// Initialize IcoSphere objects.
//
////////////////////////////////////////////////////////////////////////////////
#include "RotationAxis.h"
#include "IcosMap.h"
#include "IcosMapView.h"
#include "Matrix.h"
#include "RenderContext.h"

IcosMap g_Map;
IcosMapView g_MapView;
RotationAxis g_RotX(1.0f, 0.0f, 0.0f);
RotationAxis g_RotY(0.0f, 1.0f, 0.0f);
RotationAxis g_RotZ(0.0f, 0.0f, 1.0f);
CMatrix g_MatRotX;
CMatrix g_MatRotY;
CMatrix g_MatRotZ;
RenderContext g_RC;
bool g_StopRotation = true;

const int gc_WindowWidth	= 600;
const int gc_WindowHeight	= 600;

/* *****************************************************************************
 * *****************************************************************************
 *
 * Code below this line is derived from the "OpenGL Gears" example application.
 *
 * *****************************************************************************
 * ****************************************************************************/

static F32 g_AngleX = 0.0f;
static F32 g_AngleY = 0.0f;

static GLfloat g_ViewRotX = 0.0f;

static GLint g_Matrix = -1;
static GLint g_AttrPos = 0;
static GLint g_AttrColor = 1;

/* *****************************************************************************
 * This function is a nearly verbatim copy of the make_z_rot_matrix function
 * from the "OpenGL Gears" example application.
 * ****************************************************************************/
static void MakeZRotMatrix(GLfloat angle, GLfloat *m)
{
	float c = cos(angle * M_PI / 180.0f);
	float s = sin(angle * M_PI / 180.0f);

	for (int i = 0; i < 16; i++)
    {
		m[i] = 0.0f;
    }

	m[0] = m[5] = m[10] = m[15] = 1.0f;

	m[0] = c;
	m[1] = s;
	m[4] = -s;
	m[5] = c;
}

/* *****************************************************************************
 * This function is a nearly verbatim copy of the make_scale_matrix function
 * from the "OpenGL Gears" example application.
 * ****************************************************************************/
static void MakeScaleMatrix(GLfloat xs, GLfloat ys, GLfloat zs, GLfloat *m)
{
	for (int i = 0; i < 16; i++)
    {
		m[i] = 0.0f;
    }

	m[0] = xs;
	m[5] = ys;
	m[10] = zs;
	m[15] = 1.0f;
}

/* *****************************************************************************
 * This function is a nearly verbatim copy of the matrix_multiply function
 * from the "OpenGL Gears" example application.
 * ****************************************************************************/
static void MatrixMultiply(GLfloat *prod, const GLfloat *a, const GLfloat *b)
{
#define A(row,col)  a[(col<<2)+row]
#define B(row,col)  b[(col<<2)+row]
#define P(row,col)  p[(col<<2)+row]
	GLfloat p[16];
	for (GLint i = 0; i < 4; i++)
    {
		const GLfloat ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
		P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
		P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
		P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
		P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
	}
	memcpy(prod, p, sizeof(p));
#undef A
#undef B
#undef PROD
}

/* *****************************************************************************
 * This function is a nearly verbatim copy of the create_shaders function from
 * the "OpenGL Gears" example application.
 * ****************************************************************************/
static void CreateShaders(void)
{
	static const char *fragShaderText =
	"varying vec4 v_color;\n"
	"void main() {\n"
	"   gl_FragColor = v_color;\n"
	"}\n";
	static const char *vertShaderText =
	"uniform mat4 modelviewProjection;\n"
	"attribute vec4 pos;\n"
	"attribute vec4 color;\n"
	"varying vec4 v_color;\n"
	"void main() {\n"
	"   gl_Position = modelviewProjection * pos;\n"
	"   v_color = color;\n"
	"}\n";

	GLuint fragShader, vertShader, program;
	GLint stat;

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, (const char **) &fragShaderText, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &stat);
	if (!stat) {
		printf("Error: fragment shader did not compile!\n");
		exit(1);
	}

	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, (const char **) &vertShaderText, NULL);
	glCompileShader(vertShader);
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &stat);
	if (!stat) {
		printf("Error: vertex shader did not compile!\n");
		exit(1);
	}

	program = glCreateProgram();
	glAttachShader(program, fragShader);
	glAttachShader(program, vertShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &stat);
	if (!stat) {
		char log[1000];
		GLsizei len;
		glGetProgramInfoLog(program, 1000, &len, log);
		printf("Error: linking:\n%s\n", log);
		exit(1);
	}

	glUseProgram(program);

    glBindAttribLocation(program, g_AttrPos, "pos");
    glBindAttribLocation(program, g_AttrColor, "color");
    glLinkProgram(program);

	g_Matrix = glGetUniformLocation(program, "modelviewProjection");
}

/* *****************************************************************************
 *
 * ****************************************************************************/
GLvoid InitGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)gc_WindowWidth/(GLfloat)gc_WindowHeight,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);

	CreateShaders();
}

/* *****************************************************************************
 *
 * ****************************************************************************/
GLvoid DrawGLScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat mat[16], rot[16], scale[16];

    if (!g_StopRotation)
    {
        g_AngleX += 0.01;
        g_AngleY += 0.001;
    }

	g_RotX.GetRotationMatrix(g_AngleX, g_MatRotX);
	g_RotY.GetRotationMatrix(g_AngleY, g_MatRotY);

	MakeZRotMatrix(g_ViewRotX, rot);
	MakeScaleMatrix(1.0, 1.0, 1.0, scale);
	MatrixMultiply(rot, (GLfloat *)g_MatRotX.M, (GLfloat *)g_MatRotY.M);
	MatrixMultiply(mat, rot, scale);

	glUniformMatrix4fv(g_Matrix, 1, GL_FALSE, mat);

	g_RC.Reset();

	g_MapView.Render(g_RC);

    glutPostRedisplay();
	
    glFlush();
}

/* *****************************************************************************
 *
 * ****************************************************************************/
GLvoid ReSizeGLScene(int width, int height)
{
    glViewport (0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
    gluPerspective(45.0, (GLfloat) width / (GLfloat) height, 0.1, 100.0);
	
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* *****************************************************************************
 *
 * ****************************************************************************/
GLvoid KeyboardHandle(unsigned char key, int x, int y)
{
	switch (key)
    {
    case 27:
        exit(0);
        break;
    case 0x20:
        g_StopRotation = !g_StopRotation;
        break;
	}
}

/* *****************************************************************************
 *
 * ****************************************************************************/
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (gc_WindowWidth, gc_WindowHeight);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
	
	InitGL();

	g_Map.Initialize(50u);
    g_Map.GenerateElevations();
	g_MapView.SetMap(g_Map);

    glutDisplayFunc(DrawGLScene);
    glutReshapeFunc(ReSizeGLScene);
	glutKeyboardFunc(KeyboardHandle);
	
    glutMainLoop();
    
    return 0;
}

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/

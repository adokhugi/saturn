#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
#include "Bitmap.h"

#define MINIMALANGLE 2 * 3.1415926535 / 13

class Sphere
{
public:
	void NewGame (GLuint *texture_number_game, int n = 20);
	void RotateFields (bool updateHistory = true);
	void Rotate (bool dir = true, bool updateHistory = true);
	void Draw (float angleFields, float angleSphere);
	bool UndoMove ();
	bool IsSolved ();
	void Save (FILE *file);
	void Load (FILE *file, GLuint *texture_number_game);

private:
	struct Point 
	{
		float x;
		float y;
	};

	struct Field
	{
		int number;
		bool colour;
		Point p_bl, p_br, p_tr, p_tl;
	};

	void Initialize (GLuint *texture_number_game);
	void DrawField (int i);
	void Swap (int p1, int p2);
	void Invert (int p);

	char history [20000];
	int historyPtr;
	Field field [13];
	int pos;
	GLuint texture_number [13];
	TextObject textObject;
};

#endif
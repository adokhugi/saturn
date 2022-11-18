#include "sphere.h"

void Sphere::Initialize (GLuint *texture_number_game)
{
	int i;
	float angle_cur, angle_next = 0;
	const float radius1 = 1.0f, radius2 = radius1 + .2f;

	for (i = 0; i < 13; i++)
	{
		field [i].number = i;
		field [i].colour = true;
		angle_cur = angle_next;
		angle_next = (i + 1) * MINIMALANGLE;
		field [i].p_bl.x = radius1 * cos (angle_cur);
		field [i].p_bl.y = radius1 * sin (angle_cur);
		field [i].p_br.x = radius1 * cos (angle_next);
		field [i].p_br.y = radius1 * sin (angle_next);
		field [i].p_tr.x = radius2 * cos (angle_next);
		field [i].p_tr.y = radius2 * sin (angle_next);
		field [i].p_tl.x = radius2 * cos (angle_cur);
		field [i].p_tl.y = radius2 * sin (angle_cur);
	}

	pos = 0;

	for (i = 20000; i; )
	{
		i--;
		history [i] = 0;
	}
	historyPtr = 0;

	for (int i = 0; i < 13; i++)
		texture_number [i] = texture_number_game [i];
}

void Sphere::NewGame (GLuint *texture_number_game, int n)
{
	Initialize (texture_number_game);

	for (int i = 0; i < n; i++)
	{
		pos = rand() % 13;
		history [historyPtr] = pos;
		RotateFields ();
	}
}

void Sphere::RotateFields (bool updateHistory)
{
	int i;

	Swap (pos, pos + 3);
	Swap (pos + 1, pos + 2);
	Swap (pos + 4 + 3, pos + 4 + 3 + 2);
	Invert (pos + 4 + 3 + 1);

	if (updateHistory)
		historyPtr++;
}

void Sphere::Swap (int p1, int p2)
{
	p1 %= 13;
	p2 %= 13;
	int temp = field [p1].number;
	field [p1].number = field [p2].number;
	field [p2].number = temp;
	temp = field [p1].colour;
	field [p1].colour = !field [p2].colour;
	field [p2].colour = !temp;
}

void Sphere::Invert (int p)
{
	p %= 13;
	field [p].colour = !field [p].colour;
}

void Sphere::Rotate (bool dir, bool updateHistory)
{
	if (dir)
	{
		pos--;
		if (pos == -1)
			pos = 12;
	}
	else
	{
		pos++;
		if (pos == 13)
			pos = 0;
	}

	if (updateHistory)
		history [historyPtr] = pos;
}

void Sphere::Draw (float angleFields, float angleSphere)
{
	int i;

	glTranslatef (0.0f, 0.0f, 1.0f);

	// draw fields
	for (i = pos + 4; i < pos + 4 + 3; i++)
		DrawField (i % 13);
	for (i = pos + 4 + 3 + 3; i < pos + 4 + 3 + 3 + 3; i++)
		DrawField (i % 13);

	glRotatef (angleFields, 
		field [(pos + 2) % 13].p_bl.x, 
		field [(pos + 2) % 13].p_bl.y, 
		0.0f);

	for (i = pos; i < pos + 4; i++)
		DrawField (i % 13);
	for (i = pos + 4 + 3; i < pos + 4 + 3 + 3; i++)
		DrawField (i % 13);

	glRotatef (-angleFields, 
		field [(pos + 2) % 13].p_bl.x, 
		field [(pos + 2) % 13].p_bl.y, 
		0.0f);

	glTranslatef (0.0f, 0.0f, -1.0f);

	// draw "sphere"
	glRotatef (angleSphere, 0.0f, 0.0f, 1.0f);

	glColor3f (.6f, .6f, .6f);
	glBegin (GL_POLYGON);
		for (i = pos; i <= pos + 4; i++)
			glVertex3f (field [i % 13].p_bl.x, field [i % 13].p_bl.y, 1.0f);
	glEnd ();

	glBegin (GL_POLYGON);
		for (i = pos + 4 + 3; i <= pos + 4 + 3 + 3; i++)
			glVertex3f (field [i % 13].p_bl.x, field [i % 13].p_bl.y, 1.0f);
	glEnd ();

	glColor3f (.5f, .5f, .5f);
	glBegin (GL_POLYGON);
		for (i = pos + 4; i <= pos + 4 + 3; i++)
			glVertex3f (field [i % 13].p_bl.x, field [i % 13].p_bl.y, 1.0f);
		for (i = pos + 4 + 3 + 3; i <= pos + 4 + 3 + 3 + 3; i++)
			glVertex3f (field [i % 13].p_bl.x, field [i % 13].p_bl.y, 1.0f);
	glEnd ();
}

inline void Sphere::DrawField (int i)
{
	if (field [i].colour)
			glColor3f (1.0f, 1.0f, 1.0f);
	else
			glColor3f (1.0f, 1.0f, 0.0f);

	glBegin (GL_QUADS);
		glVertex3f (field [i].p_bl.x, field [i].p_bl.y, .01f);
		glVertex3f (field [i].p_br.x, field [i].p_br.y, .01f);
		glVertex3f (field [i].p_tr.x, field [i].p_tr.y, .01f);
		glVertex3f (field [i].p_tl.x, field [i].p_tl.y, .01f);
	glEnd ();

	glEnable (GL_TEXTURE_2D);

	glBindTexture (GL_TEXTURE_2D, texture_number [field [i].number]);

	glBegin (GL_QUADS);
		glTexCoord2f (0.0f, 1.0f); glVertex3f (field [i].p_bl.x, field [i].p_bl.y, .01f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f (field [i].p_br.x, field [i].p_br.y, .01f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f (field [i].p_tr.x, field [i].p_tr.y, .01f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (field [i].p_tl.x, field [i].p_tl.y, .01f);
	glEnd ();

	glDisable (GL_TEXTURE_2D);

	if (field [i].colour)
			glColor3f (1.0f, 1.0f, 0.0f);
	else
			glColor3f (1.0f, 1.0f, 1.0f);

	glBegin (GL_QUADS);
		glVertex3f (field [i].p_bl.x, field [i].p_bl.y, -.01f);
		glVertex3f (field [i].p_br.x, field [i].p_br.y, -.01f);
		glVertex3f (field [i].p_tr.x, field [i].p_tr.y, -.01f);
		glVertex3f (field [i].p_tl.x, field [i].p_tl.y, -.01f);
	glEnd ();

	glEnable (GL_TEXTURE_2D);

	glBindTexture (GL_TEXTURE_2D, texture_number [field [i].number]);

	glBegin (GL_QUADS);
		glTexCoord2f (1.0f, 1.0f); glVertex3f (field [i].p_bl.x, field [i].p_bl.y, -.01f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f (field [i].p_br.x, field [i].p_br.y, -.01f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (field [i].p_tr.x, field [i].p_tr.y, -.01f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f (field [i].p_tl.x, field [i].p_tl.y, -.01f);
	glEnd ();

	glDisable (GL_TEXTURE_2D);
}

bool Sphere::UndoMove ()
{
	if (historyPtr)
	{
		historyPtr--;
		pos = history [historyPtr];
		return true;
	}

	return false;
}

bool Sphere::IsSolved ()
{
	int i, first;

	if (field [0].colour)
	{
		for (i = 0; i < 13; i++)
			if (!field [i].colour)
				return false;
	}
	else
	{
		for (i = 0; i < 13; i++)
			if (field [i].colour)
				return false;
	}

	for (first = 0; field [first].number != 1; first++)

	if (field [first].number < field [(first + 1) % 13].number)
	{
		for (i = first + 1; i < first + 12; i++)
			if (field [i % 13].number > field [(i + 1) % 13].number)
				return false;
	}
	else
	{
		for (i = first + 1; i < first + 12; i++)
			if (field [i % 13].number < field [(i + 1) % 13].number)
				return false;
	}

	return true;
}

void Sphere::Save (FILE *file)
{
	for (int i = 0; i < historyPtr; i++)
		fputc (history [i], file);
}

void Sphere::Load (FILE *file, GLuint *texture_number_game)
{
	int temp;

	Initialize (texture_number_game);
	
	for (historyPtr = 0; (temp = fgetc (file)) != EOF; )
	{
		pos = temp;
		history [historyPtr] = pos;
		RotateFields ();
	}
}

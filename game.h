#ifndef _GAME_H_
#define _GAME_H_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

#include "NeHeGL.h"
#include "NeHe_Window.h"
#include "sphere.h"
#include "Bitmap.h"

class Game
{
public:
	bool Initialize (GL_Window *window, Keys *keys, DWORD tickCount);
	void Deinitialize ();
	void Update (DWORD tickCount, DWORD lastTickCount);
	void Draw (DWORD tickCount);
	void EnterMenu (DWORD tickCount);

private:
	enum GameState
	{
		ActualGame,
		Menu,
		Instructions,
		Credits,
		Difficulty,
		Load,
		Save
	};

	void NewGame ();
	inline void EnterVictory (DWORD tickCount);
	bool SaveGame (DWORD tickCount);
	void LoadGame (int number, DWORD tickCount);
	void CreateFilename (int number, char *filename);
	char *CalculateTimeDisplay (float m);
	bool FileExists (char *filename);
	inline void Update_ActualGame (DWORD tickCount, DWORD lastTickCount);
	inline void Update_Load (DWORD tickCount, DWORD lastTickCount);
	inline void Update_Save (DWORD tickCount, DWORD lastTickCount);
	inline void Update_Difficulty (DWORD tickCount, DWORD lastTickCount);
	inline void Update_Menu (DWORD tickCount, DWORD lastTickCount);
	inline void Update_Instructions (DWORD tickCount, DWORD lastTickCount);
	inline void Update_Credits (DWORD tickCount, DWORD lastTickCount);
	inline void Draw_ActualGame (DWORD tickCount);
	inline void Draw_Load (DWORD tickCount);
	inline void Draw_Save (DWORD tickCount);
	inline void Draw_Difficulty (DWORD tickCount);
	inline void Draw_Menu (DWORD tickCount);
	inline void Draw_Instructions (DWORD tickCount);
	inline void Draw_Credits (DWORD tickCount);
	inline void EnterLoad ();
	void UpdateStepsDisplay ();
	void UpdateGameNumberDisplay ();
	void UpdateDifficultyDisplay ();
	void InitKeyPressed ();
	void RenderMenuItem (int i);
	void UpdateMenuDisplay ();
	void LeaveActualGame (DWORD tickCount);
	void ReturnToActualGame (DWORD tickCount);

	float anim0_dur;
	float anim1_dur;
	GL_Window *g_window;
	Keys *g_keys;
	Sphere sphere;
	int angle;
	int targetAngle;
	int angleFrontFace;
	float rotationStartTickCount;
	bool frontFaceRotating;
	Bitmap bitmap_game [4];
	GLuint texture_game [4];
	bool cheatMode;
	bool updateHistory;
	int cheatCodePtr;
	float startTime;
	float initTime;
	float zzoom;
	TextObject textObject;
	int steps;
	GameState state;
	float endTime;
	int endSteps;
	float elapsedTime;
	bool nPressed;
	bool sPressed;
	bool lPressed;
	bool lPressedCheat;
	bool escPressed;
	bool spacePressed;
	bool leftPressed;
	bool rightPressed;
	bool victory;
	int selectedGame;
	Bitmap bitmap_load [2];
	GLuint texture_load [2];
	Bitmap bitmap_save [2];
	GLuint texture_save [2];
	Bitmap bitmap_difficulty [2];
	GLuint texture_difficulty [2];
	int selectedDifficulty;
	float tempTimer;
	Bitmap bitmap_menu [7];
	GLuint texture_menu [7];
	int selectedMenuItem;
	Bitmap bitmap_instructions;
	GLuint texture_instructions;
	Bitmap bitmap_credits;
	GLuint texture_credits;
	float cursorPos;
	bool music_playing;
	bool dir;
	Bitmap bitmap_number [13];
	GLuint texture_number [13];
};

#endif
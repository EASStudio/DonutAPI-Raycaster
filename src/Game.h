#pragma once

class Game
{
public:
	void Init();
	void Run();
	void Shutdown();

private:
	bool appIsRunning = false;

	bool editorActive = false;

	enum EditorState 
	{
		TILE,
		SECTOR,
		SLOPE,
		WALL_HEIGHT,
		PORTAL       // TODO: Add portal stuff
	};

	struct Editor 
	{
		int postionX = 0;
		int postionY = 0;
		float sensitivity = 0.1f;

		int selectedTile = 1;
		int selectedSector = 1;
		float zoom = 1.0f;       // zoom multiplier
		int viewOffsetX = 0;     // scroll offset in cells
		int viewOffsetY = 0;

		bool enabled = false;
		bool editCeil = false; // Toggle floor/ceil editing
		EditorState state = TILE;
	};
	Editor editor;

	void DrawEditor();
	void DrawSlopeDir(int screenX, int screenY, int sec, int cellW, int cellH);
	void EditorInput();
	void SaveMap();
	void LoadMap();
};
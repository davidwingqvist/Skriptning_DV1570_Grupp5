#pragma once

/*
	Call C++ functions within LUA

	structure:
		parameter: lua_State
		return: int				- amount of results to return
*/

/*
	Function that can be called in LUA
	regarding sprites
*/
int L_LoadSprite(lua_State* L);
int L_ChangeSprite(lua_State* L);
int L_RemoveSprite(lua_State* L);
int L_SetSpriteVisible(lua_State* L);
int L_SetSpritePosition(lua_State* L);
int L_SetSpriteScale(lua_State* L);
int L_SetSpriteRotation(lua_State* L);
int L_SetSpriteBlinking(lua_State* L);

/*
	Collision
*/
int L_CheckSpriteCollision(lua_State* L);
int L_SetSpriteCollision(lua_State* L);
int L_SetColliderSize(lua_State* L);

/*
	Application window
*/
int L_GetWindowWidth(lua_State* L);
int L_GetWindowHeight(lua_State* L);

/*
	Camera
*/
namespace CAM
{
	int L_CreateCamera(lua_State* L);
	int L_SetCameraPosition(lua_State* L);
	int L_SetCameraTarget(lua_State* L);
	int L_SetCameraZoom(lua_State* L);
};


int L_ChangeScene(lua_State* L);

namespace GUI
{
	// Text
	int L_AddText(lua_State* L);
	int L_SetTextPosition(lua_State* L);
	int L_SetTextSize(lua_State* L);
	int L_UpdateText(lua_State* L);
	int L_SetTextAlignment(lua_State* L);
	int L_SetTextFont(lua_State* L);
	
	// Buttons
	int L_AddButton(lua_State* L);
	int L_IsButtonPressed(lua_State* L);
	int L_RemoveButton(lua_State* L);
	int L_SetButtonPosition(lua_State* L);
	int L_SetButtonSize(lua_State* L);
	int L_SetButtonText(lua_State* L);
	int L_SetButtonFont(lua_State* L);
	int L_SetButtonImage(lua_State* L);

	// 2D image
	int L_Add2dImage(lua_State* L);
	int L_RemoveImage2d(lua_State* L);
	int L_Change2dImage(lua_State* L);
	int L_SetImage2dPosition(lua_State* L);
	int L_SetImage2dScale(lua_State* L);
};

// Graphical Interface wrapper
int L_UpdateGraphicalInterface(lua_State* L);
int	L_AddHealthbarUI(lua_State* L);
int L_SetHealthbarMax(lua_State* L);
int L_SetHealthbarBackgroundColor(lua_State* L);
int L_SetHealthbarForegroundColor(lua_State* L);
int L_SetHealthbarVisibility(lua_State* L);
int L_UpdatePosUI(lua_State* L);
int L_RemoveUI(lua_State* L);
int L_ToggleRenderUI(lua_State* L);

// Input
int L_IsKeyDown(lua_State* L);
int L_IsKeyPressedOnce(lua_State* L);
int L_IsKeyReleasedOnce(lua_State* L);

// Mouse position
int L_GetScreenCoords(lua_State* L);
int L_GetWorldCoords(lua_State* L);

// Editor
int L_AddGridsystem(lua_State* L);
int L_IsTileOccupied(lua_State* L);
int L_AddTile(lua_State* L);
int L_RemoveTile(lua_State* L);
int L_GetTileID(lua_State* L);
int L_UpdateTilePos(lua_State* L);
int L_GetTilePos(lua_State* L);
int L_ResetGridsystem(lua_State* L);
int L_SetGridLayer(lua_State* L);

int L_GridSetHoverSprite(lua_State* L);
int L_GridUpdateHover(lua_State* L);


int L_GetScreenFromWorld(lua_State* L);

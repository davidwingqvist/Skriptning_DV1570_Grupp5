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
int L_RemoveSprite(lua_State* L);
int L_SetSpritePosition(lua_State* L);
int L_SetSpriteScale(lua_State* L);
int L_SetSpriteRotation(lua_State* L);

/*
	Application window
*/
int L_GetWindowWidth(lua_State* L);
int L_GetWindowHeight(lua_State* L);

int L_ChangeScene(lua_State* L);

namespace GUI
{
	int L_AddText(lua_State* L);
	int L_AddButton(lua_State* L);
	int L_RemoveGUI(lua_State* L);
	int L_IsButtonPressed(lua_State* L);
	int L_UpdateText(lua_State* L);
};

// Graphical Interface wrapper
int L_UpdateGraphicalInterface(lua_State* L);
int	L_AddHealthbarUI(lua_State* L);
int L_UpdatePosUI(lua_State* L);
int L_RemoveUI(lua_State* L);



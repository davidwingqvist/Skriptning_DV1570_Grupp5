#pragma once

// Standard
#include <string>
#include <string_view>
#include <exception>
#include <chrono>
#include <iostream>
#include <sstream>
#include <fstream>
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include <memory>
#include <cassert> 
#include <unordered_map>
#include <vector>
#include <array>
#include <set>
#include <queue>
#include <condition_variable>
#include <bitset>
#include <algorithm>
#include <thread>

// Lua
#ifdef _DEBUG
#pragma comment(lib, "LuaLibd.lib")
#else
#pragma comment(lib, "Lualib.lib")
#endif
#include <lua.hpp>

// Irrlicht
#pragma comment(lib, "Irrlicht.lib")
#include <irrlicht.h>

// Singletons
#include "Graphics.h"
#include "LuaHandler.h"

// Paths
const std::string MODELPATH		= "../Assets/Models/";
const std::string TEXTUREPATH	= "../Assets/Textures/";
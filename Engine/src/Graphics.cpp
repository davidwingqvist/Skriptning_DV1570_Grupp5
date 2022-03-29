#include "PCH.h"
#include "Graphics.h"

Graphics::Graphics()
{
    //Default values
    m_window.name       = "Default";
    m_window.width      = 1280;
    m_window.height     = 720;
    m_window.vsync      = true;
    m_window.fullscreen = false;
    m_window.driverType = irr::video::EDT_SOFTWARE;

    //Load in options from file
    LoadOptionsLUA("Options.lua");
    
    m_device = irr::createDevice(m_window.driverType, irr::core::dimension2d<irr::u32>(m_window.width, m_window.height), 
                                16, m_window.fullscreen, false, m_window.vsync, &Input::GetInputHandler());
    
    if (!m_device)
    {
        std::cout << "Device couldn't be created.\n";
    }
    
    std::wstring winCap(m_window.name.begin(), m_window.name.end());
    m_device->setWindowCaption(winCap.c_str());
    m_driver = m_device->getVideoDriver();
    m_sceneManager = m_device->getSceneManager();
    m_guiEnvironment = m_device->getGUIEnvironment();
    dt = 0.0;
}

Graphics::~Graphics()
{
    m_device->drop();
}

auto& Graphics::Get()
{
    static Graphics instance;
    return instance;
}

void Graphics::LoadOptionsLUA(const std::string& luafile)
{
    LoadScript(luafile);

    //Name
    lua_pushstring(LUA, "name");
    lua_gettable(LUA, -2);
    if (lua_isstring(LUA, -1))
        m_window.name = static_cast<std::string>(lua_tostring(LUA, -1));
    lua_pop(LUA, 1);

    //Width
    lua_pushstring(LUA, "width");
    lua_gettable(LUA, -2);
    if (lua_isinteger(LUA, -1))
        m_window.width = static_cast<unsigned int>(lua_tonumber(LUA, -1));
    lua_pop(LUA, 1);

    //Height
    lua_pushstring(LUA, "height");
    lua_gettable(LUA, -2);
    if (lua_isinteger(LUA, -1))
        m_window.height = static_cast<unsigned int>(lua_tonumber(LUA, -1));
    lua_pop(LUA, 1);

    //Fullscreen
    lua_pushstring(LUA, "fullscreen");
    lua_gettable(LUA, -2);
    if (lua_isboolean(LUA, -1))
        m_window.fullscreen = lua_toboolean(LUA, -1);
    lua_pop(LUA, 1);

    //VSync
    lua_pushstring(LUA, "vsync");
    lua_gettable(LUA, -2);
    if (lua_isboolean(LUA, -1))
        m_window.vsync = lua_toboolean(LUA, -1);
    lua_pop(LUA, 1);

    //Drivertype
    lua_pushstring(LUA, "driverType");
    lua_gettable(LUA, -2);
    if (lua_isnumber(LUA, -1))
        m_window.driverType = static_cast<irr::video::E_DRIVER_TYPE>(lua_tonumber(LUA, -1));
    lua_pop(LUA, 1);
}

irr::IrrlichtDevice* Graphics::GetDevice()
{
    return Get().m_device;
}

irr::video::IVideoDriver* Graphics::GetDriver()
{
    return Get().m_driver;
}

irr::scene::ISceneManager* Graphics::GetSceneManager()
{
    return Get().m_sceneManager;
}

irr::gui::IGUIEnvironment* Graphics::GetGUIEnvironment()
{
    return Get().m_guiEnvironment;
}

double& Graphics::GetDeltaTime()
{
    return Get().dt;
}

unsigned int& Graphics::GetWindowWidth()
{
    return Get().m_window.width;
}

unsigned int& Graphics::GetWindowHeight()
{
    return Get().m_window.height;
}

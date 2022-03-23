#include "PCH.h"
#include "Graphics.h"

Graphics::Graphics()
{
    /*
        LoadScript("window.lua")

        Load a windowfile or luacode.
        Need:
            - Window Name
            - Window Width
            - Window Height
            - Fullscreen
            - VSYNC
            - Drivertype: DirectX, Opengl, EDT_SOFTWARE
    */
    m_device = irr::createDevice(irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(window_width, window_height), 16, false, false, true, &Input::GetInputHandler());
    if (!m_device)
    {
        std::cout << "Device couldn't be created.\n";
    }

    m_device->setWindowCaption(L"Budget Binding of Isaac");
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

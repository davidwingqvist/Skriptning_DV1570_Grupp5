#include "PCH.h"
#include "SceneManager.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "EditorScene.h"

SceneHandler::SceneHandler()
{
	m_currentSceneType = EScene::None;
}

SceneHandler::~SceneHandler()
{
}

Scene* SceneHandler::GetScene()
{
	return m_currentScene.get();
}

void SceneHandler::UpdateScene()
{
	m_currentScene->Update();
}

void SceneHandler::SetScene(const EScene& scene)
{
	// Current scene - just return
	if (scene == m_currentSceneType) return;

	// Unload/clean current scene
	if (m_currentScene)
		m_currentScene->Clean();

	// Set active scene
	m_currentSceneType = scene;

	switch (scene)
	{
	case EScene::Menu:
	{
		m_currentScene = std::make_unique<MenuScene>();
		break;
	}
	case EScene::Game:
	{
		m_currentScene = std::make_unique<GameScene>();
		break;
	}
	case EScene::Editor:
	{
		m_currentScene = std::make_unique<EditorScene>();
		break;
	}
	case EScene::None:
	{
		Graphics::GetDevice()->closeDevice();
		m_currentScene = nullptr;
		break;
	}
	default:
		break;
	};

	// Load in the scene
	if (m_currentScene)
		m_currentScene->Load();
}

const EScene& SceneHandler::GetSceneType() const
{
	return m_currentSceneType;
}

/*
*	Accesser
*/
auto& SceneAccess::Get()
{
	static SceneAccess instance;
	return instance;
}

void SceneAccess::SetSceneHandler(SceneHandler* handler)
{
	SceneAccess::Get().m_sceneHandler = handler;
}

SceneHandler* SceneAccess::GetSceneHandler()
{
	return SceneAccess::Get().m_sceneHandler;
}
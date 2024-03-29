#pragma once
#include "Sprite.h"
#include "Gridsystem.h"

class SceneHandler
{
private:
	std::string m_currentScene;

	//Unique ID
	unsigned int m_spriteUID;
	unsigned int m_textUID;
	unsigned int m_image2dUID;
	unsigned int m_buttonUID;

	std::unordered_map<unsigned int, std::unique_ptr<Sprite>>	m_sprites;
	std::unordered_map<unsigned int, irr::gui::IGUIStaticText*> m_texts;
	std::unordered_map<unsigned int, irr::gui::IGUIImage*>		m_image2ds;
	std::unordered_map<unsigned int, irr::gui::IGUIButton*>		m_buttons;

	irr::scene::ICameraSceneNode* m_camera;

	std::unique_ptr<Gridsystem> m_gridsystem;

private:
	//Singleton standard
	SceneHandler();
	~SceneHandler();
	SceneHandler(SceneHandler const&) = delete;
	SceneHandler(SceneHandler const&&) = delete;
	SceneHandler& operator=(SceneHandler const&) = delete;
	SceneHandler& operator=(SceneHandler const&&) = delete;
	static auto& Get();

	//Help functions to make the code cleaner
	void ResetScene();
	bool LoadScene(const std::string& file);

public:
	/*
		Adjust the scene
	*/
	static void LoadStartScene();
	static void ChangeScene(const std::string& file);
	static void UpdateScene();

	/*
		Sprites
	*/
	static unsigned int AddSprite(const std::string& file);
	static void RemoveSprite(const unsigned int& id);
	static void ChangeSprite(const unsigned int& id, const std::string& file);
	static void SetSpriteVisible(const unsigned int& id, const bool& isVisible);
	static void SetSpritePosition(const unsigned int& id, const irr::core::vector3df& pos);
	static void SetSpriteScale(const unsigned int& id, const irr::core::vector3df& scl);
	static void SetSpriteRotation(const unsigned int& id, const irr::core::vector3df& rot);
	static Sprite* GetSprite(const unsigned int& id);
	static void SetSpriteBlinking(const unsigned int& id, bool toggle);

	/*
		Collision - between sprites
	*/
	static void SetColliderSize(const unsigned int& id, const float& width, const float& height);
	static void SetHasCollision(const unsigned int& id, const bool& enabled);
	static bool SpriteCollisionAABB(const unsigned int& id1, const unsigned int& id2);
	static bool SpriteCollisionCircle(const unsigned int& id1, const unsigned int& id2);

	/*
		Camera
	*/
	static void AddCamera();
	static void SetCameraPosition(const irr::core::vector3df& pos);
	static void SetCameraTarget(const irr::core::vector3df& tar);
	static void SetCameraZoom(const float& zoom);
	static irr::scene::ICameraSceneNode* GetCamera();

	/*
		GUI
	*/
	static unsigned int AddText( const std::string& text);
	static void SetTextPosition( const unsigned int& id, const irr::core::vector2di& pos);
	static void SetTextSize(	 const unsigned int& id, const irr::core::vector2d<irr::u32>& size);
	static void SetTextAlignment(const unsigned int& id, const irr::gui::EGUI_ALIGNMENT& alignment);
	static void UpdateText(		 const unsigned int& id, const std::string& text);
	static void SetTextFont(	 const unsigned int& id, const std::string& fontname);
	
	// Button
	static unsigned int AddButton();
	static void RemoveButton(		const unsigned int& id);
	static bool IsButtonPressed(	const unsigned int& id);
	static void SetButtonText(		const unsigned int& id,	const std::string& text);
	static void SetButtonFont(		const unsigned int& id,	const std::string& fontname);
	static void SetButtonPosition(	const unsigned int& id,	const irr::core::vector2di& pos);
	static void SetButtonSize(		const unsigned int& id,	const irr::core::vector2d<irr::u32> size);
	static void SetButtonImage(		const unsigned int& id,	const std::string& filename);

	// Image 2d
	static const unsigned int AddImage2d(const std::string& filepath);
	static void RemoveImage2d(const unsigned int& index);
	static void ChangeImage2d(const unsigned int& index, const std::string& filepath);
	static void SetImage2dPosition(const unsigned int& index, irr::core::vector2di pos);
	static void SetImage2dScale(const unsigned int& index, const float& scale);

	/*
		Utility
	*/
	static irr::core::vector3df GetWorldCoordFromScreen();

	/*
		Editor
	*/
	static void AddGridSystem(const irr::core::vector2di& size);
	static Gridsystem* GetGridsystem();

};
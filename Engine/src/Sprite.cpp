#include "PCH.h"
#include "Sprite.h"

Sprite::Sprite()
{
	m_node = nullptr;
	m_size = irr::core::vector2df(TILE_SIZE, TILE_SIZE);
	m_collisionRadius = 0.f;
	m_hasCollision = true;
	this->LoadTexture();
}

Sprite::Sprite(const std::string& textureName)
{
	m_node = nullptr;
	m_size = irr::core::vector2df(TILE_SIZE, TILE_SIZE);
	m_collisionRadius = 0.f;
	m_hasCollision = true;
	this->LoadTexture(textureName);
}

void Sprite::SetPosition(const irr::core::vector3df& pos)
{
	m_node->setPosition(pos);
}

void Sprite::SetRotation(const irr::core::vector3df& rot)
{
	m_node->setRotation(rot);
}

void Sprite::SetScale(const irr::core::vector3df& scl)
{
	m_size.X *= scl.X;
	m_size.Y *= scl.Z;
	m_collisionRadius = m_size.getLength() / 2.f;
	m_node->setScale(scl);
}

const irr::core::vector3df& Sprite::GetPosition() const
{
	return m_node->getPosition();
}

const irr::core::vector2df Sprite::GetPosition2D() const
{
	return { m_node->getPosition().X, m_node->getPosition().Z };
}

const float& Sprite::GetCollisionRadius() const
{
	return m_collisionRadius;
}

const irr::core::rectf Sprite::GetBounds() const
{
	irr::core::vector2df pos = { m_node->getPosition().X, m_node->getPosition().Z };
	float halfXSize = m_size.X / 2.f;
	float halfYSize = m_size.Y / 2.f;

	return irr::core::rectf(irr::core::vector2df(pos.X - halfXSize, pos.Y - halfYSize),
							irr::core::vector2df(pos.X + halfXSize, pos.Y + halfYSize));
}

void Sprite::EnableBlinkEffect(bool toggle)
{
	// Create animator that blinks every 500 ms
	if (toggle)
	{
		irr::core::array<irr::video::ITexture*> allTextures(2);
		allTextures.push_back(m_texture);
		allTextures.push_back(nullptr);
		m_blinkEffect = Graphics::GetSceneManager()->createTextureAnimator(allTextures, 500, true);
		m_node->addAnimator(m_blinkEffect);
	}
	// Remove the animator
	else
	{
		if (m_blinkEffect)
		{
			m_node->setMaterialTexture(0, m_texture);
			m_node->removeAnimator(m_blinkEffect);
			m_blinkEffect->drop();
			m_blinkEffect = nullptr;
		}
	}
}

irr::core::matrix4 Sprite::GetAbsoluteTransform()
{
	return m_node->getAbsoluteTransformation();
}

void Sprite::LoadTexture(const std::string& filename)
{
	irr::core::vector3df pos;
	if (m_node)
		pos = m_node->getPosition();

	// Cleaning up before loading new
	this->Remove();

	if (!filename.empty())
		m_texture = Graphics::GetDriver()->getTexture((SPRITEPATH + filename).c_str());

	if (m_texture)
		m_size = static_cast<irr::core::dimension2df>(m_texture->getSize());

	m_mesh = Graphics::GetGeometryCreator()->createPlaneMesh(m_size);
	m_node = Graphics::GetSceneManager()->addMeshSceneNode(m_mesh, 0, -1, pos);
	
	if (!m_node)
		std::cout << "ERROR: Node not correct..." << std::endl;

	// Set material to the texture
	if (m_texture)
		m_node->setMaterialTexture(0, m_texture);
	// Load a default material
	else
		Graphics::GetSceneManager()->getMeshManipulator()->setVertexColors(m_mesh, irr::video::SColor(255, 255, 20, 147));

	//Make it possible to see using directX or openGL
	m_node->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
	//Possible to rotate the sprite
	m_node->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_BACK_FACE_CULLING, false);
	//Alpha value makes it transparent
	m_node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
	//Turn off filtering - no interpolation
	m_node->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_BILINEAR_FILTER, false);

	// Calculate collision radius
	m_collisionRadius = m_size.getLength() / 2.f;
	
	/*
		DEBUGGING - COLLISION
	*/
#if DEBUG_AABB_HITBOXES
	m_node->setDebugDataVisible(irr::scene::EDS_BBOX);
#endif
#if DEBUG_CIRCULAR_HITBOXES
	irr::scene::ISceneNode* sphereNode = Graphics::GetSceneManager()->addSphereSceneNode(m_collisionRadius, 12, m_node);
	sphereNode->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_WIREFRAME, true);
#endif

}

void Sprite::Remove()
{
	if (m_node)
	{
		m_node->remove();
		m_node = nullptr;
	}
}

void Sprite::SetVisible(const bool& isVisible)
{
	if (m_node)
	{
		m_node->setVisible(isVisible);
	}
}

void Sprite::SetCollision(const bool& hasCollision)
{
	m_hasCollision = hasCollision;
}

const bool& Sprite::HasCollision() const
{
	return m_hasCollision;
}

void Sprite::SetColliderSize(const float& width, const float& height)
{
#if DEBUG_AABB_HITBOXES
	irr::core::aabbox3df box;
	float halfWidth = width / 2.f;
	float halfHeight = height / 2.f;
	box.MinEdge = { -halfWidth, 0, -halfHeight };
	box.MaxEdge = {  halfWidth, 0,  halfHeight };
	m_mesh->setBoundingBox(box);
#endif

	m_size.X = width;
	m_size.Y = height;
}


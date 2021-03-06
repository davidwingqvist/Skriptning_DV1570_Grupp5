local gameObject = require('script/gameObject')

local DoorTile = gameObject:New()

function DoorTile:New()
	local g = gameObject:New()
	g.hp = 10000000000
	g.type = "door"
	g.key = gameObject:New()
	g.key.id = C_LoadSprite('key.png')
	--C_SetSpriteVisible(g.key.id, false)

	-- test position
	g.key:SetPosition(35,0.1,0)

	self.__index = DoorTile
	setmetatable(g, self)

	return g

end

--[[ Check if player collides with the key, if so, 
	 set itself and the key to invisible, or remove itself.
]]
function DoorTile:Update()

	if C_CheckSpriteCollision(player.id, self.key.id) then
		C_SetSpriteVisible(self.key.id, false)
		C_SetSpriteVisible(self.id, false)
		C_RemoveSprite(self.id)
		C_RemoveSprite(self.key.id)
	end

end

return DoorTile

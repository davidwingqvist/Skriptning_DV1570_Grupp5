-- require/include
local gameObject = require('script/gameObject')
local Vector = require('script/vector')

local Powerup = gameObject:New()

local BOMB_RADIUS = 5.0
local BOMB_DAMAGE = 50.0

local modes = 
{
	[1] = "Money",
	[2] = "Attack",
	[3] = "Speed",
	[4] = "Health",
	[5] = "Bomb"
}

local RESPAWN_TIME = 5.0

function Powerup:Initiate()
	
	return modes[math.random(#modes)]
	--return "Bomb"

end

function Powerup:New()
	local g = gameObject:New()
	g.mode = self:Initiate()
	g.hp = 100000000000
	g.type = 'powerup'
	g.defaultsprite = 'chest.png'

	g.respawntimer = 0.0
	g.shouldrespawn = false

	g.bomb = gameObject:New()
	g.bomb.id = C_LoadSprite('bomb.png')
	g.bomb:SetPosition(g.position.x, g.position.y, g.position.z)
	g.bomb.countdown = 3.0
	g.bomb.active = false
	C_SetSpriteVisible(g.bomb.id, false)

	self.__index = Powerup
	setmetatable(g, self)
	return g
end

function Powerup:Gain(player, goldText)

	if self.mode == "Money" then
		player.gold = player.gold + 5

		-- Update gold text
		goldText:Update(player)
	elseif self.mode == "Attack" then
		player.weapon.damage = player.weapon.damage + 5.0
	elseif self.mode == "Speed" then
		player.speed = player.speed + 2.5
	elseif self.mode == "Health" then
		player.hp = player.hp + 15.0
	elseif self.mode == "Bomb" then
		self.bomb.active = true
		self.bomb:SetPosition(self.position.x, self.position.y, self.position.z)
		C_SetSpriteVisible(self.bomb.id, true)

	end

	player.lastpickup = self.mode

	-- Hide from player.
	C_SetSpriteVisible(self.id, false)
	--self.OnEnd()

	self.respawntimer = RESPAWN_TIME
	self.shouldrespawn = true

end

function Powerup:Update(enemies, goldText, lastpickupText)
	--Check if player and the powerup is colliding
	if C_CheckSpriteCollision(player.id, self.id) and self.shouldrespawn == false then
		
		self:Gain(player, goldText)

		-- Update last pickup text
		if lastpickupText ~= nil then
			lastpickupText:Update()
		end
	end

	-- Update bomb timer
	if(self.bomb.active == true) then
		self.bomb.countdown = self.bomb.countdown - deltatime
	end

	-- Bomb explodes
	if(self.bomb.countdown < 0) then
		self.bomb.active = false
		self.bomb.countdown = 3


		for k, v in pairs(enemies) do
			
			local x = math.abs(v.position.x - self.bomb.position.x)
			local z = math.abs(v.position.z - self.bomb.position.z)

			if(x < BOMB_RADIUS and z < BOMB_RADIUS) then
				v.hp = v.hp - BOMB_DAMAGE
			end

		end

		C_SetSpriteVisible(self.bomb.id, false)
	end

end

return Powerup
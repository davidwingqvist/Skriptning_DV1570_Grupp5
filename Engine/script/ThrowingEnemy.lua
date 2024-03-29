local gameObject = require('script/gameObject')
local Vector = require('script/vector')

local ThrowMonkey = gameObject:New()

function ThrowMonkey:New()
	local g = gameObject:New()
	g.hp = 25
	g.worth = 15
	g.xp = 25
	g.damage = 5
	g.speed = math.random(3) + 1
	g.type = "monkey"
	g.name = "enemy"
	g.defaultsprite = 'necromancer.png'
	g.RandomizePos(g)
	self.__index = ThrowMonkey
	setmetatable(g, self)

	g.gid = C_AddHealthbar(0.0, 0.0, 75.0, 25.0, g.hp)

	g.weapon = Weapon.new("default")
	g.weapon.fireRate = 1

	return g
end

function ThrowMonkey:OnDeath()
	self:OnEnd()
end

function ThrowMonkey:Throw()
	local dir = player.position - self.position
	dir:Normalize()
	self.weapon:Fire(self.position, dir, self.id)
	self.weapon:Update()
end

function ThrowMonkey:Update()
	self:Throw()
	C_UpdatePosUI(self.gid, self.position.x, self.position.z, 75.0, 25.0)
	C_UpdateUI(self.gid, self.hp)
end


return ThrowMonkey
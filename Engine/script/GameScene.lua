Player			= require('script/Player')
player			= Player:New()
refMonster		= require('script/Monster')
refMonkey		= require('script/ThrowingEnemy')
boss			= require('script/BasicBossEnemy'):New()
refThrowBoss	= require('script/ThrowingBoss')
powerup			= require('script/Powerups')
goldText		= require('script/GoldText')
refCamera		= require('script/Camera')
lastpickupText	= require('script/lastpickuptext')
require('script/SceneHelp')

-- Collect separate types in different tables
monsters = {}

local deltatime = 0

function AddMonster(modelfilepath)
	local monster = refMonster:New()
	monster.id = C_LoadSprite(modelfilepath)
	table.insert(monsters, monster)
end

-- Returns all variables from the monsters table, in this case userdata.
--function getMonsters()
	--return table.unpack(monsters)
--end

function Start()
	math.randomseed(os.time())
	AddMonster('skeleton.png')
	AddMonster('skeleton.png')

	local newMonkey = refMonkey:New()
	local throwBoss = refThrowBoss:New()

	powerup = require('script/Powerups'):New()
	goldText:Initialize()
	lastpickupText:Initialize(player)
	
	table.insert(monsters, newMonkey)
	table.insert(monsters, boss)
	table.insert(monsters, throwBoss)

	--Camera setup
	camera = refCamera:New()
	camera:SetPosition(0,40,0)
	camera:SetTarget(0,0,0.1)
	camera:SetFOV(50)
end

-- Destroying everything
function Clean()
	print("### Removing player ###")
	player:OnEnd()

	print("### Removing monsters ###")
	for k, v in pairs(monsters) do
		v:OnEnd()
	end

	--print("### Removing powerups ###")
	--for k, v in pairs(powerups) do
	--	v:OnEnd()
	--end
end

function OnInput(x, y)
	assert(type(x) == "number", "OnInput: Value is not a number")
	assert(type(y) == "number", "OnInput: Value is not a number")
	
	
	if x == -1 then
		player:RotateLeft()
	elseif x == 1 then
		player:RotateRight()
	end

	local vec = vector:New()
	vec.x = x * deltatime * player.speed
	vec.z = y * deltatime * player.speed

	player:Move(vec)
	camera:Move(vec)
end

-- Game loop
function Update(dt)
	deltatime = dt

	-- Loop through all enemies
	for k, v in pairs(monsters) do
		
		if v.hp > 0 then
			v:Update(player, dt)
		elseif v.hp <= 0 then
			RemoveEnemy(k, v)
		end
	end

	-- Update powerup
	if powerup ~= nil then
		powerup:Update(player, dt, monsters, goldText, lastpickupText)
	end

	-- Go back to menu when player dies
	if(player:IsAlive() == false) then
		C_ChangeScene(Scene.MENU)
	end

	-- Update player
	player:Update()
end


function RemoveEnemy(num, monster)

	--monster:OnDeath(player.gold)
	table.remove(monsters, num)
	C_RemoveSprite(monster.id)
	C_RemoveUI(monster.gid)

end

-- Communication between lua and c++

-- Find the indexed object and return its position
function GetObjectPosition(ind)

	if player.id == ind then
		return player.position.x, player.position.z
	end

	if boss.id == ind then
		return boss.position.x, boss.position.z
	end

	for k, v in pairs(monsters) do
		if v.id == ind then
			return v.position.x, v.position.z
		end
	end

	return 'err', 'err'
end

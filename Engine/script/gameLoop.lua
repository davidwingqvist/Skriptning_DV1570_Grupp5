player = require('script/Player')
refMonster = require('script/Monster')
monsters = {}

function addMonster(ind)
	local monster = refMonster:New()
	monster.id = ind
	--print(ind)
	table.insert(monsters, monster)
end

function getMonsterPosition(index)
	for k, v in pairs(monsters) do
		if v.id == index then
			return v.position.x, v.position.y
		end
	end

	return 0, 0
end

-- Returns all variables from the monsters table, in this case userdata.
--function getMonsters()
	--return table.unpack(monsters)
--end

function Start()
	math.randomseed(os.time())
end

-- Update function for lua. return 0 if nothing happend, 1 if player died.
function Update()

	--print(player.position)

	for k, v in pairs(monsters) do
		print(v.position)
	end

	if player:getHealth() <= 0 then
		return 1
	end
	return 0
end
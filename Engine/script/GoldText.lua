
local goldText = {}

function goldText:Initialize()

	goldText.text = AddText("Gold: 0", "roboto_48.xml", 120, 100, 350, 100)
	--Add functionality to set alignment to left, right and center

end

function goldText:Update(player)

	-- Update the text here
	UpdateText(goldText.text, 'Gold: ' .. player.gold)

end

return goldText
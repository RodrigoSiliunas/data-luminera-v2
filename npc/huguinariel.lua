local internalNpcName = "Huguinariel"
local npcType = Game.createNpcType(internalNpcName)
local npcConfig = {}

npcConfig.name = internalNpcName
npcConfig.description = internalNpcName

npcConfig.health = 100
npcConfig.maxHealth = npcConfig.health
npcConfig.walkInterval = 2000
npcConfig.walkRadius = 2

npcConfig.outfit = {
	lookType = 54,
	lookHead = 0,
	lookBody = 119,
	lookLegs = 119,
	lookFeet = 126,
}

npcConfig.flags = {
	floorchange = false,
}

local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)

npcType.onThink = function(npc, interval)
	npcHandler:onThink(npc, interval)
end

npcType.onAppear = function(npc, creature)
	npcHandler:onAppear(npc, creature)
end

npcType.onDisappear = function(npc, creature)
	npcHandler:onDisappear(npc, creature)
end

npcType.onMove = function(npc, creature, fromPosition, toPosition)
	npcHandler:onMove(npc, creature, fromPosition, toPosition)
end

npcType.onSay = function(npc, creature, type, message)
	npcHandler:onSay(npc, creature, type, message)
end

npcType.onCloseChannel = function(npc, creature)
	npcHandler:onCloseChannel(npc, creature)
end

npcHandler:addModule(FocusModule:new(), npcConfig.name, true, true, true)

npcConfig.shop = {
    { itemName = "angelic axe", clientId = 7436, sell = 5000 },
    { itemName = "ancient shield", clientId = 3432, buy = 5000, sell = 900 },
    { itemName = "black shield", clientId = 3429, sell = 800 },
    { itemName = "blue robe", clientId = 3567, sell = 10000 },
    { itemName = "bonebreaker", clientId = 7428, sell = 10000 },
    { itemName = "bonelord shield", clientId = 3418, buy = 7000, sell = 1200 },
    { itemName = "boots of haste", clientId = 3079, sell = 30000 },
    { itemName = "broadsword", clientId = 3301, sell = 500 },
    { itemName = "butcher's axe", clientId = 7412, sell = 18000 },
    { itemName = "crown armor", clientId = 3381, sell = 12000 },
    { itemName = "crown helmet", clientId = 3385, sell = 2500 },
    { itemName = "crown legs", clientId = 3382, sell = 12000 },
    { itemName = "crown shield", clientId = 3419, sell = 8000 },
    { itemName = "crusader helmet", clientId = 3391, sell = 6000 },
    { itemName = "dark armor", clientId = 3383, buy = 1500, sell = 400 },
    { itemName = "dark helmet", clientId = 3384, buy = 1000, sell = 250 },
    { itemName = "dragon hammer", clientId = 3322, sell = 2000 },
    { itemName = "dragon lance", clientId = 3302, sell = 9000 },
    { itemName = "dragon shield", clientId = 3416, sell = 4000 },
    { itemName = "dreaded cleaver", clientId = 7419, sell = 15000 },
    { itemName = "fire axe", clientId = 3320, sell = 8000 },
    { itemName = "fire sword", clientId = 3280, sell = 4000 },
    { itemName = "giant sword", clientId = 3281, sell = 17000 },
    { itemName = "glorious axe", clientId = 7454, sell = 3000 },
    { itemName = "guardian shield", clientId = 3415, sell = 2000 },
    { itemName = "haunted blade", clientId = 7407, sell = 8000 },
    { itemName = "ice rapier", clientId = 3284, buy = 5000, sell = 1000 },
    { itemName = "knight armor", clientId = 3370, sell = 5000 },
    { itemName = "knight axe", clientId = 3318, sell = 2000 },
    { itemName = "knight legs", clientId = 3371, sell = 5000 },
    { itemName = "mystic turban", clientId = 3574, sell = 150 },
    { itemName = "noble armor", clientId = 3380, buy = 8000, sell = 900 },
    { itemName = "obsidian lance", clientId = 3313, buy = 3000, sell = 500 },
    { itemName = "onyx flail", clientId = 7421, sell = 22000 },
    { itemName = "ornamented axe", clientId = 7411, sell = 20000 },
    { itemName = "phoenix shield", clientId = 3439, sell = 16000 },
    { itemName = "poison dagger", clientId = 3299, sell = 50 },
    { itemName = "queen's sceptre", clientId = 7410, sell = 20000 },
    { itemName = "royal helmet", clientId = 3392, sell = 30000 },
    { itemName = "scimitar", clientId = 3307, sell = 150 },
    { itemName = "serpent sword", clientId = 3297, buy = 6000, sell = 900 },
    { itemName = "shadow sceptre", clientId = 7451, sell = 10000 },
    { itemName = "skull staff", clientId = 3324, sell = 6000 },
    { itemName = "spike sword", clientId = 3271, buy = 8000, sell = 1000 },
    { itemName = "strange helmet", clientId = 3373, sell = 500 },
    { itemName = "thaian sword", clientId = 7391, sell = 16000 },
    { itemName = "titan axe", clientId = 7413, sell = 4000 },
    { itemName = "tower shield", clientId = 3428, sell = 8000 },
    { itemName = "vampire shield", clientId = 3434, sell = 15000 },
    { itemName = "war hammer", clientId = 3279, buy = 10000, sell = 1200 },
    { itemName = "warrior helmet", clientId = 3369, sell = 5000 },
}

-- On buy npc shop message
npcType.onBuyItem = function(npc, player, itemId, subType, amount, ignore, inBackpacks, totalCost)
	npc:sellItem(player, itemId, amount, subType, 0, ignore, inBackpacks)
end
-- On sell npc shop message
npcType.onSellItem = function(npc, player, itemId, subtype, amount, ignore, name, totalCost)
	player:sendTextMessage(MESSAGE_INFO_DESCR, string.format("Sold %ix %s for %i gold.", amount, name, totalCost))
end
-- On check npc shop message (look item)
npcType.onCheckItem = function(npc, player, clientId, subType) end

npcType:register(npcConfig)

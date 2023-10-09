local internalNpcName = "Tundriel"
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
    { itemName = "ankh", clientId = 3077, sell = 100 },
    { itemName = "axe ring", clientId = 3092, buy = 500, sell = 100 },
    { itemName = "bronze amulet", clientId = 3056, buy = 100, sell = 50, count = 200 },
    { itemName = "club ring", clientId = 3093, buy = 500, sell = 100 },
    { itemName = "dragon necklace", clientId = 3085, buy = 1000, sell = 100, count = 200 },
    { itemName = "dwarven ring", clientId = 3097, buy = 2000, sell = 100 },
    { itemName = "elven amulet", clientId = 3082, buy = 500, sell = 100, count = 50 },
    { itemName = "energy ring", clientId = 3051, buy = 2000, sell = 100 },
    { itemName = "garlic necklace", clientId = 3083, buy = 100, sell = 50 },
    { itemName = "glacial rod", clientId = 16118, sell = 6500 },
    { itemName = "hailstorm rod", clientId = 3067, sell = 3000 },
    { itemName = "life crystal", clientId = 4840, sell = 50 },
    { itemName = "life ring", clientId = 3052, buy = 900, sell = 50 },
    { itemName = "magic light wand", clientId = 3046, buy = 120, sell = 35 },
    { itemName = "might ring", clientId = 3048, buy = 5000, sell = 250, count = 20 },
    { itemName = "mind stone", clientId = 3062, sell = 100 },
    { itemName = "moonlight rod", clientId = 3070, sell = 200 },
    { itemName = "muck rod", clientId = 16117, sell = 6000 },
    { itemName = "mysterious fetish", clientId = 3078, sell = 50 },
    { itemName = "necrotic rod", clientId = 3069, sell = 1000 },
    { itemName = "northwind rod", clientId = 8083, sell = 1500 },
    { itemName = "orb", clientId = 3060, sell = 750 },
    { itemName = "power ring", clientId = 3050, buy = 100, sell = 50 },
    { itemName = "protection amulet", clientId = 3084, buy = 700, sell = 100, count = 250 },
    { itemName = "ring of healing", clientId = 3098, buy = 2000, sell = 100 },
    { itemName = "silver amulet", clientId = 3054, buy = 100, sell = 50, count = 200 },
    { itemName = "snakebite rod", clientId = 3066, sell = 100 },
    { itemName = "springsprout rod", clientId = 8084, sell = 3600 },
    { itemName = "stealth ring", clientId = 3049, buy = 5000, sell = 200 },
    { itemName = "stone skin amulet", clientId = 3081, buy = 5000, sell = 500, count = 5 },
    { itemName = "strange talisman", clientId = 3045, buy = 100, sell = 30, count = 200 },
    { itemName = "sword ring", clientId = 3091, buy = 500, sell = 100 },
    { itemName = "terra rod", clientId = 3065, sell = 2000 },
    { itemName = "time ring", clientId = 3053, buy = 2000, sell = 100 },
    { itemName = "underworld rod", clientId = 8082, sell = 4400 },
    { itemName = "wand of cosmic energy", clientId = 3073, sell = 2000 },
    { itemName = "wand of decay", clientId = 3072, sell = 1000 },
    { itemName = "wand of defiance", clientId = 16096, sell = 6500 },
    { itemName = "wand of draconia", clientId = 8093, sell = 1500 },
    { itemName = "wand of dragonbreath", clientId = 3075, sell = 200 },
    { itemName = "wand of everblazing", clientId = 16115, sell = 6000 },
    { itemName = "wand of inferno", clientId = 3071, sell = 3000 },
    { itemName = "wand of starstorm", clientId = 8092, sell = 3600 },
    { itemName = "wand of voodoo", clientId = 8094, sell = 4400 },
    { itemName = "wand of vortex", clientId = 3074, sell = 100 },
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

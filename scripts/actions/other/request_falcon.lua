local falcon = Action()

function falcon.onUse(player, item, fromPosition, target, toPosition, isHotkey)
    player:getPosition():sendMagicEffect(CONST_ME_SOUND_YELLOW)
    return true
end

falcon:id(8148)
falcon:register()

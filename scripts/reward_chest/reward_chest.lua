local chest = Action()

function chest.onUse(player, item, fromPosition, target, toPosition, isHotkey) end

-- Create reward chest in the Montag temple
chest:position({ x = 1348, y = 1122, z = 7 }, 19250)

chest:register()

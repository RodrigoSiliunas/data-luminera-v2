local http = require('socket.http')
local falcon = Action()

function falcon.onUse(player, item, fromPosition, target, toPosition, isHotkey)
    local result, status = http.request('http://www.google.com')

    player:getPosition():sendMagicEffect(CONST_ME_SOUND_YELLOW)
    player:sendTextMessage("You have successfully on send a request to google.com, status:" .. status)
    return true
end

falcon:id(8148)
falcon:register()

local falcon = Action()

function falcon.onUse(player, item, fromPosition, target, toPosition, isHotkey)
    local customHeaders = {
        ["Content-Type"] = "application/json"
    }
    local apiUrl = "https://pokeapi.co/api/v2/pokemon/pikachu/"

    -- Envia a solicitação GET usando o método sendGetRequest
    local response_body = {}
    local response_code = Webhook.sendGetRequest(apiUrl, customHeaders, response_body)
    print(response_code)

    player:getPosition():sendMagicEffect(CONST_ME_SOUND_YELLOW)
    return true
end

falcon:id(8148)
falcon:register()

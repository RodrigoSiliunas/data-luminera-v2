local falcon = Action()

function falcon.onUse(player, item, fromPosition, target, toPosition, isHotkey)
    local customHeaders = {
        ["Content-Type"] = "application/json"
    }
    local apiUrl = "https://jsonplaceholder.typicode.com/posts/1"

    -- Envia a solicitação GET usando o método sendGetRequest
    local response_code, response_body = Webhook.sendGetRequest(apiUrl, customHeaders, response_body)
    
    -- Imprime a resposta
    print("Requisição Efetuada. Status: " .. response_code .. "\nBody: " .. response_body)

    player:getPosition():sendMagicEffect(CONST_ME_SOUND_YELLOW)
    return true
end

falcon:id(8148)
falcon:register()

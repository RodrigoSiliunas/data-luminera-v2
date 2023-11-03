local falcon = Action()

function falcon.onUse(player, item, fromPosition, target, toPosition, isHotkey)
    local customHeaders = {
        ["Content-Type"] = "application/json"
    }
    local apiUrl = "https://pokeapi.co/api/v2/pokemon/pikachu/"

    -- Envia a solicitação GET usando o método sendGetRequest
    local response_body = {}
    local response_code, response = Webhook.sendGetRequest(apiUrl, customHeaders, response_body)
    
    -- Converte a tabela response_body em uma string
    local response_string = table.concat(response_body)
    
    -- print("Requisição Efetuada. Status: " .. response_code .. "\nBody: " .. response_string)

    print(response)

    player:getPosition():sendMagicEffect(CONST_ME_SOUND_YELLOW)
    return true
end

falcon:id(8148)
falcon:register()

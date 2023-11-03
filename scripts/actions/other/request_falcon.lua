local falcon = Action()

function falcon.onUse(player, item, fromPosition, target, toPosition, isHotkey)
    local customHeaders = {
        ["Content-Type"] = "application/json"
    }
    local apiUrl = "https://jsonplaceholder.typicode.com/posts/1"

    -- Envia a solicitação GET usando o método sendGetRequest
    local response_body = {}
    local response_code = Webhook.sendGetRequest(apiUrl, customHeaders, response_body)
    
    -- Converte a tabela response_body em uma string
    local response_string = table.concat(response_body)
    
    -- Imprime a resposta
    print("Requisição Efetuada. Status: " .. response_code .. "\nBody: " .. response_string)

    player:getPosition():sendMagicEffect(CONST_ME_SOUND_YELLOW)
    return true
end

falcon:id(8148)
falcon:register()

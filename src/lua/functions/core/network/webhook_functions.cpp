/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#include "pch.hpp"

#include "lua/functions/core/network/webhook_functions.hpp"
#include "server/network/webhook/webhook.hpp"

int WebhookFunctions::luaWebhookSendMessage(lua_State* L) {
    // Implementação da função sendMessage
    std::string title = getString(L, 1);
    std::string message = getString(L, 2);
    std::map<std::string, std::string> customHeaders;
    std::string payload;

    // Mapeamento das strings para os valores de enumeração HttpMethod
    HttpMethod method = HttpMethod::GET; // Valor padrão
    if (lua_gettop(L) >= 3) {
        const std::string methodStr = getString(L, 3);
        if (methodStr == "POST") {
            method = HttpMethod::POST;
        }
    }

    if (lua_gettop(L) >= 4) {
        // Se um quarto argumento estiver presente, é o payload
        payload = getString(L, 4);
    }

    g_webhook().sendMessage(title, message, customHeaders, payload, method);
    lua_pushnil(L);

    return 1;
}

int WebhookFunctions::luaWebhookSendGetRequest(lua_State* L) {
    // Implementação da função sendGetRequest
    std::string url = getString(L, 1);
    std::map<std::string, std::string> customHeaders;

    std::string response_body;  // Adicione uma variável para armazenar a resposta

    if (lua_gettop(L) >= 2) {
        // Se um segundo argumento estiver presente, é um mapa de cabeçalhos personalizados
        luaL_checktype(L, 2, LUA_TTABLE);
        lua_pushnil(L);  // Primeira chave da tabela
        while (lua_next(L, 2) != 0) {
            // Usa key (índice 3) e value (índice 4) da tabela
            if (lua_type(L, 3) == LUA_TSTRING && lua_type(L, 4) == LUA_TSTRING) {
                // Converte as chaves e valores para strings
                const char* key = lua_tostring(L, 3);
                const char* value = lua_tostring(L, 4);
                customHeaders[key] = value;
            }
            // Remove o valor, mantendo a chave para a próxima iteração
            lua_pop(L, 1);
        }
    }

    // Chame a função sendGetRequest da classe Webhook do código C++
    // usando a URL, cabeçalhos personalizados e response_body fornecidos
    int response_code = g_webhook().sendGetRequest(url, customHeaders, &response_body);

    // Empurre o código de resposta e o response_body para a pilha Lua
    lua_pushinteger(L, response_code);
    lua_pushstring(L, response_body.c_str());

    return 2; // Retorna 2 valores para Lua (código de resposta e response_body)
}

int WebhookFunctions::luaWebhookSendPostRequest(lua_State* L) {
    // Implementação da função sendPostRequest
    std::string url = getString(L, 1);
    std::map<std::string, std::string> customHeaders;
    std::string payload = getString(L, 2);

    std::string response_body;  // Adicione uma variável para armazenar a resposta

    if (lua_gettop(L) >= 3) {
        // Se um terceiro argumento estiver presente, é um mapa de cabeçalhos personalizados
        luaL_checktype(L, 3, LUA_TTABLE);
        lua_pushnil(L);  // Primeira chave da tabela
        while (lua_next(L, 3) != 0) {
            // Usa key (índice 4) e value (índice 5) da tabela
            if (lua_type(L, 4) == LUA_TSTRING && lua_type(L, 5) == LUA_TSTRING) {
                // Converte as chaves e valores para strings
                const char* key = lua_tostring(L, 4);
                const char* value = lua_tostring(L, 5);
                customHeaders[key] = value;
            }
            // Remove o valor, mantendo a chave para a próxima iteração
            lua_pop(L, 1);
        }
    }

    // Chame a função sendPostRequest da classe Webhook do código C++
    // usando a URL, cabeçalhos personalizados e payload fornecidos
    int response_code = g_webhook().sendPostRequest(url, customHeaders, payload, &response_body);

    // Empurre o código de resposta e a resposta_body para a pilha Lua
    lua_pushinteger(L, response_code);
    lua_pushstring(L, response_body.c_str());

    return 2; // Retorna 2 valores para Lua (código de resposta e response_body)
}
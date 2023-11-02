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
    // Webhook.sendMessage(title, message, customHeaders, payload)
    std::string title = getString(L, 1);
    std::string message = getString(L, 2);
    std::map<std::string, std::string> customHeaders;
    std::string payload;

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

    if (lua_gettop(L) >= 4) {
        // Se um quarto argumento estiver presente, é o payload
        payload = getString(L, 4);
    }

    g_webhook().sendMessage(title, message, customHeaders, payload);
    lua_pushnil(L);

    return 1;
}

int WebhookFunctions::luaWebhookSendGetRequest(lua_State* L) {
    // Implementação da função sendGetRequest
    std::string url = getString(L, 1);
    std::map<std::string, std::string> customHeaders;

    if (lua_gettop(L) >= 2) {
        // Se um segundo argumento estiver presente, é um mapa de cabeçalhos personalizados
        luaL_checktype(L, 2, LUA_TTABLE);
        lua_pushnil(L);  // Primeira chave da tabela
        while (lua_next(L, 2) != 0) {
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

    // Chame a função sendGetRequest da classe Webhook do código C++
    // usando a URL e cabeçalhos personalizados fornecidos
    int response_code = g_webhook().sendGetRequest(url, customHeaders);
    lua_pushinteger(L, response_code);

    return 1;
}

int WebhookFunctions::luaWebhookSendPostRequest(lua_State* L) {
    // Implementação da função sendPostRequest
    std::string url = getString(L, 1);
    std::map<std::string, std::string> customHeaders;
    std::string payload = getString(L, 2);

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
    int response_code = g_webhook().sendPostRequest(url, customHeaders, payload);
    lua_pushinteger(L, response_code);

    return 1;
}
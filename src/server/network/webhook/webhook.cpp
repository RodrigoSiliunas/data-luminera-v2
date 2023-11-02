/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#include "pch.hpp"

#include "server/network/webhook/webhook.hpp"
#include "config/configmanager.hpp"
#include "game/scheduling/dispatcher.hpp"
#include "utils/tools.hpp"

Webhook::Webhook(ThreadPool &threadPool) :
	threadPool(threadPool) {
	if (curl_global_init(CURL_GLOBAL_ALL) != 0) {
		g_logger().error("Failed to init curl, no webhook messages may be sent");
		return;
	}

	headers = curl_slist_append(headers, "accept: application/json");
	headers = curl_slist_append(headers, "User-Agent: canary (https://github.com/opentibiabr/canary)");

	if (headers == nullptr) {
		g_logger().error("Failed to init curl, appending request headers failed");
		return;
	}

	run();
}

Webhook &Webhook::getInstance() {
	return inject<Webhook>();
}

void Webhook::run() {
	threadPool.addLoad([this] { sendWebhook(); });
	g_dispatcher().scheduleEvent(
		g_configManager().getNumber(DISCORD_WEBHOOK_DELAY_MS), [this] { run(); }, "Webhook::run"
	);
}

void Webhook::sendMessage(const std::string url, HttpMethod method, std::map<std::string, std::string> customHeaders, const std::string payload) {
	std::scoped_lock lock { taskLock };
	webhooks.push_back(std::make_shared<WebhookTask>(url, method, customHeaders, payload));
}

int Webhook::sendRequest(const char* url, HttpMethod method, std::map<std::string, std::string> customHeaders, const char* payload, std::string* response_body) const {
	CURL* curl = curl_easy_init();
	if (!curl) {
		g_logger().error("Failed to send webhook message; curl_easy_init failed");
		return -1;
	}

	// Configurar os headers personalizados
	struct curl_slist* curlHeaders = nullptr;
	for (const auto &header : customHeaders) {
		std::string headerString = header.first + ": " + header.second;
		curlHeaders = curl_slist_append(curlHeaders, headerString.c_str());
	}

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);

	// Configurar o método de requisição (GET ou POST)
	if (method == HttpMethod::GET) {
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
	} else if (method == HttpMethod::POST) {
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);
	}

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Webhook::writeCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, reinterpret_cast<void*>(response_body));
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "canary (https://github.com/opentibiabr/canary)");

	CURLcode res = curl_easy_perform(curl);

	if (res != CURLE_OK) {
		g_logger().error("Failed to send webhook message with the error: {}", curl_easy_strerror(res));
		curl_easy_cleanup(curl);
		curl_slist_free_all(curlHeaders);
		return -1;
	}

	int response_code;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
	curl_easy_cleanup(curl);
	curl_slist_free_all(curlHeaders);

	return response_code;
}

void Webhook::sendWebhook() {
	std::scoped_lock lock { taskLock };
	if (webhooks.empty()) {
		return;
	}

	auto task = webhooks.front();

	std::string response_body;
	auto response_code = sendRequest(task->url.c_str(), task->method, task->customHeaders, task->payload.c_str(), &response_body);

	if (response_code == -1) {
		return;
	}

	if (response_code == 429 || response_code == 504) {
		g_logger().warn("Webhook encountered error code {}, re-queueing task.", response_code);
		return;
	}

	webhooks.pop_front();

	if (response_code >= 300) {
		g_logger().error(
			"Failed to send webhook message, error code: {} response body: {} request body: {}",
			response_code,
			response_body,
			task->payload
		);

		return;
	}

	g_logger().debug("Webhook successfully sent to {}", task->url);
}

int Webhook::sendGetRequest(const char* url, std::map<std::string, std::string> customHeaders, std::string* response_body) const {
	return sendRequest(url, HttpMethod::GET, customHeaders, nullptr, response_body);
}

int Webhook::sendPostRequest(const char* url, std::map<std::string, std::string> customHeaders, const char* payload, std::string* response_body) const {
	return sendRequest(url, HttpMethod::POST, customHeaders, payload, response_body);
}

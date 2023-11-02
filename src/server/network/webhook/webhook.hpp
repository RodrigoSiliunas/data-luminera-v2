/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#pragma once

#include "lib/thread/thread_pool.hpp"

enum class HttpMethod {
	GET,
	POST
};

struct WebhookTask {
	std::string url;
	HttpMethod method;
	std::map<std::string, std::string> customHeaders;
	std::string payload;

	WebhookTask(std::string url, HttpMethod method, std::map<std::string, std::string> customHeaders, std::string payload) :
		url(std::move(url)), method(method), customHeaders(std::move(customHeaders)), payload(std::move(payload)) { }
};

class Webhook {
public:
	Webhook(ThreadPool &threadPool);
	static Webhook &getInstance();

	void sendMessage(const std::string url, HttpMethod method, std::map<std::string, std::string> customHeaders, const std::string payload);
	int sendGetRequest(const char* url, std::map<std::string, std::string> customHeaders, std::string* response_body) const;
	int sendPostRequest(const char* url, std::map<std::string, std::string> customHeaders, const char* payload, std::string* response_body) const;

private:
	void run();
	int sendRequest(const char* url, HttpMethod method, std::map<std::string, std::string> customHeaders, const char* payload, std::string* response_body) const;
	void sendWebhook();
	static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp);

	ThreadPool &threadPool;
	std::mutex taskLock;
	std::deque<std::shared_ptr<WebhookTask>> webhooks;
	curl_slist* headers = nullptr;
};

constexpr auto g_webhook = Webhook::getInstance;

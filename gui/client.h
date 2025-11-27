#pragma once

#include <future>

extern std::future<int> clientFuture;
int initClient();
void startClient();
#pragma once
#include <future>

// future client
extern std::future<int> serverFuture;
int initServer();
void startServer();


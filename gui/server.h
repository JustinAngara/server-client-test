#pragma once
#include <future>

// future client
int initServer();
std::future<int> serverFuture;
void startServer();


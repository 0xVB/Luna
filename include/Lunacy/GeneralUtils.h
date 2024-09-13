#pragma once
#include <Windows.h>
#include <string.h>
#include <sstream>

void Patch(DWORD Address, std::string Bytes);
void OverwriteByte(DWORD Address, unsigned char Level);
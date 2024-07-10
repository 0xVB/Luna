#pragma once
#include "ForwardDefinitions.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>

class PopString : public std::string
{
private:
	virtual void _pad() {};
public:
	PopString() : std::string() {};
	PopString(std::string str) : std::string(str) {};
	PopString(const char* cstr) : std::string(cstr) {};
};

class PopWString : public std::wstring
{
private:
	virtual void _pad() {};
public:
	PopWString() : std::wstring() {};
	PopWString(std::wstring wstr) : std::wstring(wstr) {};
	PopWString(const wchar_t* wcstr) : std::wstring(wcstr) {};
};

template <typename T>
class PopList : public std::list<T>
{
private:
	virtual void _pad() {};
public:
	PopList() : std::list<T>() {};
	PopList(std::list<T> self) : std::list<T>(self) {};
};

template <typename T>
class PopVector : public std::vector<T>
{
private:
	virtual void _pad() {};
public:
	PopVector() : std::vector<T>() {};
	PopVector(std::vector<T> self) : std::vector<T>(self) {};
};

template <typename T>
class PopSet : public std::set<T>
{
private:
	virtual void _pad() {};
public:
	PopSet() : std::set<T>() {};
	PopSet(std::set<T> self) : std::set<T>(self) {};
};

template <typename K, typename V>
class PopMap : public std::map<K, V>
{
private:
	virtual void _pad() {};
public:
	PopMap() : std::map<K, V>() {};
	PopMap(std::map<K, V> self) : std::map<K, V>(self) {};
};

template <typename K, typename V>
class PopPair : public std::pair<K, V>
{
private:
	virtual void _pad() {};
public:
	PopPair() : std::pair<K, V>() {};
	PopPair(std::pair<K, V> self) : std::pair<K, V>(self) {};
};
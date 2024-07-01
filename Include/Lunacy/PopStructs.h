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
};

class PopWString : public std::wstring
{
private:
	virtual void _pad() {};
};

template <typename T>
class PopList : public std::list<T>
{
private:
	virtual void _pad() {};
};

template <typename T>
class PopVector : public std::vector<T>
{
private:
	virtual void _pad() {};
};

template <typename T>
class PopSet : public std::set<T>
{
private:
	virtual void _pad() {};
};

template <typename K, typename V>
class PopMap : public std::map<K, V>
{
private:
	virtual void _pad() {};
};

template <typename K, typename V>
class PopPair : public std::pair<K, V>
{
private:
	virtual void _pad() {};
};
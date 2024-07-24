#pragma once
#include "ForwardDefinitions.h"
#include <string>
#include <map>

class GameObject
{
	LawnApp* mApp;
	Lawn* mLawn;
	int mX;
	int mY;
	int mWidth;
	int mHeight;
	bool mVisible;
	int mRow;
	int mRenderOrder;
};

/*
template <typename T>
class AttachmentHelper
{
private:
	union ValueType
	{
		void* p;
		double d;
	};

	static std::map<unsigned long long, ValueType> Attachments = std::map<unsigned long long, ValueType>();

	unsigned long long _GetKey()
	{
		int Address = (int)this;
		return (this << 32) | *((int*)(Address + sizeof(T)));
	}
public:

	void SetValue(std::string ValueName, double Value)
	{
		auto Key = _GetKey();
		Attachments[Key] = Value;
	}

	double GetValue(std::string ValueName, bool* Exists)
	{
		if (Exists)
			*Exists = true;

		auto Key = _GetKey();
		if (Attachments.find(Key) != Attachments.end())
			return Attachments[Key];

		if (Exists)
			*Exists = false;
		return 0;
	}

	void RemoveValue(std::string ValueName)
	{
		auto Key = _GetKey();
		if (Attachments.find(Key) != Attachments.end())
	}
};
*/
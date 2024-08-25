#pragma once
#include <string>
#include <map>

#include "Lunacy/CGeometry.h"

class AssociationManager
{
public:
	union Association
	{
		bool Boolean;
		void* Pointer;
		double Double;
		Sexy::FVector2 F2;
		Sexy::FVector3 F3;
		Sexy::FRect FR;

		Association() : FR() {};
		Association(bool);
		Association(void*);
		Association(double);
		Association(Sexy::FRect);
		Association(Sexy::FVector2);
		Association(Sexy::FVector3);
		Association(const Association& Other);
		Association& operator=(const Association& Other);
	};

private:
	std::map<std::string, Association> Associations;

public:
	Association Get(std::string);// Returns the association if found, if not it uses the default constructor of IRect and returns that.
	void Set(std::string, Association);// Sets the association.
	void Delete(std::string);// Deletes the association if it exists.
};

AssociationManager* GetAssociation(char* Cave);
void DeleteAssociation(char* Cave);
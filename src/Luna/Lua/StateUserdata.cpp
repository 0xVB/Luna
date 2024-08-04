#include "Luna/Lua/StateUserdata.hpp"

Luna::StateUserdata::StateUserdata(ScriptIdentity identity, ModParserPtr mod) : _identity(identity), _mod(mod)
{

}

Luna::StateUserdata::~StateUserdata()
{
}

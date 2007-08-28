#ifndef SCRIPT_H
#define SCRIPT_H

#include "../singleton.h"

extern "C"
{
	#include "lua/lua.h"
	#include "lua/lauxlib.h"
	#include "lua/lualib.h"
	#include "lua/tolua.h"
}

#include "bindings.h"

namespace Small
{
class Script : public Singleton<Script>
{
	friend class Singleton<Script>;

private:
	lua_State *l;

public:
	Script();
	~Script();

	void RaiseEvent(char *Event);
}; // class Script

} // namespace Small

#endif SCRIPT_H
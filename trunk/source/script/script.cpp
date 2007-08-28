
#include "script.h"

#include "../log.h"

namespace Small
{
Script::Script()
{
	int error;

	l = lua_open();

	luaL_openlibs(l);
	tolua_bindings_open(l);

	error = luaL_dofile(l, "resources/scripts/global.lua");
	if( error )
	{
		Log::Instance().Write("LuaError: %s", lua_tostring(l, -1) );
		lua_pop(l, 1);
	}
}

Script::~Script()
{
	lua_close(l);
}

// PENDIENTE: dependiendo del tipo de evento a levantar habrá que aportar algún parámetro o algo.
void Script::RaiseEvent(char *Event)
{
	int error;
	char buffer[255];

	sprintf(buffer, "%s();", Event);

	error = luaL_loadbuffer(l, buffer, strlen(buffer), "Event") || 
			lua_pcall(l, 0, 0, 0);

	if( error )
	{
		Log::Instance().Write("LuaError: %s", lua_tostring(l, -1) );
		lua_pop(l, 1);
	}
}

} // namespace Small
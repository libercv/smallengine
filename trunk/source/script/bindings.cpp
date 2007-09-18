/*
** Lua binding: bindings
** Generated automatically by tolua 5.1b on 09/15/07 23:22:17.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua.h"

/* Exported function */
TOLUA_API int tolua_bindings_open (lua_State* tolua_S);
LUALIB_API int luaopen_bindings (lua_State* tolua_S);


/* function to release collected object */
#ifdef __cplusplus
#else
static int tolua_collect (lua_State* tolua_S)
{
 void* self = tolua_tousertype(tolua_S,1,0);
 free(self);
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"StateGame");
 tolua_usertype(tolua_S,"Log");
}

/* method: Instance of class  Log */
static int tolua_bindings_Log_Instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Log",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  Log& tolua_ret = (Log&)  Log::Instance();
 tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Log");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Instance'.",&tolua_err);
 return 0;
#endif
}

/* method: LuaWrite of class  Log */
static int tolua_bindings_Log_LuaWrite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Log",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Log* self = (Log*)  tolua_tousertype(tolua_S,1,0);
  const char* Text = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaWrite'",NULL);
#endif
 {
  self->LuaWrite(Text);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaWrite'.",&tolua_err);
 return 0;
#endif
}

/* method: Instance of class  StateGame */
static int tolua_bindings_StateGame_Instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"StateGame",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  StateGame& tolua_ret = (StateGame&)  StateGame::Instance();
 tolua_pushusertype(tolua_S,(void*)&tolua_ret,"StateGame");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Instance'.",&tolua_err);
 return 0;
#endif
}

/* method: KillPlayer of class  StateGame */
static int tolua_bindings_StateGame_KillPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"StateGame",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  StateGame* self = (StateGame*)  tolua_tousertype(tolua_S,1,0);
  char* PlayerId = ((char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'KillPlayer'",NULL);
#endif
 {
  self->KillPlayer(PlayerId);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'KillPlayer'.",&tolua_err);
 return 0;
#endif
}

/* method: KillObject of class  StateGame */
static int tolua_bindings_StateGame_KillObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"StateGame",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  StateGame* self = (StateGame*)  tolua_tousertype(tolua_S,1,0);
  char* PlayerId = ((char*)  tolua_tostring(tolua_S,2,0));
  char* ObjectId = ((char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'KillObject'",NULL);
#endif
 {
  self->KillObject(PlayerId,ObjectId);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'KillObject'.",&tolua_err);
 return 0;
#endif
}

/* method: SetActiveCamera of class  StateGame */
static int tolua_bindings_StateGame_SetActiveCamera00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"StateGame",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  StateGame* self = (StateGame*)  tolua_tousertype(tolua_S,1,0);
  int NewActiveCamera = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetActiveCamera'",NULL);
#endif
 {
  self->SetActiveCamera(NewActiveCamera);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetActiveCamera'.",&tolua_err);
 return 0;
#endif
}

/* Open lib function */
LUALIB_API int luaopen_bindings (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"Log","Log","",0);
#else
 tolua_cclass(tolua_S,"Log","Log","",tolua_collect);
#endif
 tolua_beginmodule(tolua_S,"Log");
 tolua_function(tolua_S,"Instance",tolua_bindings_Log_Instance00);
 tolua_function(tolua_S,"LuaWrite",tolua_bindings_Log_LuaWrite00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"StateGame","StateGame","",0);
#else
 tolua_cclass(tolua_S,"StateGame","StateGame","",tolua_collect);
#endif
 tolua_beginmodule(tolua_S,"StateGame");
 tolua_function(tolua_S,"Instance",tolua_bindings_StateGame_Instance00);
 tolua_function(tolua_S,"KillPlayer",tolua_bindings_StateGame_KillPlayer00);
 tolua_function(tolua_S,"KillObject",tolua_bindings_StateGame_KillObject00);
 tolua_function(tolua_S,"SetActiveCamera",tolua_bindings_StateGame_SetActiveCamera00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}
/* Open tolua function */
TOLUA_API int tolua_bindings_open (lua_State* tolua_S)
{
 lua_pushcfunction(tolua_S, luaopen_bindings);
 lua_pushstring(tolua_S, "bindings");
 lua_call(tolua_S, 1, 0);
 return 1;
}

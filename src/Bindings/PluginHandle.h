
#pragma once

#include "PluginManager.h"


// tolua_begin
class cPluginHandle
{
public:
	// tolua_end
	
	cPluginHandle(CPlugin * const a_Plugin);
	virtual ~cPluginHandle();

	// tolua_begin
	const AString & GetName(void) const  { return m_Name; }
	
	int GetVersion(void) const     { return m_Version; }
	
	bool TryLoadLock();
	void ReleaseLoadLock;
	
		// The following templates allow calls to arbitrary Lua functions residing in the plugin:
	
	/// Call a Lua function with 0 args
	template <typename FnT> bool Call(FnT a_Fn)
	{
		cCSLock Lock(m_CriticalSection);
		return m_LuaState.Call(a_Fn);
	}

	/// Call a Lua function with 1 arg
	template <typename FnT, typename ArgT0> bool Call(FnT a_Fn, ArgT0 a_Arg0)
	{
		cCSLock Lock(m_CriticalSection);
		return m_LuaState.Call(a_Fn, a_Arg0);
	}

	/// Call a Lua function with 2 args
	template <typename FnT, typename ArgT0, typename ArgT1> bool Call(FnT a_Fn, ArgT0 a_Arg0, ArgT1 a_Arg1)
	{
		cCSLock Lock(m_CriticalSection);
		return m_LuaState.Call(a_Fn, a_Arg0, a_Arg1);
	}

	/// Call a Lua function with 3 args
	template <typename FnT, typename ArgT0, typename ArgT1, typename ArgT2> bool Call(FnT a_Fn, ArgT0 a_Arg0, ArgT1 a_Arg1, ArgT2 a_Arg2)
	{
		cCSLock Lock(m_CriticalSection);
		return m_LuaState.Call(a_Fn, a_Arg0, a_Arg1, a_Arg2);
	}

	/// Call a Lua function with 4 args
	template <typename FnT, typename ArgT0, typename ArgT1, typename ArgT2, typename ArgT3> bool Call(FnT a_Fn, ArgT0 a_Arg0, ArgT1 a_Arg1, ArgT2 a_Arg2, ArgT3 a_Arg3)
	{
		cCSLock Lock(m_CriticalSection);
		return m_LuaState.Call(a_Fn, a_Arg0, a_Arg1, a_Arg2, a_Arg3);
	}

	// tolua_end

private:
	Plugin * m_Plugin;
	bool PluginLoaded;

};	// tolua_export

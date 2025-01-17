// See the file "COPYING" in the main distribution directory for copyright.

// Low-level support utilities/globals for ZAM compilation.

#pragma once

#include "zeek/Expr.h"
#include "zeek/Stmt.h"
#include "zeek/script_opt/ZAM/Profile.h"

namespace zeek::detail {

using ValVec = std::vector<ValPtr>;

namespace ZAM {

// The name of the current function being compiled. For inlined functions,
// this is the name of the inlinee, not the inliner.
extern std::string curr_func;

// The location corresponding to the current statement being compiled.
extern std::shared_ptr<ZAMLocInfo> curr_loc;

// Needed for the logging built-in.  Exported so that ZAM can make sure it's
// defined when compiling.
extern TypePtr log_ID_enum_type;

// Needed for a slight performance gain when dealing with "any" types.
extern TypePtr any_base_type;

} // namespace ZAM

// True if a function with the given profile can be compiled to ZAM.
// If not, returns the reason in *reason, if non-nil.
class ProfileFunc;
extern bool is_ZAM_compilable(const ProfileFunc* pf, const char** reason = nullptr);

// True if a given type is one that we treat internally as an "any" type.
extern bool IsAny(const Type* t);

// Convenience functions for getting to these.
inline bool IsAny(const TypePtr& t) { return IsAny(t.get()); }
inline bool IsAny(const Expr* e) { return IsAny(e->GetType()); }

// Run-time checking for "any" type being consistent with
// expected typed.  Returns true if the type match is okay.
extern bool CheckAnyType(const TypePtr& any_type, const TypePtr& expected_type, const std::shared_ptr<ZAMLocInfo>& loc);

extern void ZAM_run_time_error(const char* msg);
extern void ZAM_run_time_error(std::shared_ptr<ZAMLocInfo> loc, const char* msg);
extern void ZAM_run_time_error(std::shared_ptr<ZAMLocInfo> loc, const char* msg, const Obj* o);
extern void ZAM_run_time_error(const Stmt* stmt, const char* msg);
extern void ZAM_run_time_error(const char* msg, const Obj* o);

extern bool ZAM_error;

extern void ZAM_run_time_warning(std::shared_ptr<ZAMLocInfo> loc, const char* msg);

extern StringVal* ZAM_to_lower(const StringVal* sv);
extern StringVal* ZAM_sub_bytes(const StringVal* s, zeek_uint_t start, zeek_int_t n);

extern StringValPtr ZAM_val_cat(const ValPtr& v);

} // namespace zeek::detail

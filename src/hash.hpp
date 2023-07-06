#pragma once 

#include <intercept.hpp>
#include <hash_table8.hpp>

class game_data_hashmap_new : public game_data
{
public:
	game_data_hashmap_new(){}
	game_data_hashmap_new(const emhash8::HashMap<game_value, game_value>& hash) {}
	void lastRefDeleted() const override{ delete this; }
	const sqf_script_type& type() const override;
	~game_data_hashmap_new(){}

	bool get_as_bool() const override { return true;}
	float get_as_number() const override { return 0.f;}
	const r_string& get_as_string() const override { static r_string nm("HASHMAP"sv); return nm; }
	game_data* copy() const override { return new game_data_hashmap_new(*this); }
	r_string to_string() const override { return r_string("HASHMAP"sv);}
	const char* type_as_string() const override { return "HASHMAP";}
	bool is_nil() const override { return false; }
	bool can_serialize() override { return true; }
	serialization_return serialize(param_archive& ar) override;
	emhash8::HashMap<game_value, game_value> hashmap;
};

class CallStackItemHashmapNewForEach : public vm_context::callstack_item
{
public:
	intercept::types::ref<game_data_hashmap_new> _hashmap;
	intercept::types::ref<game_data_code> _code;
	emhash8::HashMap<game_value, game_value>::iterator _iter;
	unsigned int _index;
	bool _exitOrBreak;

	CallStackItemHashmapNewForEach(){}
	CallStackItemHashmapNewForEach(game_data_hashmap_new* hashmap, game_data_code* code, vm_context::callstack_item* parent, game_var_space varSpace, int stackPos, game_state* gs);


	virtual game_instruction* next(int& d1, const game_state* s);
	virtual bool someEH(void* state);
	virtual bool someEH2(void* state);

	virtual r_string get_type() const;

	virtual serialization_return serialize(param_archive& ar);

	virtual void on_before_exec();

	virtual const char* getName() const
	{
		return "FrameBody";
	};
	virtual int varCount() const
	{
		return 1;
	}
	virtual int getVariables(const IDebugVariable** storage, int count) const
	{
		return 1;
	}
	virtual __internal::I_debug_value::RefType EvaluateExpression(const char* code, unsigned int rad)
	{
		return game_value(1).data.get();
	}
	virtual void getSourceDocPosition(char* file, int fileSize, int& line)
	{
		file[0] = 0;
		line = 0;
	}
	virtual IDebugScope* getParent()
	{
		return _parent;
	}
};

class CallStackItemHashmapNewApply : public vm_context::callstack_item
{
public:
	intercept::types::ref<game_data_hashmap_new> _hashmap;
	intercept::types::ref<game_data_code> _code;
	emhash8::HashMap<game_value, game_value>::iterator _iter;
	auto_array<game_value> _array;
	int _index;
	bool _exitOrBreak;

	CallStackItemHashmapNewApply()
	{
	}
	CallStackItemHashmapNewApply(game_data_hashmap_new* hashmap, game_data_code* code, vm_context::callstack_item* parent, game_var_space varSpace, int stackPos, game_state* gs);


	virtual game_instruction* next(int& d1, const game_state* s);
	virtual bool someEH(void* state);
	virtual bool someEH2(void* state);

	virtual r_string get_type() const;

	virtual serialization_return serialize(param_archive& ar);

	virtual void on_before_exec();

	virtual const char* getName() const
	{
		return "FrameBody";
	};
	virtual int varCount() const
	{
		return 1;
	}
	virtual int getVariables(const IDebugVariable** storage, int count) const
	{
		return 1;
	}
	virtual __internal::I_debug_value::RefType EvaluateExpression(const char* code, unsigned int rad)
	{
		return game_value(1).data.get();
	}
	virtual void getSourceDocPosition(char* file, int fileSize, int& line)
	{
		file[0] = 0;
		line = 0;
	}
	virtual IDebugScope* getParent()
	{
		return _parent;
	}
};

// game_data_code encapsulation
class CallStackItemData : public vm_context::callstack_item
{
public:
	intercept::types::ref<game_data_code> _code;
	int _programCounter;
	CallStackItemData( game_data_code* code, vm_context::callstack_item* parent, game_var_space varSpace, int stackPos, const game_state* gs);

	virtual game_instruction* next(int& d1, const game_state* s);
	virtual bool someEH(void* state);
	virtual bool someEH2(void* state);

	virtual r_string get_type() const
	{
		return r_string("yes");
	}

	virtual serialization_return serialize(param_archive& ar);

	virtual void on_before_exec();

	virtual const char* getName() const
	{
		return "Frame";
	};
	virtual int varCount() const
	{
		return 1;
	}
	virtual int getVariables(const IDebugVariable** storage, int count) const
	{
		return 1;
	}
	virtual __internal::I_debug_value::RefType EvaluateExpression(const char* code, unsigned int rad)
	{
		return game_value(1).data.get();
	}
	virtual void getSourceDocPosition(char* file, int fileSize, int& line)
	{
		file[0] = 0;
		line = 0;
	}
	virtual IDebugScope* getParent()
	{
		return _parent;
	}
};

enum execution
{
	continueEx, // continue the next instruction ???
	continueEx2, // continue with the next instruction ??? don't know why there is two execution controls
	done, // level done
	interrupt // execution is suspended
};

void pre_start_hashing();
#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "object/Class.h"
#include "object/Instance.h"

// Note: Primitives cannot be constructed in code

//////////
// Null //
//////////
class Null : public Class {
public:
	Null() : Class(nullptr, "Null", nullptr) {}
	virtual ~Null() = default;

	bool truthy() const override {
		return false;
	}

	bool equals(Object * other) const override {
		return dynamic_cast<Null*>(other);
	}

	std::string to_string() const override {
		return "<Null>";
	}

	instance_ptr make_instance(scope_ptr closure){
		return std::make_shared<Instance>(closure, this);
	}

private:
	obj_ptr call(Interpreter & ip, ObjList && args) override {
		return nullptr;
	}

	// Null cannot be copied
	obj_ptr clone() const override {
		return nullptr;
	}
};

const auto NullClass = std::make_shared<Null>();

class NullObject : public Instance {
public:
	NullObject() : Instance(scope_ptr closure, NullClass.get()) {}
}

//////////
// Bool //
//////////
class Bool : public Class {
public:
	Bool(const bool & b) : Class(nullptr, "Bool", nullptr), value(b)  {}
	virtual ~Bool() = default;

	bool get_value() const {
		return value;
	}

	bool truthy() const override {
		return value;
	}

	bool equals(Object * other) const override {
		Bool * b = dynamic_cast<Bool*>(other);
		return b && value == b->get_value();
	}

	obj_ptr clone() const override {
		return std::make_shared<Bool>(value);
	}

	std::string to_string() const override {
		return "<Bool:"+ std::to_string(value) + ">";
	}

private:
	bool value;
};

const auto BoolClass = std::make_shared<Bool>();

/////////
// Int //
/////////
class Int : public Object {
public:
	Int(const int & i) : Object(ObjectType::Int), value(i) {}
	virtual ~Int() = default;

	int get_value() const {
		return value;
	}

	bool equals(Object * other) const override {
		if(other->type == ObjectType::Float){
			return false;
		}
		return value == static_cast<Int*>(other)->get_value();
	}

	obj_ptr clone() const override {
		return std::make_shared<Int>(value);
	}

	std::string to_string() const override {
		return "<Int:"+ std::to_string(value) +">";
	}

private:
	int value;
};

///////////
// Float //
///////////
class Float : public Object {
public:
	Float(const double & d) : Object(ObjectType::Float), value(d) {}
	virtual ~Float() = default;

	double get_value() const {
		return value;
	}

	bool equals(Object * other) const override {
		if(other->type != ObjectType::Float){
			return false;
		}
		return value == static_cast<Float*>(other)->get_value();
	}

	obj_ptr clone() const override {
		return std::make_shared<Float>(value);
	}

	std::string to_string() const override {
		return "<Float:"+ std::to_string(value) + ">";
	}

private:
	double value;
};

////////////
// String //
////////////
class String : public Object {
public:
	String(const std::string & s) : Object(ObjectType::String), value(s) {}
	virtual ~String() = default;

	std::string get_value() const {
		return value;
	}

	bool equals(Object * other) const override {
		if(other->type != ObjectType::String){
			return false;
		}
		return value == static_cast<String*>(other)->get_value();
	}

	obj_ptr clone() const override {
		return std::make_shared<String>(value);
	}

	std::string to_string() const override {
		return "<String:'"+ value +"'>";
	}

private:
	std::string value;
};

#endif
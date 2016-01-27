#ifndef __PDDL_DAE_H__
#define __PDDL_DAE_H__
#include <iostream>
#include <string>
#include <vector>
namespace daex
{
class pddlType 
{
public:
    pddlType( std::string name ) : _name(name) { }
    std::string name() const { return this->_name; }
protected:
     std::string _name;
public:
    friend std::ostream& operator<<( std::ostream& out, const pddlType & type )
    {
        out << type._name;
	return out;
    }
};
class pddlObject
{
public:
    pddlObject( std::vector< pddlType > types, 
                std::string value 
              ) : _types(types), _value(value) { }
public:
    std::vector< pddlType > types() const { return this->_types; }
    std::string value() const { return this->_value; }
protected:
    const std::vector< pddlType > _types;
    const std::string             _value;
public:
    friend std::ostream& operator<<( std::ostream& out, const pddlObject & obj )
    {
        out << obj._value;
	return out;
    }
};
class pddlPredicate
{
public:
    pddlPredicate( std::string name, unsigned int arity ) : _name(name), _arity(arity) { }
public:
    std::string name() const { return this->_name; }
    unsigned int arity() const { return this->_arity; }
protected:
    const std::string _name;
    const unsigned int _arity;
public:
    friend std::ostream& operator<<( std::ostream& out, const pddlPredicate & pred )
    {
        out << pred._name;
	return out;
    }
};
} 
#endif

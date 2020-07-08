#ifndef BASEVISITOR_H
#define BASEVISITOR_H

#include <vector>
#include <memory>

struct Node;
struct ExprStmt;
struct Literal;
struct Identifier;
struct VarDecl;
struct Block;
struct FuncDecl;
struct FuncCall;
struct Infix;
struct IfExpr;
struct While;
struct ReturnStmt;
struct ClassDecl;

class BaseVisitor {
public:
	BaseVisitor() {}
	virtual ~BaseVisitor() = default;
	
	virtual void visit(ExprStmt * expr_stmt) = 0;
	virtual void visit(Literal * literal) = 0;
	virtual void visit(Identifier * id) = 0;
	virtual void visit(VarDecl * var_decl) = 0;
	virtual void visit(Block * block) = 0;
	virtual void visit(FuncDecl * func_decl) = 0;
	virtual void visit(FuncCall * func_call) = 0;
	virtual void visit(Infix * infix) = 0;
	virtual void visit(IfExpr * if_expr) = 0;
	virtual void visit(While * w) = 0;
	virtual void visit(ReturnStmt * return_stmt) = 0;
	virtual void visit(ClassDecl * class_decl) = 0;
	
};

#endif
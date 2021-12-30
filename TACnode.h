#ifndef _TACNODE_H
#define _TACNODE_H
#include "syntax_tree.h"
#include <iostream>
#include <stack>
#include <stdlib.h>
#include <string.h>
//#define _DEBUG_PRINT_TREE

#define VISIT_CHILDREN                     \
    for (int i = 0; i < children_num; ++i) \
    {                                      \
        if (children[i])                   \
        {                                  \
            children[i]->visit();          \
        }                                  \
    }

/*
 * 简单实现版：
 * 没有考虑
 * 1. 每个函数如何计算要保留多少空间、要恢复多少空间
 * 2. 数组变量
 * 3. 仅测试了test下的6个简单例子
 * 4. 对于a=call func()这种，现在的逻辑会输出a=然后pushp然后call（目前逻辑：call上下紧邻push和pop）
 */

syntax_tree_node *new_TACnode(std::string kind);
//返回新树的根
syntax_tree_node *turn_to_TACnode(syntax_tree_node *node);

void del_TACtree(syntax_tree_node *node);

void println(std::string s, int indent = 0);

void print(std::string s, int indent = 0);

std::string alloc_label();

std::string alloc_loc();

class program_node : public _syntax_tree_node
{
public:
    void visit();
};

class declaration_list_node : public _syntax_tree_node
{
public:
    void visit();
};

class declaration_node : public _syntax_tree_node
{
public:
    void visit();
};

class var_declaration_node : public _syntax_tree_node
{
public:
    void visit();
};

class type_specifier_node : public _syntax_tree_node
{
public:
    void visit();
};

class fun_declaration_node : public _syntax_tree_node
{
public:
    void visit();
};

class params_node : public _syntax_tree_node
{
public:
    void visit();
};

class param_list_node : public _syntax_tree_node
{
public:
    void visit();
};

class param_node : public _syntax_tree_node
{
public:
    void visit();
};

class compound_stmt_node : public _syntax_tree_node
{
public:
    void visit();
};

class local_declarations_node : public _syntax_tree_node
{
public:
    void visit();
};

class statement_list_node : public _syntax_tree_node
{
public:
    void visit();
};

class statement_node : public _syntax_tree_node
{
public:
    void visit();
};

class expression_stmt_node : public _syntax_tree_node
{
public:
    void visit();
};

class selection_stmt_node : public _syntax_tree_node
{
public:
    void visit();
};

class iteration_stmt_node : public _syntax_tree_node
{
public:
    void visit();
};

class return_stmt_node : public _syntax_tree_node
{
public:
    void visit();
};

class expression_node : public _syntax_tree_node
{
public:
    void visit();
};

class var_node : public _syntax_tree_node
{
public:
    void visit();
};

class simple_expression_node : public _syntax_tree_node
{
public:
    void visit();
};

class relop_node : public _syntax_tree_node
{
public:
    void visit();
};

class additive_expression_node : public _syntax_tree_node
{
public:
    void visit();
};

class addop_node : public _syntax_tree_node
{
public:
    void visit();
};

class term_node : public _syntax_tree_node
{
public:
    void visit();
};

class mulop_node : public _syntax_tree_node
{
public:
    void visit();
};

class factor_node : public _syntax_tree_node
{
public:
    void visit();
};

class integer_node : public _syntax_tree_node
{
public:
    void visit();
};

class float_node : public _syntax_tree_node
{
public:
    void visit();
};

class call_node : public _syntax_tree_node
{
public:
    void visit();
};

class args_node : public _syntax_tree_node
{
public:
    void visit();
};

class arg_list_node : public _syntax_tree_node
{
public:
    void visit();
};

/*
 * 终结符
 */

class ADD_node : public _syntax_tree_node
{
public:
    void visit();
};

class SUB_node : public _syntax_tree_node
{
public:
    void visit();
};

class MUL_node : public _syntax_tree_node
{
public:
    void visit();
};

class DIV_node : public _syntax_tree_node
{
public:
    void visit();
};

class LT_node : public _syntax_tree_node
{
public:
    void visit();
};

class GT_node : public _syntax_tree_node
{
public:
    void visit();
};

class ASSIN_node : public _syntax_tree_node
{
public:
    void visit();
};

class SEMICOLON_node : public _syntax_tree_node
{
public:
    void visit();
};

class COMMA_node : public _syntax_tree_node
{
public:
    void visit();
};

class LPARENTHESE_node : public _syntax_tree_node
{
public:
    void visit();
};

class RPARENTHESE_node : public _syntax_tree_node
{
public:
    void visit();
};

class LBRACE_node : public _syntax_tree_node
{
public:
    void visit();
};

class RBRACE_node : public _syntax_tree_node
{
public:
    void visit();
};

class LTE_node : public _syntax_tree_node
{
public:
    void visit();
};

class GTE_node : public _syntax_tree_node
{
public:
    void visit();
};

class EQ_node : public _syntax_tree_node
{
public:
    void visit();
};

class NEQ_node : public _syntax_tree_node
{
public:
    void visit();
};

class ELSE_node : public _syntax_tree_node
{
public:
    void visit();
};

class IF_node : public _syntax_tree_node
{
public:
    void visit();
};

class INT_node : public _syntax_tree_node
{
public:
    void visit();
};

class FLOAT_node : public _syntax_tree_node
{
public:
    void visit();
};

class RETURN_node : public _syntax_tree_node
{
public:
    void visit();
};

class VOID_node : public _syntax_tree_node
{
public:
    void visit();
};

class WHILE_node : public _syntax_tree_node
{
public:
    void visit();
};

class ARRAY_node : public _syntax_tree_node
{
public:
    void visit();
};

class LBRACKET_node : public _syntax_tree_node
{
public:
    void visit();
};

class RBRACKET_node : public _syntax_tree_node
{
public:
    void visit();
};

class IDENTIFIER_node : public _syntax_tree_node
{
public:
    void visit();
};

class LETTER_node : public _syntax_tree_node
{
public:
    void visit();
};

class INTEGER_node : public _syntax_tree_node
{
public:
    void visit();
};

class FLOATPOINT_node : public _syntax_tree_node
{
public:
    void visit();
};

#endif //_TACNODE_H

#include "TACnode.h"

extern std::stack<std::string> locstack;
extern std::stack<std::string> locstack;
extern int depth;
extern int label_cnt;
extern int loc_cnt;

std::string alloc_label()
{
    return "_L" + std::to_string(label_cnt++);
}

std::string alloc_loc()
{
    return "_t" + std::to_string(loc_cnt++);
}

void println(std::string s, int indent)
{
    for (int i = 0; i < indent; ++i)
    {
        std::cout << "    ";
    }
    std::cout << s << std::endl;
}

void print(std::string s, int indent)
{
    for (int i = 0; i < indent; ++i)
    {
        std::cout << "    ";
    }
    std::cout << s;
}

syntax_tree_node *new_TACnode(std::string kind)
{
    if (kind == "program")
    {
        return new program_node;
    }
    if (kind == "declaration_list")
    {
        return new declaration_list_node;
    }
    if (kind == "declaration")
    {
        return new declaration_node;
    }
    if (kind == "var_declaration")
    {
        return new var_declaration_node;
    }
    if (kind == "type_specifier")
    {
        return new type_specifier_node;
    }
    if (kind == "fun_declaration")
    {
        return new fun_declaration_node;
    }
    if (kind == "params")
    {
        return new params_node;
    }
    if (kind == "param_list")
    {
        return new param_list_node;
    }
    if (kind == "param")
    {
        return new param_node;
    }
    if (kind == "compound_stmt")
    {
        return new compound_stmt_node;
    }
    if (kind == "local_declarations")
    {
        return new local_declarations_node;
    }
    if (kind == "statement_list")
    {
        return new statement_list_node;
    }
    if (kind == "statement")
    {
        return new statement_node;
    }
    if (kind == "expression_stmt")
    {
        return new expression_stmt_node;
    }
    if (kind == "selection_stmt")
    {
        return new selection_stmt_node;
    }
    if (kind == "iteration_stmt")
    {
        return new iteration_stmt_node;
    }
    if (kind == "return_stmt")
    {
        return new return_stmt_node;
    }
    if (kind == "expression")
    {
        return new expression_node;
    }
    if (kind == "var")
    {
        return new var_node;
    }
    if (kind == "simple_expression")
    {
        return new simple_expression_node;
    }
    if (kind == "relop")
    {
        return new relop_node;
    }
    if (kind == "additive_expression")
    {
        return new additive_expression_node;
    }
    if (kind == "addop")
    {
        return new addop_node;
    }
    if (kind == "term")
    {
        return new term_node;
    }
    if (kind == "mulop")
    {
        return new mulop_node;
    }
    if (kind == "factor")
    {
        return new factor_node;
    }
    if (kind == "integer")
    {
        return new integer_node;
    }
    if (kind == "float")
    {
        return new float_node;
    }
    if (kind == "call")
    {
        return new call_node;
    }
    if (kind == "args")
    {
        return new args_node;
    }
    if (kind == "arg_list")
    {
        return new arg_list_node;
    }
    if (kind == "ADD")
    {
        return new ADD_node;
    }
    if (kind == "SUB")
    {
        return new SUB_node;
    }
    if (kind == "MUL")
    {
        return new MUL_node;
    }
    if (kind == "DIV")
    {
        return new DIV_node;
    }
    if (kind == "LT")
    {
        return new LT_node;
    }
    if (kind == "GT")
    {
        return new GT_node;
    }
    if (kind == "ASSIN")
    {
        return new ASSIN_node;
    }
    if (kind == "SEMICOLON")
    {
        return new SEMICOLON_node;
    }
    if (kind == "COMMA")
    {
        return new COMMA_node;
    }
    if (kind == "LPARENTHESE")
    {
        return new LPARENTHESE_node;
    }
    if (kind == "RPARENTHESE")
    {
        return new RPARENTHESE_node;
    }
    if (kind == "LBRACE")
    {
        return new LBRACE_node;
    }
    if (kind == "RBRACE")
    {
        return new RBRACE_node;
    }
    if (kind == "LTE")
    {
        return new LTE_node;
    }
    if (kind == "GTE")
    {
        return new GTE_node;
    }
    if (kind == "EQ")
    {
        return new EQ_node;
    }
    if (kind == "NEQ")
    {
        return new NEQ_node;
    }
    if (kind == "ELSE")
    {
        return new ELSE_node;
    }
    if (kind == "IF")
    {
        return new IF_node;
    }
    if (kind == "INT")
    {
        return new INT_node;
    }
    if (kind == "FLOAT")
    {
        return new FLOAT_node;
    }
    if (kind == "RETURN")
    {
        return new RETURN_node;
    }
    if (kind == "VOID")
    {
        return new VOID_node;
    }
    if (kind == "WHILE")
    {
        return new WHILE_node;
    }
    if (kind == "ARRAY")
    {
        return new ARRAY_node;
    }
    if (kind == "LBRACKET")
    {
        return new LBRACKET_node;
    }
    if (kind == "RBRACKET")
    {
        return new RBRACKET_node;
    }
    if (kind == "IDENTIFIER")
    {
        return new IDENTIFIER_node;
    }
    if (kind == "LETTER")
    {
        return new LETTER_node;
    }
    if (kind == "INTEGER")
    {
        return new INTEGER_node;
    }
    if (kind == "FLOATPOINT")
    {
        return new FLOATPOINT_node;
    }
    return nullptr;
}

//返回新树的根
syntax_tree_node *turn_to_TACnode(syntax_tree_node *node)
{
    std::string name = node->name, yytext = node->yytext;
    //替换其中的-（最多出现一次-）
    size_t idx = name.find('-');
    if (idx != std::string::npos)
    {
        *(name.begin() + idx) = '_';
    }
    syntax_tree_node *new_node = new_TACnode(name);
    if (new_node != nullptr)
    {
        if (name.c_str())
            strncpy(new_node->name, name.c_str(), SYNTAX_TREE_NODE_NAME_MAX);
        else
            new_node->name[0] = '\0';

        if (yytext.c_str())
            strncpy(new_node->yytext, yytext.c_str(), SYNTAX_TREE_NODE_NAME_MAX);
        else
            new_node->yytext[0] = '\0';

        int num = node->children_num;
        new_node->children_num = num;
        for (int i = 0; i < num; ++i)
        {
            new_node->children[i] = turn_to_TACnode(node->children[i]);
        }
    }
    return new_node;
}

void del_TACtree(syntax_tree_node *node)
{
    if (node == nullptr)
    {
        return;
    }
    //child
    for (int i = 0; i < node->children_num; ++i)
    {
        if (node->children[i])
            delete node->children[i];
    }
    delete node;
}

/*
 * 语法结点
 */

void program_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    depth = 0;
    println("program", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
    label_cnt = 0;
    loc_cnt = 0;
    while (locstack.empty() == 0)
    {
        locstack.pop();
    }
}

void declaration_list_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("declaration_list", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void declaration_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("declaration", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void var_declaration_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("var_declaration", depth);
#endif //_DEBUG_PRINT_TREE
    //VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void type_specifier_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("type_specifier", depth);
#endif //_DEBUG_PRINT_TREE
    //VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void fun_declaration_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("fun_declaration", depth);
#endif //_DEBUG_PRINT_TREE

    children[1]->visit();
    std::string funname = locstack.top();
    locstack.pop();
    println("_" + funname + ":");
    println("BeginFunc N", 1);
    children[5]->visit();
    println("EndFunc", 1);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void params_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("params", depth);
#endif //_DEBUG_PRINT_TREE
    //VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void param_list_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("param_list", depth);
#endif //_DEBUG_PRINT_TREE
    //VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void param_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("param", depth);
#endif //_DEBUG_PRINT_TREE
    //VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void compound_stmt_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("compound_stmt", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void local_declarations_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("local_declarations", depth);
#endif //_DEBUG_PRINT_TREE
    //VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void statement_list_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("statement_list", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void statement_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("statement", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void expression_stmt_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("expression_stmt", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void selection_stmt_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("selection_stmt", depth);
#endif                    //_DEBUG_PRINT_TREE
    children[2]->visit(); //condition expression,把地址放栈顶
    std::string cond_str = locstack.top();
    locstack.pop();
    std::string falseL = alloc_label(), endL;
    if (children_num == 7)
    {
        //if else
        endL = alloc_label();
    }
    else
    {
        endL = falseL;
    }
    println("Ifz " + cond_str + " Goto " + falseL, 1);
    //if_s
    children[4]->visit();
    println("Goto " + endL, 1);
    println(falseL + ":");
    if (children_num == 7)
    {
        //if else
        //else_s
        children[6]->visit();
        println(endL + ":");
    }

#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void iteration_stmt_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("iteration_stmt", depth);
#endif //_DEBUG_PRINT_TREE
    std::string testL = alloc_label(), endL = alloc_label();
    println(testL + ":");
    children[2]->visit(); //condition expression,把地址放栈顶
    std::string cond_str = locstack.top();
    locstack.pop();
    println("Ifz " + cond_str + " Goto " + endL, 1);
    //body
    children[4]->visit();
    println("Goto " + testL, 1);
    println(endL + ":");
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void return_stmt_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("return_stmt", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void expression_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("expression", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
    if (children_num == 3)
    {
        //assign
        std::stack<std::string> tmp;
        for (int i = 0; i < children_num; ++i)
        {
            tmp.push(locstack.top());
            locstack.pop();
        }
        print("", 1);
        for (int i = 0; i < children_num; ++i)
        {
            print(tmp.top() + " ");
            tmp.pop();
        }
        println("");
    }
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void var_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("var", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void simple_expression_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("simple_expression", depth);
#endif //_DEBUG_PRINT_TREE
    if (children_num == 3)
    {
        //additive-expression  relop  additive-expression
        children[1]->visit();
        std::string op = locstack.top();
        locstack.pop();
        children[0]->visit();
        std::string left = locstack.top();
        locstack.pop();
        children[2]->visit();
        std::string right = locstack.top();
        locstack.pop();

        std::string re_loc = alloc_loc();
        println(re_loc + " = " + left + " " + op + " " + right, 1);
        locstack.push(re_loc);
    }
    else
    {
        //additive-expression
        VISIT_CHILDREN
    }
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void relop_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("relop", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void additive_expression_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("additive_expression", depth);
#endif //_DEBUG_PRINT_TREE
    if (children_num == 3)
    {
        //additive-expression  addop  term
        children[1]->visit();
        std::string op = locstack.top();
        locstack.pop();
        children[0]->visit();
        std::string left = locstack.top();
        locstack.pop();
        children[2]->visit();
        std::string right = locstack.top();
        locstack.pop();

        std::string re_loc = alloc_loc();
        println(re_loc + " = " + left + " " + op + " " + right, 1);
        locstack.push(re_loc);
    }
    else
    {
        //term
        VISIT_CHILDREN
    }
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void addop_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("addop", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void term_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("term", depth);
#endif //_DEBUG_PRINT_TREE
    if (children_num == 3)
    {
        //term  mulop  factor
        children[1]->visit();
        std::string op = locstack.top();
        locstack.pop();
        children[0]->visit();
        std::string left = locstack.top();
        locstack.pop();
        children[2]->visit();
        std::string right = locstack.top();
        locstack.pop();

        std::string re_loc = alloc_loc();
        println(re_loc + " = " + left + " " + op + " " + right, 1);
        locstack.push(re_loc);
    }
    else
    {
        //factor
        VISIT_CHILDREN
    }
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void mulop_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("mulop", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void factor_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("factor", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void integer_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("integer", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void float_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("float", depth);
#endif //_DEBUG_PRINT_TREE
    VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void call_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("call", depth);
#endif //_DEBUG_PRINT_TREE
    //参数入栈
    children[2]->visit();
    //函数名
    children[0]->visit();
    std::string funname = locstack.top();
    locstack.pop();
    println("LCall _" + funname, 1);
    if (children[2]->children_num > 0)
    {
        println("PopParmams N", 1);
    }
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void args_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("args", depth);
#endif //_DEBUG_PRINT_TREE
    //参数入栈
    VISIT_CHILDREN
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void arg_list_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("arg_list", depth);
#endif //_DEBUG_PRINT_TREE
    //参数逆序入栈
    children[children_num - 1]->visit(); //exp
    println("PushParam " + locstack.top());
    locstack.pop();
    if (children_num > 1)
    {
        children[0]->visit();
    }
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

/*
 * 终结符结点：把yytext放栈顶
 * 操作符：放locstack栈顶
 * int float 注意分配位置输出赋值
 * ID,= 输出，不要换行
 */
void ADD_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("ADD", depth);
#endif //_DEBUG_PRINT_TREE
    locstack.push(yytext);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void SUB_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("SUB", depth);
#endif //_DEBUG_PRINT_TREE
    locstack.push(yytext);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void MUL_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("MUL", depth);
#endif //_DEBUG_PRINT_TREE
    locstack.push(yytext);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void DIV_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("DIV", depth);
#endif //_DEBUG_PRINT_TREE
    locstack.push(yytext);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void LT_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("LT", depth);
#endif //_DEBUG_PRINT_TREE
    locstack.push(yytext);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void GT_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("GT", depth);
#endif //_DEBUG_PRINT_TREE
    locstack.push(yytext);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void ASSIN_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("ASSIN", depth);
#endif //_DEBUG_PRINT_TREE
    locstack.push(yytext);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void SEMICOLON_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("SEMICOLON", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void COMMA_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("COMMA", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void LPARENTHESE_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("LPARENTHESE", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void RPARENTHESE_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("RPARENTHESE", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void LBRACE_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("LBRACE", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void RBRACE_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("RBRACE", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void LTE_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("LTE", depth);
#endif //_DEBUG_PRINT_TREE
    locstack.push(yytext);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void GTE_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("GTE", depth);
#endif //_DEBUG_PRINT_TREE
    locstack.push(yytext);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void EQ_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("EQ", depth);
#endif //_DEBUG_PRINT_TREE
    locstack.push(yytext);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void NEQ_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("NEQ", depth);
#endif //_DEBUG_PRINT_TREE
    locstack.push(yytext);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void ELSE_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("ELSE", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void IF_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("IF", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void INT_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("INT", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void FLOAT_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("FLOAT", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void RETURN_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("RETURN", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void VOID_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("VOID", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void WHILE_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("WHILE", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void ARRAY_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("ARRAY", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void LBRACKET_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("LBRACKET", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void RBRACKET_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("RBRACKET", depth);
#endif //_DEBUG_PRINT_TREE
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void IDENTIFIER_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("IDENTIFIER", depth);
#endif //_DEBUG_PRINT_TREE
    locstack.push(yytext);
    //print(yytext);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void LETTER_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("LETTER", depth);
#endif //_DEBUG_PRINT_TREE
    print(yytext);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void INTEGER_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("INTEGER", depth);
#endif //_DEBUG_PRINT_TREE
    std::string new_loc = alloc_loc();
    println(new_loc + " = " + yytext, 1);
    locstack.push(new_loc);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}

void FLOATPOINT_node::visit()
{
#ifdef _DEBUG_PRINT_TREE
    ++depth;
    println("FLOATPOINT", depth);
#endif //_DEBUG_PRINT_TREE
    std::string new_loc = alloc_loc();
    println(new_loc + " = " + yytext, 1);
    locstack.push(new_loc);
#ifdef _DEBUG_PRINT_TREE
    --depth;
#endif //_DEBUG_PRINT_TREE
}


#include "syntax_tree.h"
#include "TACnode.h"
extern syntax_tree *parse(const char *);

std::stack<std::string> locstack;
//std::stack<std::string> opstack;
int depth;
int label_cnt;
int loc_cnt;

int main(int argc, char *argv[])
{
    syntax_tree *tree = NULL;
    const char *input = NULL;

    if (argc >= 3)
    {
        printf("usage: %s\n", argv[0]);
        printf("usage: %s <cminus_file>\n", argv[0]);
        return 1;
    }

    if (argc == 2)
    {
        input = argv[1];
    }

    // Call the syntax analyzer.
    tree = parse(input);
    //将tree转成同步但是各结点有不同类型的树（现在节点类型体现在name字段中）
    syntax_tree_node *newtree = turn_to_TACnode(tree->root);
    //这些结点都继承自syntax_tree_node,有visit虚函数的实现

    //dfs对每个结点调用visit方法
    newtree->visit();
    //print_syntax_tree(stdout, tree);
    del_syntax_tree(tree);
    del_TACtree(newtree);
    return 0;
}


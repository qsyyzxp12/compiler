
## 1.Multiple and Division

Use two-level CFG rules without left recursion

expr -> term exprTail  
exprTail -> + term exprTail | - term exprTail  
term -> factor termTail  
termTail -> * factor termTail | / factor termTail  
factor -> digit | (expr)

## 2.Multiple Length Variables

use stl map structure to handle variable name and its register name

## 3.Constant Folding

recursively traverse all nodes in expression tree, if two children are all constant, do folding



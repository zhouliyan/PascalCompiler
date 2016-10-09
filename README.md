# PascalCompiler
 - 一个简单实用的Pascal语言编译器，用于<编译原理>的学习
 - CodeBlocks项目工程
 - 各文件含义如下：
<table>
    <tr>
        <th>文件</th>
        <th>用途</th>
    </tr>
    <tr>
        <td>code.txt</td>
        <td>Pascal源代码文件</td>
    </tr>
    <tr>
        <td>lex.txt</td>
        <td>生成词法分析后的文件</td>
    </tr>          
    <tr>
        <td>imcode.txt</td>
        <td>生成的中间代码文件</td>
    </tr>
    <tr>           
        <td>yacc.y</td>
        <td>此编译器的文法，使用yacc来生成对应的分析表</td>
    </tr>
    <tr> 			
        <td>main.c</td>
        <td>语法分析器与中间代码生成器，它调用词法分析器</td>
    </tr> 
    <tr>
        <td>token_analyze.c</td>
        <td>词法分析器</td>
    </tr>
    <tr>
        <th>相关数据结构</th>
    </tr>
    <tr>     		
        <td>queue.h</td>
        <td>队列</td>
    </tr>
    <tr>
        <td>stack.txt</td>
        <td>栈</td>
    </tr>
    <tr>
        <td>linklist.h</td>
        <td>链表</td>
    </tr>
    <tr>
        <td>data_struct.h</td>
        <td>Token数据结构</td>
    </tr>
    <tr>
        <td>FourElemFormula.h</td>
        <td>四元式相关，如四元式的数据结构、打印（到文件）函数、释放四元式内存行数</td>
    </tr>
    <tr>
        <td>operator.h</td>
        <td>四元式的第一个运算符宏定义</td>
    </tr>
    <tr>
        <td>symboltable.h</td>
        <td>符号表管理</td>
    </tr>
    <tr>
        <td>debug.h</td>
        <td>打印符号表</td>
    </tr>
    <tr>
        <td>table.h</td>
        <td>bison生成的预测分析表</td>
    </tr>
</table>
*详细教程位于 http://www.cnblogs.com/zhouliyan/*


 




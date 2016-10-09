%{
/*
* grammar.y
*
* Pascal grammar in Yacc format, based originally on BNF given
* in "Standard Pascal -- User Reference Manual", by Doug Cooper.
* This in turn is the BNF given by the ANSI and ISO Pascal standards,
* and so, is PUBLIC DOMAIN. The grammar is for ISO Level 0 Pascal.
* The grammar has been massaged somewhat to make it LALR, and added
* the following extensions.
*
* constant expressions
* otherwise statement in a case
* productions to correctly match else's with if's
* beginnings of a separate compilation facility
*/

%}

%token AND ARRAY ASSIGNMENT CASE CHARACTER_STRING COLON COMMA CONST DIGSEQ
%token DIV DO DOT DOTDOT DOWNTO ELSE END EQUAL EXTERNAL FOR FORWARD FUNCTION
%token GE GOTO GT IDENTIFIER IF IN LABEL LBRAC LE LPAREN LT MINUS MOD NIL NOT
%token NOTEQUAL OF OR OTHERWISE PACKED PBEGIN PFILE PLUS PROCEDURE PROGRAM RBRAC
%token REALNUMBER RECORD REPEAT RPAREN SEMICOLON SET SLASH STAR STARSTAR THEN
%token TO TYPE UNTIL UPARROW VAR WHILE WITH

%%
file : program
;

program : program_heading semicolon muldec_m1 block DOT
;

muldec_m1 : 
;

program_heading : PROGRAM identifier
;

identifier_list : identifier_list comma identifier
| identifier
;

block : variable_declaration_part
procedure_and_function_declaration_part
statement_part
;

constant : non_string
| sign non_string
;

sign : PLUS
| MINUS
;

non_string : DIGSEQ
;

type_denoter : identifier
| new_type
;

new_type : new_structured_type
;

new_ordinal_type : subrange_type
;

subrange_type : constant DOTDOT constant
;

new_structured_type : structured_type
;

structured_type : array_type
;

array_type : ARRAY LBRAC index_list RBRAC OF component_type
;

index_list : index_list comma index_type
| index_type
;

index_type : ordinal_type ;

ordinal_type : new_ordinal_type
;

component_type : type_denoter ;

variable_declaration_part : VAR variable_declaration_list semicolon
|
;

variable_declaration_list :
   variable_declaration_list semicolon variable_declaration
| variable_declaration
;

variable_declaration : identifier_list COLON type_denoter
;

procedure_and_function_declaration_part :
  proc_or_func_declaration_list semicolon
|
;

proc_or_func_declaration_list :
   proc_or_func_declaration_list semicolon proc_or_func_declaration
| proc_or_func_declaration
;

proc_or_func_declaration : procedure_declaration
;

procedure_declaration : procedure_heading semicolon muldec_m2 procedure_block
;

muldec_m2 :
;

procedure_heading : procedure_identification
| procedure_identification formal_parameter_list
;

formal_parameter_list : LPAREN formal_parameter_section_list RPAREN ;

formal_parameter_section_list : formal_parameter_section_list semicolon formal_parameter_section
| formal_parameter_section
;

formal_parameter_section : value_parameter_specification
| variable_parameter_specification
;

value_parameter_specification : identifier_list COLON identifier
;

variable_parameter_specification : VAR identifier_list COLON identifier
;

procedure_identification : PROCEDURE identifier ;

procedure_block : block ;

statement_part : compound_statement ;

compound_statement : PBEGIN statement_sequence END ;

statement_sequence : statement_sequence semicolon ctrl_m statement
| statement
;

statement : open_statement
| closed_statement
;

open_statement : non_labeled_open_statement
;

closed_statement : non_labeled_closed_statement
;

non_labeled_closed_statement : assignment_statement
| procedure_statement
| compound_statement
| repeat_statement
| closed_if_statement
| closed_while_statement
| closed_for_statement
|
;

non_labeled_open_statement : open_if_statement
| open_while_statement
| open_for_statement
;

repeat_statement : REPEAT ctrl_m statement_sequence UNTIL repeat_n boolean_expression
;

open_while_statement : WHILE ctrl_m boolean_expression DO ctrl_m open_statement
;

closed_while_statement : WHILE ctrl_m boolean_expression DO ctrl_m closed_statement
;

open_for_statement : FOR control_variable ASSIGNMENT initial_value direction
   final_value DO for_m open_statement
;

closed_for_statement : FOR control_variable ASSIGNMENT initial_value direction
   final_value DO for_m closed_statement
;

open_if_statement : IF boolean_expression THEN ctrl_m statement
| IF boolean_expression THEN ctrl_m closed_statement ctrl_n ELSE ctrl_m open_statement
;

closed_if_statement : IF boolean_expression THEN ctrl_m closed_statement ctrl_n
   ELSE ctrl_m closed_statement
;

assignment_statement : variable_access ASSIGNMENT expression
;

variable_access : identifier
| indexed_variable
;

indexed_variable :  index_expression_list RBRAC
;

index_expression_list : index_expression_list comma index_expression
| identifier LBRAC index_expression
;

index_expression : expression ;

procedure_statement : identifier params
| identifier
;

params : LPAREN actual_parameter_list RPAREN ;

actual_parameter_list : actual_parameter_list comma actual_parameter
| actual_parameter
;

/*
* this forces you to check all this to be sure that only write and
* writeln use the 2nd and 3rd forms, you really can't do it easily in
* the grammar, especially since write and writeln aren't reserved
*/
actual_parameter : expression
;

control_variable : identifier ;

initial_value : expression ;

direction : TO
| DOWNTO
;

final_value : expression ;

boolean_expression : expression ;

expression : simple_expression
| simple_expression relop simple_expression
;

simple_expression : term
| simple_expression addop boolean_m term
;

term : factor
| term mulop boolean_m factor
;

factor : sign factor
| exponentiation
;

exponentiation : primary
;

primary : variable_access
| unsigned_constant
| LPAREN expression RPAREN
| NOT primary
;

unsigned_constant : unsigned_number
| CHARACTER_STRING
;

unsigned_number : unsigned_integer | unsigned_real ;

unsigned_integer : DIGSEQ
;

unsigned_real : REALNUMBER
;

addop: PLUS
| MINUS
| OR
;

mulop : STAR
| SLASH
| DIV
| MOD
| AND
;

relop : EQUAL
| NOTEQUAL
| LT
| GT
| LE
| GE
;

identifier : IDENTIFIER
;

semicolon : SEMICOLON
;

comma : COMMA
;

boolean_m : 
;

ctrl_m:
;

ctrl_n:
;

repeat_n:
;

for_m:
;

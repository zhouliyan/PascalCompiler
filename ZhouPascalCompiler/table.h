#define TN 67      /*终结符数,不含accept!!!*/
#define LCHECK 204 /*make check表长度*/

typedef unsigned char yytype_uint8;
typedef signed char yytype_int8;
typedef unsigned short int yytype_uint16;
typedef short int yytype_int16;

static const yytype_uint8 yytranslate[] =               /*token[0]=0!!!!必须的*/
{
    0,3,4,44,6,10,12,13,16,17,18,
    45,21,23,25,28,29,30,36,37,38,
    40,41,43,47,48,51,52,55,59,60,
    61,62,64,65,66,27,11,50,7,46,
    35,57,56,19,34,26,32,24,39,33,
    53,9,42,14,15,8,5,54,63,58,
    31,49,22,20
};/*种别码和符号数的对应关系*/

static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AND", "ARRAY", "ASSIGNMENT", "CASE",
  "CHARACTER_STRING", "COLON", "COMMA", "CONST", "DIGSEQ", "DIV", "DO",
  "DOT", "DOTDOT", "DOWNTO", "ELSE", "END", "EQUAL", "EXTERNAL", "FOR",
  "FORWARD", "FUNCTION", "GE", "GOTO", "GT", "IDENTIFIER", "IF", "IN",
  "LABEL", "LBRAC", "LE", "LPAREN", "LT", "MINUS", "MOD", "NIL", "NOT",
  "NOTEQUAL", "OF", "OR", "OTHERWISE", "PACKED", "PBEGIN", "PFILE", "PLUS",
  "PROCEDURE", "PROGRAM", "RBRAC", "REALNUMBER", "RECORD", "REPEAT",
  "RPAREN", "SEMICOLON", "SET", "SLASH", "STAR", "STARSTAR", "THEN", "TO",
  "TYPE", "UNTIL", "UPARROW", "VAR", "WHILE", "WITH", "$accept", "file",
  "program", "muldec_m1", "program_heading", "identifier_list", "block",
  "constant", "sign", "non_string", "type_denoter", "new_type",
  "new_ordinal_type", "subrange_type", "new_structured_type",
  "structured_type", "array_type", "index_list", "index_type",
  "ordinal_type", "component_type", "variable_declaration_part",
  "variable_declaration_list", "variable_declaration",
  "procedure_and_function_declaration_part",
  "proc_or_func_declaration_list", "proc_or_func_declaration",
  "procedure_declaration", "muldec_m2", "procedure_heading",
  "formal_parameter_list", "formal_parameter_section_list",
  "formal_parameter_section", "value_parameter_specification",
  "variable_parameter_specification", "procedure_identification",
  "procedure_block", "statement_part", "compound_statement",
  "statement_sequence", "statement", "open_statement", "closed_statement",
  "non_labeled_closed_statement", "non_labeled_open_statement",
  "repeat_statement", "open_while_statement", "closed_while_statement",
  "open_for_statement", "closed_for_statement", "open_if_statement",
  "closed_if_statement", "assignment_statement", "variable_access",
  "indexed_variable", "index_expression_list", "index_expression",
  "procedure_statement", "params", "actual_parameter_list",
  "actual_parameter", "control_variable", "initial_value", "direction",
  "final_value", "boolean_expression", "expression", "simple_expression",
  "term", "factor", "exponentiation", "primary", "unsigned_constant",
  "unsigned_number", "unsigned_integer", "unsigned_real", "addop", "mulop",
  "relop", "identifier", "semicolon", "comma", "boolean_m", "ctrl_m",
  "ctrl_n", "repeat_n", "for_m", 0
};

static const yytype_uint8 yyr1[] =
{
       0,    67,    68,    69,    70,    71,    72,    72,    73,    74,
      74,    75,    75,    76,    77,    77,    78,    79,    80,    81,
      82,    83,    84,    84,    85,    86,    87,    88,    88,    89,
      89,    90,    91,    91,    92,    92,    93,    94,    95,    96,
      96,    97,    98,    98,    99,    99,   100,   101,   102,   103,
     104,   105,   106,   106,   107,   107,   108,   109,   110,   110,
     110,   110,   110,   110,   110,   110,   111,   111,   111,   112,
     113,   114,   115,   116,   117,   117,   118,   119,   120,   120,
     121,   122,   122,   123,   124,   124,   125,   126,   126,   127,
     128,   129,   130,   130,   131,   132,   133,   133,   134,   134,
     135,   135,   136,   136,   137,   138,   138,   138,   138,   139,
     139,   140,   140,   141,   142,   143,   143,   143,   144,   144,
     144,   144,   144,   145,   145,   145,   145,   145,   145,   146,
     147,   148,   149,   150,   151,   152,   153
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     5,     0,     2,     3,     1,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     6,     3,     1,     1,     1,     1,     3,     0,     3,
       1,     3,     2,     0,     3,     1,     1,     4,     0,     1,
       2,     3,     3,     1,     1,     1,     3,     4,     2,     1,
       1,     3,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     1,     1,     1,     6,
       6,     6,     9,     9,     5,     9,     9,     3,     1,     1,
       2,     3,     3,     1,     2,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     4,
       1,     4,     2,     1,     1,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     0,     0,     0,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,   129,     5,     1,   130,     4,
      28,     0,     0,    33,     0,     0,    30,     7,     3,     0,
       0,     0,    35,    36,     0,    39,     0,   131,     0,    27,
      48,    65,     8,    50,    32,    38,     0,    40,     0,    31,
      15,    16,    19,    20,    14,     6,    29,     0,     0,   133,
     133,    60,     0,    53,    54,    55,    57,    56,    61,    67,
      63,    68,    64,    66,    62,    58,     0,    79,     0,    59,
      85,    34,    28,     0,     0,     0,    43,    44,    45,     0,
       0,    90,   110,   113,     0,    12,     0,    11,   114,     0,
     105,     0,    95,    96,    98,   100,   103,   104,   106,   109,
     111,   112,    78,    65,     0,    51,   133,     0,    80,     0,
       0,     0,    84,    49,    37,     0,     0,    41,     0,    13,
       0,     0,     9,    25,    17,     0,    23,    24,     0,     0,
     108,   102,   133,   123,   128,   126,   127,   125,   116,   124,
     117,   115,   132,     0,   122,   120,   121,   119,   118,   132,
       0,     0,    65,    77,    81,    83,    82,     0,    88,    89,
       0,    46,    42,     0,    10,     0,     0,     0,    91,   107,
      65,     0,    97,     0,   135,   133,    52,    86,     0,    47,
      18,     0,    22,    93,    92,     0,    74,    55,    99,   101,
       0,    65,    87,    26,    21,     0,    94,     0,    69,    70,
      71,   136,   133,    65,    65,    72,    73,    75,    76
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    10,     4,    14,    12,   120,    89,   122,
      39,    40,   123,   124,    41,    42,    43,   125,   126,   127,
     194,    13,    15,    16,    20,    21,    22,    23,    72,    24,
      37,    75,    76,    77,    78,    25,   114,    32,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    90,    67,    68,   154,    69,   112,   157,
     158,    80,   167,   185,   195,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   142,   149,   143,   102,
     106,    28,   171,   103,   197,   190,   203
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -123
static const yytype_int16 yypact[] =
{
     -31,    -3,    26,  -123,   -18,  -123,  -123,  -123,  -123,  -123,
     -26,    -3,    33,     4,    13,   -18,  -123,  -123,  -123,    -3,
      27,   -18,  -123,  -123,   -18,    41,    12,  -123,    -3,    -3,
    -123,    34,  -123,  -123,     4,  -123,   -12,  -123,    45,  -123,
    -123,  -123,  -123,  -123,  -123,  -123,  -123,    -3,    68,  -123,
    -123,  -123,    -5,  -123,  -123,  -123,  -123,  -123,  -123,  -123,
    -123,  -123,  -123,  -123,  -123,  -123,    82,  -123,     5,  -123,
      65,  -123,   -26,    -3,   117,    80,  -123,  -123,  -123,    31,
     100,  -123,  -123,  -123,    68,  -123,    30,  -123,  -123,    68,
    -123,    24,  -123,    97,     8,  -123,  -123,  -123,  -123,  -123,
    -123,  -123,    77,    34,    68,  -123,  -123,    68,  -123,    68,
      68,    68,  -123,  -123,  -123,   133,    -3,  -123,   -12,  -123,
      96,   109,  -123,  -123,  -123,    10,  -123,  -123,    68,    75,
    -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,
    -123,  -123,  -123,    68,  -123,  -123,  -123,  -123,  -123,  -123,
      50,   122,    34,  -123,  -123,  -123,  -123,     0,  -123,  -123,
      -3,  -123,  -123,    31,  -123,    90,    31,    -4,  -123,  -123,
      34,    68,    78,    68,  -123,  -123,  -123,  -123,    68,  -123,
    -123,    12,  -123,  -123,  -123,    68,  -123,   120,     8,  -123,
      68,    34,  -123,  -123,  -123,   126,  -123,   127,  -123,  -123,
    -123,  -123,  -123,    34,    34,  -123,  -123,  -123,  -123
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -123,  -123,  -123,  -123,  -123,   -28,    73,   -17,   -75,    28,
     -34,  -123,  -123,  -123,  -123,  -123,  -123,  -123,   -16,  -123,
    -123,  -123,  -123,   119,  -123,  -123,   118,  -123,  -123,  -123,
    -123,  -123,    35,  -123,  -123,  -123,  -123,  -123,   135,    53,
     -85,   -94,  -122,  -123,  -123,  -123,  -123,  -123,  -123,  -123,
    -123,  -123,  -123,   -30,  -123,  -123,    47,  -123,  -123,  -123,
     -20,  -123,  -123,  -123,  -123,   -97,   -78,    17,    -9,   -84,
    -123,    79,  -123,  -123,  -123,  -123,  -123,  -123,  -123,    -1,
      19,   -65,    14,   -48,  -123,  -123,  -123
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -135
static const yytype_int16 yytable[] =
{
       6,    66,   104,   109,   121,   131,   129,   151,    74,    27,
      17,   144,   183,   105,    27,     5,    38,     1,    30,    27,
     145,    26,    27,     9,     5,    44,     7,    45,    17,   153,
      70,   155,   155,   159,    29,    17,     8,    82,    11,     5,
      34,    83,   119,    35,   146,   115,    81,    18,   187,     8,
     168,    19,    73,   177,   108,    47,   184,     5,   152,   165,
     166,     5,    48,    84,   147,   148,    85,   176,    86,   200,
     -78,    31,    17,    66,    36,    82,    79,    87,    31,    83,
      88,   206,   208,   132,   170,   186,    49,   107,   121,   189,
      74,   121,   178,   198,   118,     5,   110,   199,   111,    50,
     159,    84,    70,    85,     8,   128,    86,   196,   110,   205,
     207,   163,   174,   138,    87,   161,   133,    17,    88,   140,
     119,   134,    66,   135,   141,   116,    27,   191,   169,   136,
     181,   137,   138,   117,     8,   175,   139,  -134,   140,   201,
      66,   160,    27,   141,   202,   113,   180,   193,    46,   164,
     182,    70,    71,   162,   204,    33,   150,   156,   192,   179,
     172,    66,   188,   173,     0,   130,     0,     0,     0,    70,
       0,     0,     0,    66,    66,     0,     0,     0,     0,     0,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      70,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70,    70
};

static const yytype_int16 yycheck[] =
{
       1,    31,    50,    68,    79,    89,    84,   104,    36,     9,
      11,     3,    16,    18,     9,    27,     4,    48,    19,     9,
      12,     8,     9,     4,    27,    26,     0,    28,    29,   107,
      31,   109,   110,   111,    15,    36,    54,     7,    64,    27,
      21,    11,    11,    24,    36,    73,    47,    14,   170,    54,
     128,    47,    64,    53,    49,    21,    60,    27,   106,    49,
     125,    27,    28,    33,    56,    57,    35,   152,    38,   191,
       5,    44,    73,   103,    33,     7,    31,    46,    44,    11,
      50,   203,   204,    59,   132,   170,    52,     5,   163,   173,
     118,   166,   157,   190,    75,    27,    31,   191,    33,    65,
     178,    33,   103,    35,    54,     5,    38,   185,    31,   203,
     204,    15,    62,    35,    46,   116,    19,   118,    50,    41,
      11,    24,   152,    26,    46,     8,     9,   175,    53,    32,
      40,    34,    35,    53,    54,    13,    39,    17,    41,    13,
     170,     8,     9,    46,    17,    72,   163,   181,    29,   121,
     166,   152,    34,   118,   202,    20,   103,   110,   178,   160,
     143,   191,   171,   149,    -1,    86,    -1,    -1,    -1,   170,
      -1,    -1,    -1,   203,   204,    -1,    -1,    -1,    -1,    -1,
     181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   203,   204
};

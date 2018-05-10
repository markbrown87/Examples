%{

  open AST
  open Exp

%}

%token <int32> INTCONST
%token <float> FLOATCONST
%token <bool> BOOLCONST
%token <string> ID

%token DEF LET WHILE IF THEN ELSE REF INT FLOAT BOOL UNIT TT IN

%token NOT DEREF
%token PLUS MINUS TIMES DIV
%token AND OR LT INT_EQ DEFEQ

%token LPAREN RPAREN LBRACE RBRACE SEMI EQ COLON COMMA EOF 

%right SEMI
%nonassoc DEFEQ 
%nonassoc REF
%left OR AND
%nonassoc LT INT_EQ
%left PLUS MINUS
%left TIMES DIV
%nonassoc NOT DEREF              

%start <(AST.ty, unit Exp.exp) AST.prog> prog

%%

mytype:
| LPAREN ty = mytype RPAREN { ty }
| INTCONST 	{TyInt}
| FLOATCONST {TyFloat}
| BOOLCONST	{TyBool}
| REF ty = mytype	{TyRef ty}
| UNIT	{TyUnit}
  
unop:
| MINUS
  { UMinus }
| NOT
  { UNot }
| DEREF
  { UDeref }

%inline binop:
| PLUS	{ BPlus }
| MINUS {BMinus}
| TIMES {BTimes}
| DIV 	{BDiv}
| AND	{BAnd}
| OR	{BOr}
| LT	{BLt}
| INT_EQ	{BIntEq}
| DEFEQ	{BUpdate}

id:
| i = ID
  { Id i }

exp_list:
| l = separated_list(COMMA, exp)
  { l }
  
exp_semi_list:
| l = separated_list(SEMI, exp)
  { l }
  
exp: 
| e = raw_exp
    { {start_of = $startpos;
        end_of = $endpos;
        exp_of = e;
        ety_of = ()} }
| LPAREN e = exp RPAREN 
  { e } 
  
raw_exp: 
| LBRACE e = exp RBRACE {EScope e}
| n = INTCONST { EInt n }
| n = FLOATCONST {EFloat n}
| n = id {EId n}
| e1 = exp SEMI e2 = exp_semi_list {ESeq (e1::e2)} (*THIS IS MOST LIKELY WRONG*)
| n = id LPAREN el = exp_list RPAREN {ECall (n, el)}
| REF e = exp {ERef e}
| n = unop e = exp {EUnop (n, e)}
| e1 = exp n = binop e2 = exp {EBinop (n, e1, e2)}
| IF e1 = exp THEN e2 = exp ELSE e3 = exp {EIf (e1, e2, e3)}
| WHILE e1 = exp e2 = exp {EWhile (e1, e2)}
| LET n = id EQ e1 = exp IN e2 = exp {ELet (n, e1, e2)}
| TT {EUnit} 
| n = BOOLCONST {if n = true then ETrue else EFalse}
 
arg:
| arg = id COLON arg_ty = mytype
  { mk_tid arg arg_ty }			    
  
arg_list:
| l = separated_list(COMMA, arg)
  { l }		    
  
fundef:
| DEF nm = id LPAREN args = arg_list RPAREN COLON ret_ty = mytype LBRACE body = exp RBRACE
  { {nm; args; ret_ty; body} }
  
beginfn:
| {[]}
| n = fundef c = beginfn {n::c}

prog: 
| fn = beginfn e = exp EOF
  { {fundefs = fn;
     result = e}
   }


	


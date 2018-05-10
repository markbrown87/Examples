{
  open Lexing
  open Parser
  open Printf

  exception Eof
  exception Syntax_err of string
	    
  let next_line lexbuf =
    let pos = lexbuf.lex_curr_p in
    lexbuf.lex_curr_p <-
      { pos with pos_bol = pos.pos_cnum;
                 pos_lnum = pos.pos_lnum + 1;
      }

  let keyword_table = Hashtbl.create 42
  let _ =
    List.iter (fun (kwd, tok) -> Hashtbl.add keyword_table kwd tok)
              [ "def", DEF;
		"let", LET;
		"while", WHILE;
		"if", IF;
		"then", THEN;
		"else", ELSE;
		"ref", REF;
		"int", INT;
		"float", FLOAT;
		"bool", BOOL;
		"true", BOOLCONST(true);
		"false", BOOLCONST(false);
		"unit", UNIT;
		"tt", TT;
		"not", NOT;
		"in", IN ]

}

let newline = '\r' | '\n' | "\r\n"
  
rule token = parse
    "//"                        		{ comment lexbuf }
  | newline                     		{ next_line lexbuf; token lexbuf }
  | ['0'-'9']+ as lxm           		{ INTCONST(Int32.of_string lxm) }
  | ['0'-'9']+ '.' ['0'-'9']* as lxm	{ FLOATCONST(float_of_string lxm) }
  |	"let"	{LET}
  | "while" {WHILE}
  | "if" 	{IF}
  | "then" 	{THEN}
  | "else" 	{ELSE}
  | "ref" 	{REF}
  | "int"	{INT}
  | "float" {FLOAT}
  | "bool" 	{BOOL}
  | "true" 	{BOOLCONST(true)}
  | "false" {BOOLCONST(false)}
  | "unit" 	{UNIT}
  | "tt" 	{TT}
  | "not" 	{NOT}
  | "in" 	{IN}
  | ['a'-'z' 'A'-'Z']+ ['_' 'a'-'z' 'A'-'Z' '0'-'9']* as lxm	{ ID lxm }
  | "!" 	{DEREF}
  | "+"		{PLUS}
  | "-"		{MINUS}
  | "/"		{DIV}  
  |	"*"		{TIMES}
  | "&&"	{AND}
  |	"||"  	{OR}
  | "<"		{LT}
  | "=="	{INT_EQ}
  |	":="	{DEFEQ}  
  | "(" 	{LPAREN}
  | ")"		{RPAREN}
  | "{"		{LBRACE}
  |	"}" 	{RBRACE}
  |	";"		{SEMI}
  |	"=" 	{EQ}
  | ":"		{COLON}
  | ","		{COMMA}
  | eof		{EOF}
  | " "+	{token lexbuf}			
  | "\t"	{token lexbuf}
  | "(*"	{nested_comment 1 lexbuf}
  | _       { raise (Syntax_err ("Unexpected char: " ^ Lexing.lexeme lexbuf)) }

and comment = parse
    newline    { next_line lexbuf; token lexbuf }
  | eof        { EOF }
  | _          { comment lexbuf }

and nested_comment level = parse
  | "*)"			{if level = 1 then token lexbuf else nested_comment (level-1) lexbuf}		 		  
  | "(*"			{nested_comment (level+1) lexbuf}
  | _          		{ nested_comment level lexbuf }
  


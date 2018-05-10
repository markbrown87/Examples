open Batteries
open BatFormat
open BatOptParse

open Lexing
open AST
open Exp       
open Tycheck
			    
let print_pos outchan lexbuf =
  let pos = lexbuf.lex_curr_p in
  fprintf outchan "%s:%d:%d" pos.pos_fname 
	  pos.pos_lnum (pos.pos_cnum - pos.pos_bol + 1)  
		    
let parse_with_err lexbuf =
  try Parser.prog Lexer.token lexbuf with
  | Parser.Error -> 
    eprintf "%a: syntax error\n" print_pos lexbuf;
    exit (-1)
      
  | Lexer.Syntax_err msg -> 
    eprintf "%a: %s\n" print_pos lexbuf msg;
    exit (-1)

let () =
  let opt_parser = OptParser.make () in
  let infile_opt = StdOpt.str_option ~metavar:"filename" () in
  let dump_tycheck_opt = StdOpt.store_false () in
  let dump_rtl_opt = StdOpt.store_false () in
  OptParser.add opt_parser ~short_name:'i' ~long_name:"infile" infile_opt;  
  OptParser.add opt_parser ~long_name:"dump-tycheck" dump_tycheck_opt;
  OptParser.add opt_parser ~long_name:"dump-rtl" dump_rtl_opt;  
  let _ = OptParser.parse_argv opt_parser in
  try
    let infile =
      try Opt.get infile_opt
      with Opt.No_value ->
	   OptParser.usage opt_parser ();
	   exit (-1)
    in
    let tycheckfile = infile ^ ".tychecked" in
    let inbuf  = open_in infile in
    let lexbuf = Lexing.from_channel inbuf in
    lexbuf.lex_curr_p <- { lexbuf.lex_curr_p with pos_fname = infile };
    let p = parse_with_err lexbuf in
    let p_tychecked =
      try tycheck_prog p 
      with Ty_error err ->
	eprintf "Type error: %s\n" err;
	exit (-1)
    in
    
    (* conditionally dump tychecked *)
    if Opt.is_set dump_tycheck_opt
    then let tycheckbuf = open_out tycheckfile in
	 let tycheckbuf_ppf = formatter_of_out_channel tycheckbuf in
	 pp_prog tycheckbuf_ppf pp_texp pp_ty pp_nl p_tychecked
    else ();
  with
  | Sys_error err -> eprintf "System error: %s\n" err
  | Failure err -> eprintf "Error: %s\n" err
  | Internal_error err -> eprintf "Internal error: %s\n" err

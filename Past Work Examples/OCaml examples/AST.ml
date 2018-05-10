open Batteries
open BatFormat       

exception Internal_error of string

type id =
| Id of string

type label = 
| Label of id

type 'a tid = 
  { id_of : id;
    ty_of : 'a }

let mk_tid (i : id) (t : 'a) : 'a tid =
  { id_of = i;
    ty_of = t }

type ty =
| TyInt
| TyFloat
| TyBool
| TyRef of ty
| TyUnit

let is_arith_ty (t : ty) = 
  match t with
  | TyInt -> true
  | TyFloat -> true
  | _ -> false

type unop =
| UMinus
| UNot
| UDeref

type binop =
| BPlus
| BMinus
| BTimes
| BDiv
| BAnd
| BOr
| BLt
| BIntEq
| BUpdate
					   
type ('ty,'exp) fundef = 
  { nm  : id;
    args : ('ty tid) list;      
    ret_ty : 'ty;
    body : 'exp;
  }

type ('ty,'exp) prog =
  { fundefs : (('ty,'exp) fundef) list;
    result  : 'exp;
  }

let pp_id ppf (i : id) : unit =
  match i with
  | Id s -> fprintf ppf "%s" s

let pp_label ppf (l : label) : unit =
  match l with
  | Label x -> pp_id ppf x

let pp_int ppf (i : int) : unit =
  fprintf ppf "%d" i

let pp_float ppf (f : float) : unit =
  fprintf ppf "%f" f

let rec pp_ty ppf (t : ty) : unit =
  match t with
  | TyInt -> fprintf ppf "int"
  | TyFloat -> fprintf ppf "float"
  | TyBool -> fprintf ppf "bool"
  | TyRef t2 -> fprintf ppf "%a@ ref" pp_ty t2
  | TyUnit -> fprintf ppf "unit"
		 
let pp_tid ppf (i : 'a tid) : unit = 
  fprintf ppf "%a" pp_id i.id_of

let pp_unop ppf (u : unop) : unit = 
  match u with
  | UMinus -> fprintf ppf "-"
  | UNot -> fprintf ppf "not"
  | UDeref -> fprintf ppf "!"

let pp_binop ppf (b : binop) : unit =
  match b with
  | BPlus -> fprintf ppf "+"
  | BMinus -> fprintf ppf "-"
  | BTimes -> fprintf ppf "*"
  | BDiv -> fprintf ppf "/"
  | BAnd -> fprintf ppf "&&"
  | BOr -> fprintf ppf "||"
  | BLt -> fprintf ppf "<"
  | BIntEq -> fprintf ppf "=="
  | BUpdate -> fprintf ppf ":="

let rec pp_list ppf pp sep l : unit =
  match l with
  | [] -> ()
  | x :: [] -> fprintf ppf "%a" pp x
  | x :: l' ->
     fprintf ppf "%a%a" pp x sep ();
     pp_list ppf pp sep l'

let pp_string ppf s : unit -> unit =
  fun _ -> fprintf ppf s

let pp_comma ppf = pp_string ppf ", "
			     
let pp_semi ppf = pp_string ppf "; "
			    
let pp_nl ppf = pp_string ppf "@\n"			    
	  
let pp_fundef ppf pp ppty f : unit =
  fprintf ppf "@[<1>def %a(%a)@ :@ %a {@\n@[%a@]@]@\n}@,"
	  pp_id f.nm
	  (fun ppf0 ->
	   pp_list ppf0 (fun ppf1 x ->
			 fprintf ppf1 "%a : %a" pp_id x.id_of ppty x.ty_of) pp_comma) f.args
	  ppty f.ret_ty
	  pp f.body

let pp_prog ppf pp ppty sep p =
  fprintf ppf "@[<0>%a%a@[%a@]@]@\n@."
	  (fun ppf0 -> BatList.iter (pp_fundef ppf0 pp ppty)) p.fundefs
	  sep ()
	  pp p.result

let pp_to_string pp : string =
  pp str_formatter;
  flush_str_formatter ()

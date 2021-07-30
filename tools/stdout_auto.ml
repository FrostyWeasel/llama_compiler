(* The standard prelude implemented in OCaml *)

let unSome o =
  match o with
  | Some x -> x
  | None   -> raise (Failure "uninitialized variable")

let incr x = x := Some (unSome !x + 1)

let decr x = x := Some (unSome !x - 1)

let fabs x = abs_float x

let round x =
  if x > 0.0 then
    int_of_float (floor (x +. 0.5))
  else
    int_of_float (ceil (x -. 0.5))

let strlen s =
  let rec loop i =
     if unSome !((snd s).(i)) = '\000' then
       i
     else
       loop (i+1) in
  loop 0

let strcmp s1 s2 =
  let rec loop i =
    let c1 = unSome !((snd s1).(i)) in
    let c2 = unSome !((snd s2).(i)) in
    if c1 > c2 then
      1
    else if c1 < c2 then
      -1
    else if c1 = '\000' then
      0
    else
      loop (i+1) in
  loop 0

let strcpy s1 s2 =
  let len1 = List.hd (fst s1) in
  let len2 = strlen s2 in
  if len1 <= len2 then
    raise (Failure "string length too short")
  else
  begin
    let rec loop i =
      let c = unSome !((snd s2).(i)) in
      (snd s1).(i) := Some c;
      if c <> '\000' then
        loop (i+1) in
    loop 0
  end

let print_bool b =
  if b then print_string "true" else print_string "false"

let print_string s =
  let rec loop i =
    let c = unSome !((snd s).(i)) in
    if c <> '\000' then
    begin
       print_char c;
       loop (i+1)
    end in
  loop 0

let llamastr_of_string s =
  let l = String.length s in
  let chr n =
    if n < l then
      ref (Some (s.[n]))
    else if n == l then
      ref (Some '\000')
    else
      ref None in
  [l+1], Array.init (l+1) chr

let read_string s =
  let str  = read_line () in
  let len1 = List.hd (fst s) in
  let len2 = String.length str in
  if len1 <= len2 then
    raise (Failure "string length too short")
  else
  begin
    for i = 0 to len2 - 1 do
      let c = String.get str i in
      (snd s).(i) := Some c
    done;
    (snd s).(len2) := Some '\000'
  end

let read_char () =
  input_char stdin

let strcat s1 s2 = 
  let len1 = strlen s1 in
  let len2 = strlen s2 in
  let len_available = List.hd (fst s1) in
  if len_available <= len1 + len2 then
    raise (Failure "string length too short")
  else
  begin
    let rec loop i =
      let c = unSome !((snd s2).(i)) in
      (snd s1).(len1 + i) := Some c;
      if c <> '\000' then
        loop (i+1) in
    loop 0
  end

let ln x = 
  log x /. log 2.0

let pi () = 3.14159

(* Automatically generated stuff *)

(* The program *)

let rec prime (n : int) : bool = if n < 0 then prime (-n)
  else if n < 2 then false
  else if n = 2 then true
  else if n mod 2 = 0 then false
  else
    let rec loop (i : int) : bool =
      if i <= n / 2 then if n mod i = 0 then false else loop (i + 2)
      else true in
    loop 3

let main : unit =
  print_string (llamastr_of_string "Please, give the upper limit: ");
  let limit : int = read_int () in
  print_string (llamastr_of_string "Prime numbers between 0 and ");
  print_int limit;
  print_string (llamastr_of_string "\n\n");
  let counter : int option ref = ref None in
  counter := Some 0;
  if limit >= 2 then (incr counter;
                      print_string (llamastr_of_string "2\n"));
  if limit >= 3 then (incr counter;
                      print_string (llamastr_of_string "3\n"));
  let rec loop (number : int) : unit =
    if number <= limit then
      (if prime (number - 1) then
         (incr counter;
          print_int (number - 1);
          print_string (llamastr_of_string "\n"));
       if number <> limit && prime (number + 1) then
         (incr counter;
          print_int (number + 1);
          print_string (llamastr_of_string "\n"));
       loop (number + 6)) in
  loop 6;
  print_string (llamastr_of_string "\n");
  print_int (unSome !counter);
  print_string (llamastr_of_string " prime number(s) were found.\n")

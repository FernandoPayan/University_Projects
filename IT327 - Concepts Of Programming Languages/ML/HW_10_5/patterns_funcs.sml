(* 
Authors: Fernando Payan, Sean Kim, John Skluzacek, and Andrew Richmond
Dr. Califf
IT 327 
October 4th, 2022
*)

(* Returns true if e is an element of the list L*)
fun member (e, []) = false (* Base case if list is empty*)
    | member (e, x::list) = 
    if (e = x) then true
    else member(e, list);

fun less (e, []) = nil (* Base case if list is empty. Returns an empty list *)
    | less (e, x::list) =
    if (x < e) then x :: less(e, list) (* If the value in the list is < e, we add it in the list*)
    else less(e, list);

fun repeats ([]) = false (* Base case if list is empty *)
    | repeats ([_]) = false (* If the list has a single element, then it automatically returns false *)
    | repeats(x::y::list) = (* Checks first two elements in a list *)
    if (x = y) then true (* If adjacent values are =, return true *)
    else repeats(y::list);

fun reduce 0 = 0
    | reduce num = reduce(num - 1);

fun getdifference num1 =
    let
      fun subtract num2 = num1 - num2
    in
      subtract
    end;
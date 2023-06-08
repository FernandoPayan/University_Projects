(* prog2.sml is a file composing of a bunch of functions that perform different things
    Written by Fernando Payan and John Skluzacek
    IT 327
    10/27/2022
*)

(* Chapter 7: Exercise 5 - Eval *)
    (* Helper Functions for Eval *)
        (* Gets the length of a list used in eval helper*)
        fun length x =
            if null x then 0
            else 1 + length (tl x);

        (*Computes the power of the base used in eval_helper*)
        fun power (_, 0) = 1.0
        |   power (base, exp) = power(base, exp - 1) * base;

        (* Reverse the list used in eval*)
        fun reverse L =
            if null L then nil
            else reverse(tl L) @ [hd L];

        (*This is the actual eval that is doing the calculations and recursion, computes the polynomial*)
        fun eval_helper ([], _) = 0.0 (*If there is no polynomial passed*)
        |   eval_helper (num_list, x) = (*x represents what our x value will be*)
            ( power(x, (length(tl num_list))) * (hd num_list)) + eval_helper((tl num_list),x) (* Calculates the exponent, multiplies it to the head of the list, and then we add the next resulting value from the recursion *)

    (* Eval Function: Returns the value of the polynomial at the given x *)
    fun eval (num_list,x) = eval_helper(reverse(num_list),x)

(* Chapter 9: Exercise 23 - Convert *)
    (* Convert Function: Returns a pair of lists, preserving the order of the elements *)
    fun convert list = foldl (fn ( (val1, val2), (val3, val4) )=> (val3 @ [val1], val4 @ [val2] ) ) ([],[]) list; (* Takes in the leftmost two tuples from the list, and anonymous function concatenates them. *)

(* Chapter 9: Exercise 25 - Evalm *)
    (* Evalm Function: Returns the value of the polynomial at the given x *)
    fun evalm ([], _) = 0.0 (* base condition *)
    | evalm (list, x) = hd list + x * (evalm (tl list, x)) (* The head of the list adds the result of x times the head of the list. We are able to compute the value of the exponent by using x * evalm *)

(* Union Function *)
    (* Returns a list with a single copy of all elements from both lists *)
    fun union ([], []) = ([]) (* base cases *)
    |   union ([], list_2) = list_2
    |   union (list_1, []) = list_1
    |   union (list_1, list_2) = (*depending on which number is smaller, concatenate it with the list*)
        if (hd list_1) <= (hd list_2) (* If the head of the first list is <= to head of the second list, then we concatenate the head of the first list*)
        then (hd list_1) :: union(tl list_1,list_2)
        else (hd list_2) :: union(list_1,tl list_2) (* Else, we concantenate the head of the second list *)

(* Intersection Function *)
    (* Returns a list with a single copy of elements that appear in both lists *)
    fun intersection ([], []) = ([]) (* base cases *)
    |   intersection (list_1, []) = ([])
    |   intersection ([], list_2) = ([])
    |   intersection (list_1,list_2) = if (list_1 = list_2) then list_1
        else if (hd list_1) = (hd list_2) then (hd list_1) :: intersection(tl list_1, tl list_2) (* If the head of the first list is = to head of the second list, then we concatenate the head of the first list*)
        else if (hd list_1) < (hd list_2) then intersection(tl list_1, list_2) (* If the head of the first list is < head of second list, we move to the tail of the list and do comparision again *)
        else intersection(list_1 , tl list_2) (* If head of first list > head of second list, we move onto the next item in the second list *)

(* Find Subset Function *)
    (* Helper Functions *)
        (* Takes a lists and returns all the possible combinations of that list *)
        fun findcombos ([]) = [[]]
        | findcombos (list) = map (fn newtail => hd list :: newtail) (findcombos (tl list)) @ findcombos (tl list)

        (* Goes through the list of combinations and finds out which set adds up to the sum. *)
        fun findSubsetHelper(sum,[]) : int list = ([])
        |   findSubsetHelper(sum, listOfCombinations) =
            if foldr (op +) 0 (hd listOfCombinations) = sum then (hd listOfCombinations) (* If the sum of the list is = to the passed argument of sum, then we return the list *)
            else findSubsetHelper(sum, (tl listOfCombinations)) (* Else, we move onto the next set *)

    (* findSubset function: Returns a subset of the list that adds up to the first argument. If no such subset can be found, we return an empty list *)
    fun findSubset (sum,list) = findSubsetHelper(sum,findcombos(list)) (* Calls the helper function *)

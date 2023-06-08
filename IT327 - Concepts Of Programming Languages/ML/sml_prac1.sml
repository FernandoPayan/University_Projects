(*Recommended SML extensions: vscode-better-sml v0.0.4 by Di Wang *)
(* To start SML, write: sml FILE_NAME.sml *)
(* to update and restart, type: use "FILE_NAME_.sml"; *)

(* Returns the smallest value from the three inputs*)
fun smallest (num1, num2, num3) =
    if num1 <= num2 then 
        if num1 < num3 then num1 else num3 else 
        if num2 < num3 then num2 else num3
        
(*Returns a tuple of the first and last element in a tuple*)
fun red3 (val1, val2, val3) =
    (val1, val3);

(*Returns an int that is the sum of the squares from 0 to n EX: sqsum 4*)
fun sqsum num =
    if num = 0 then 0 else
    num * num + sqsum(num - 1);

(*Returns an int that is the largest of that list of integers*)
fun rec_max (num_list, cur_max) =
    if null(num_list) then cur_max
    else if hd(num_list) > cur_max then rec_max(tl(num_list), hd(num_list))
    else rec_max(tl(num_list), cur_max);

(* This is where the user will enter their list. We're doing the tail here because we're using the head as our cur_max. When doing output, put NO SPACES between the indexes: EX: max [10,2,5,7];*)
fun max num_list = rec_max(tl(num_list), hd(num_list));

(*Exercise 1: Returns the cube of its parameter*)
fun cube num =
    (num * num * num);

(*Exercise 3: Returns the fourth element in a list*)
fun fourth num_list =
    hd (tl(tl(tl(num_list))));

(*Exercise 7: Moves the head to the end of the list*)
fun cycle1 num_list =
    tl(num_list) @ [hd(num_list)];

(*Exercise 12: Raises a real number to an integer power*)
fun pow (base, power) =
    if power = 0 then 1.0
    else base * pow(base, power - 1);
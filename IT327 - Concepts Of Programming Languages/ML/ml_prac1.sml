(* Authors: Sean Kim, John Skluzacek, Andrew Richmond, Fernando Payan*)

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
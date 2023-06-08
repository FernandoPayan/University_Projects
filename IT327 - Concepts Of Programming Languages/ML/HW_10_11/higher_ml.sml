(* 
Authors: Fernando Payan, Sean Kim, John Skluzacek, and Andrew Richmond
Dr. Califf
IT 327 
October 11th, 2022
*)

(* Returns the multiplication of a pair in a list *)
fun multipairs num_list = map (fn (val1,val2) => val1 * val2) num_list;

(* Returns the count of the number of true values in the list *)
fun truecount bool_list = foldl (fn (element,counter) => if element then counter + 1 else counter) 0 bool_list;

print ("Expected Output: 2 | Resulting output: ");
truecount [true, false, true];
print ("\n");
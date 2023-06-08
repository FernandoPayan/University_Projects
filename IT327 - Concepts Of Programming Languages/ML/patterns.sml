(*The first 3 can be ambigous, but we want the fourth item to be declared as an item.*)
(*Go into whatever list I got (doesn't matter type due to item) and easily get fourth item.*)
(*You will get a warning because if you give it a list of < 4 items, it will not work*)
fun fourth (_::_::_::item::_) =
    item; 
(*Returns the item. Practice with: fourth [5,4,6,7,9,10]; and fourth["a","b","c","d","e"];*)

(*We're returning the base case INSIDE of the function call itself.*)
(*Rather than writing (if n = 0), we can do FUNC_NAME = 0. It does the same thing*)
fun sqsum 0 = 0
|   sqsum num = num*num + sqsum(num - 1); 
(*Putting parenthesis here because it's an expression. If we didn't have num - 1, could've just said sqsum num*)


fun rec_max (nil, current_max) = current_max
    rec_max (head::tail,current_max) =
        if head > current_max then rec_max(tail,head)
                            else rec_max(tail,current_max);
    
fun max (current_max::num_list) = rec_max(num_list,current_max);
(*Practice with: max [5]; max [4,2,9,10,6];*)


fun power (_,0) = 1.0
|   power (base, exp) = power(base, exp-1) * base;
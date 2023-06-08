(*output prog2_test.sml is a file meant to test the functions from prog2.sml
    written by Fernando Payan and John Skluzacek
    IT 327
    10/27/2022*)
use "prog2.sml";

(*eval tests*)
print ("Eval tests \n");

print ("Input is : ([1.0,5.0,3.0], 2.0) | Expected output: 23.0 | Actual Output: ");
eval ([1.0,5.0,3.0], 2.0);
print ("\n");

print ("Input is : ([0.0,~2.0,0.0,1.0], 2.0) | Expected output: 4.0 | Actual Output: ");
eval([0.0,~2.0,0.0,1.0], 2.0);
print ("\n");

print ("Input is : ([], 2.0) | Expected output: 0.0 | Actual Output: ");
eval([], 2.0);
print ("\n");

print ("Input is : ([1.0,5.0,3.0], 0.0) | Expected output: 1.0 | Actual Output: ");
eval([1.0,5.0,3.0], 0.0);
print ("\n");

print ("Input is : ([],0) | Expected output: 0.0 | Actual Output: ");
eval([], 0.0);
print ("\n");


(*convert tests*)
print ("Convert tests \n");
print ("Input is : [(1,2),(3,4),(5,6)] | Expected output: ([1,3,5],[2,4,6]) | Actual Output: ");
convert([(1,2),(3,4),(5,6)]);
print ("\n");

print ("Input is : [(0,0),(1,1)] | Expected output: ([0,1],[0,1]) | Actual Output: " );
convert([(0,0),(1,1)]);
print ("\n");


(* evalm tests*)
print ("Evalm tests \n");

print ("Input is : ([1.0,5.0,3.0],2.0) | Expected output: 23.0 | Actual Output: ");
evalm([1.0,5.0,3.0], 2.0);
print ("\n");

print ("Input is : ([0.0,~2.0,0.0,1.0],2.0) | Expected output: 4.0 | Actual Output: ");
 evalm([0.0,~2.0,0.0,1.0], 2.0);
print ("\n");

print ("Input is : ([],2.0) | Expected output: 0.0 | Actual Output: ");
evalm([], 2.0);
print ("\n");

print ("Input is : ([1.0,5.0,3.0], 0.0) | Expected output: 1.0 | Actual Output: ");
evalm([1.0,5.0,3.0], 0.0);
print ("\n");

print ("Input is : ([], 0.0) | Expected output: 0.0 | Actual Output: " );
evalm([], 0.0);
print ("\n");

print ("Input is : ([1.0, 6.0, 8.0], 5.0) | Expected output: 231.0 | Actual Output: " );
evalm([1.0, 6.0, 8.0], 5.0);
print ("\n");


(* union tests*)
print ("Union tests \n");

print ("Input is : ([1,2,3],[4,5,6]) | Expected output: ([1,2,3,4,5,6]) | Actual Output: ");
union([1,2,3],[4,5,6]);
print ("\n");

print ("Input is : ([],[4,5,6]) | Expected output: ([4,5,6]) | Actual Output: ");
union([],[4,5,6]);
print ("\n");

print ("Input is : ([1,2,3],[]) | Expected output: ([1,2,3]) | Actual Output: ");
union([1,2,3],[]);
print ("\n");

print ("Input is : ([],[]) | Expected output: ([]) | Actual Output: ");
union([],[]);
print ("\n");

print ("Input is : ([10,20,100],[1,2,10,11,23,50,101]) | Expected output: ([1,2,10,10,11,20,23,50,100,101]) | Actual Output: ");
union([10,20,100],[1,2,10,11,23,50,101]);
print ("\n");


(* intersection tests*)
print("Intersection tests \n");

print ("Input is : ([1,2,3,10],[10,4,5,6]) | Expected output: ([10]) | Actual Output: ");
intersection([1,2,3,10],[10,4,5,6]);
print ("\n");

print ("Input is : ([],[4,5,6]) | Expected output: ([]) | Actual Output: ");
intersection([],[4,5,6]);
print ("\n");

print ("Input is : ([1,2,3],[4]) | Expected output: ([]) | Actual Output: ");
intersection([1,2,3],[4]);
print ("\n");

print ("Input is : ([],[]) | Expected output: ([]) | Actual Output: ");
intersection([],[]);
print ("\n");

print ("Input is : ([10,20,100],[1,2,10,11,23,50,101]) | Expected output: ([10]) | Actual Output: ");
intersection([10,20,100],[1,2,10,11,23,50,101]);
print ("\n");

print ("Input is : ([10,20,100],[10,20,100]) | Expected output: ([10,20,100]) | Actual Output: ");
intersection([10,20,100],[10,20,100]);
print ("\n");


(* findSubset tests*)
print ("FindSubset Tests \n");

print ("Input is: (10, [4,3,2,12,5]) | Expected output: [3,2,5] | Actual output: ");
findSubset(10, [4,3,2,12,5]);
print ("\n");

print ("Input is: (10, [4,3,2,12,5,6]) | Expected output: [4,6] | Actual output: ");
findSubset(10, [4,3,2,12,5,6]);
print ("\n");

print ("Input is: (10, [4,3,2,12]) | Expected output: [] | Actual output: ");
findSubset(10, [4,3,2,12]);
print ("\n");

print ("Input is : (10,[]) | Expected output: ([]) | Actual Output: ");
findSubset(10,[]);
print ("\n");
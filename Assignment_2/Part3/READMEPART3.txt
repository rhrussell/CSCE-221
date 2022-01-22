Name: Ryan Russell
UIN: 227006614
Section Number: CSCE 221-511
Username: rhrussell
Email: rhrussell@tamu.edu

I certify that I have listed all the sources that I used to develop the solutions and code to the
submitted work.
On my honor as an Aggie, I have neither given nor received any unauthorized help
on this academic work.
Ryan Russell	3/6/2020

Resources:
None

No known problems

I tested my code for correctness by working on one part of the assignment one at a time
and then testing the method or part of the code to see if I got the expected result. If I
did not get those results I would try to break down the method or that part of the assignment
even further to figure out the problem. I used exceptions for error handling by throwing
obvious cases (i.e getting the min of an empty queue, removing an item that doesn't exist, 
removing an item when the min queue is empty) and if there were other cases that popped up in
the development process then I would incorporate them. Templating definitely was hard to
implement, but I was able to make the transition from the original code to templated 
version pretty easy. 

enqueue(T x) Runtime: O(1)
It is O(1) because there are only two operations done for any queue of size n which results
in O(2) which simplifies to O(1).

T dequeue() Runtime: O(1)
It is O(1) because there are only two operations done for any queue of size n which results
in O(2) which simplifies to O(1).

int size() Runtime: O(1)
It is O(1) because there is only one operation done for any queue of size n which results
in O(1).

bool is_empty() Runtime: O(1)
It is O(1) because there is only one operation done for any queue of size n which results
in O(1).

T min() Runtime: O(n)
It is O(n) because there are 4*n + 4 operations that occur for a queue of size n. One 
operation is getting the first node and another operation is getting the object of that node.
In its worst case, the while loop will execute n + 1 times and the if statement, the assignment
of the new min and the traversing to the next node will execute n times. Finally, the return
statement will execute one time. This results in O(1 + 1 + n + 1 + n + n + n + 1) = O(4*n + 4)
which simplifies down to O(n).

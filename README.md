# B(ored) O(n) A T(rain)

I would like to note that this is not by any means a serious project. It's just something i've wanted to do for a while</br>
and that's why the code is awful in multiple areas.

### Syntaxes ###
``` int a 10``` - int variable declaration</br>
``` string a 10``` - string variable declaration</br>
``` int a 10 20 30 40``` - int array declaration consisting of 4 elements</br>
``` print value``` - Prints value in the terminal, use /variableName if you want to print the value of a variable</br>
``` printnl value ``` - Same as print, but adds a newline after each print</br>
```A + B``` - Addition of two variables A and B</br>
```A - B``` - Subtraction of two variables A and B</br>
```A * B```  - Multiplication of two variables A and B</br>
```A / B``` - Division of two variables A and B</br>
```A // B```- Modular of two variables A and B</br>
```include fileName``` - Imports the code from the file "fileName"</br>
```cits variable```- Converts a variable type from int to string</br>
```def funcName whatTheFuncDoes``` - Creates a function with the name funcName, can be used later one by calling upon it.
</br>
``` % text ``` - This is how you represent a comment </br>
```up A B ``` - Updates variables A values with B's</br>
```up A[0] B ``` - Updates array A's pos 0 values with B's</br>
```up A[0] B[0] ``` - Updates array A's pos 0 values with arrays B pos 0</br>
```up A B[0] ``` - Updates variables A value with array B's value at pos 0</br>
```while i > t doSomething```- Example of a while loop, you can also use <. Var's i and t must be declared beforehand </br>
```if i <= t doSomething``` - Evalutes if i <= t, you can also use <,>= and > </br>
```in A ``` - Takes an input from the user and saves it in the variabel A </br>

### Code example ###
```
include test.txt % includes variable c
% this is a comment
int a 3
int b 6

b / a

print /b % 2
print /a % 3
print /c % 4

int floor 0
int roof 10

while floor < roof print /floor % 0 1 2 3 4 5 6 7 8 9

int array 10 20 30 40 50
print value at location array[2]: /array[2] % value at location array[2]: 30

print hello world % prints "hello world"
print a has the value /a % a has the value 1

def sub a - b % important that a and b both have been declared before!
sub % calls upon the function
print /a % -1

% You can even chainlink commands within a function
def subAdd a - b b + a % This will first subtract b from a and then add a to b
```
### Error example & explanation ###
```
(4) Error: Variable A has already been declared
```
```(4)``` - Index on which row the error occurred on</br>
```Error: Variable A has already been declared``` - The error message

</br>If there is any issue, open up a ticket and I will take a look at it


# B(ored) O(n) A T(rain)

I would like to note that this is not by any means a serious project. It's just something i've wanted to do for a while</br>
and that's why the code is awful in multiple areas.

### Syntaxes ###
``` int, string``` - Variable declaration</br>
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
```upd A B ``` - Updates variables A values with B's </br>

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

b + c
print /b % 6

int d 2
a - d
print /a % 1

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

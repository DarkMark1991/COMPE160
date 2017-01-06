### Lake Search

This project demonstrates several important concepts in c programming: 

	* File I/O.
	* Custom header files.
	* Passing function as an argument.
	* Void pointer variables.
  
Custom header files allow us to split code into multiple files. In this instance I have put the struct Lake and all functions associated with it in a separate header file.

Passing function as an argument allows us to combine several functions with similar functionality in one. In this case search function combines search by name, area, height and depth by receiving the function that actually checks the equality as an argument.

Void pointers allow us to pass different types of pointers into the function. In this case we pass a string and a float into the same variable, depending on what we need.

To demonstrate all this I’ll read lakes (name, area, height/altitude, depth) from a file into an array of structs. And will implement a search function which will take in a function for checking if the lake is found as an argument and will also take the search term as a void pointer (to check both name and numerical attributes).

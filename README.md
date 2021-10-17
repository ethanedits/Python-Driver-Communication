# Python-Driver-Communication
 A python wrapper that communicates to a C++ func hook driver
 
The actual C++ function hook driver is located in the `Driver` folder, and needs to mapped using `kdmapper.exe`.

The Wrapper Library is in the `UsermodeLibrary` folder.

The Python Usermode is located in the `Usermode` folder, with _x86_ and _x64_ examples titled **x86UsermodeExample.py** and **x64UsermodeExample.py**.

(Note: x64 processes/modules must manually be inputted in the Driver) *This is temporary and will be changed soon.*

# Binary Search Tree (BST) <br> implementation in C++

**Trees** are connected, acyclic undirected graphs.   
**Binary Trees** have at most 2 children.   
**Balanced Trees** keep its height (maximal number of levels below the root) small: red-black, AA, 2-3 tree.    

O(n) insert, delete, and faster search (O(log *n*) compared to O(n) for lists)

### Binary Search Tree Uses
- Storing and retrieving information. 
- Take advantage of log *n* height

## Code usage

Compile (needs googletest header files): 

    > make

Run:

    > ./unittest.out

You should see all tests PASSED.  

## Google C++ Testing
Note that I have included the Google Test object file (gtest_main.a) 
so that you do not need to re-build Google's C++ test framework.
The object file is built against version 1.7.     

If you wish to re-build another version, you may download the 
test framework at http://code.google.com/p/googletest/   

Move the gtest folder somewhere permenant, e.g. ~/Documents.   
Create a symlink to the gtest folder where Makefile resides.

    > ln -s ~/Documents/lib/gtest-1.7.0 gtest  

To use it, comment out the .INTERMEDIATE line in the Makefile.
This will build the gtest object file located at GTEST_DIR.
Replace $(GTEST_OBJECT) with $(GTEST_HEADERS)

**This source code is for a School project submission**

 # Project Description
this project use binary search tree to search on list
of song names then returns a info about the song along with
source on where to listen it


## scenario
supposed there was a bunch of song list and you want to find
the info of a song like album, cover, singer, writer, or even
a link on where to listen to it. Now how we will be able to
find a song?? We can use the list way, where we parse the
data then surf on each on them then match if its the data we
need, sure it does the thing while being simple to implement
however we comes to the problem that the speed of the execution
was O(n) where n is the line size and O(n) is very slow,
imagine 1000 lines of song list, we have known algorithm
called **BST(Binary-search Tree)** it was a algorithm used to search
bunch of things really fast, example if we have 1000 line of
data to search with and we use both the first method will give
you average speed of 500 step while using BST is bit more
complex lets say on the line there's 25% that a line would be
a header or the header of the information, on our case it is
the song name, you can only use binary search tree when the
tree exist, on our case if the tree still exist on the
computer's memory, due to that limitation we can take
advantage of the BST's speed if the program is still active
therefore we take this approach, first parse the file to
search for header, store that on a node that can hold basic
information like what line:row the header resides and its
name along with the child nodes, we can store this on a
separate file so that we can just re-read the headers
without requiring to read unnecessary lines, thus making
the search faster, along side that ones we have the
bin-tree file we can just use bin tree to make it very fast.


However there some nuance to this, like what will happen
if there's no data on the file, something went wrong on the
compiling, invalid data type or invalid inputs, we can
solve it by using error handling, where we try to prevent
error to just make the program stops, and give us useful
information about the error and give us diagnostics about
the program, plus we can avoid the program from causing
unwanted memory leaks and core dump error that might cause
problem on the device, in addition to that we can catch
early bugs that probably can cause the program to hang and
never show us whats wrong.


To keep the project from being too complicated and hard to
manage this what we will do instead. First process is done
file by surfing to each line, then if a line ends with a
":" create new node with the name of header (excluding ":")
and where to find the header on the file, then add it to
the tree and choose a correct branch. After that we take
the target header name and do a binary search.

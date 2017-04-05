# introduction
  - [algorithm](http://algs4.cs.princeton.edu/home/)

# sort
  - prior queue
    - heap sort
      - sink
      - swim
      ```
      sink start from  N/2..0   --> Maxtop heap
      for n 0..N-1
       exch(top, botom)
       sink at new top for N-1 length
      end
      ```

# analysis
  - total running time of a program relates to factors:
    - the cost of executing each statement
      - computer
      - os
      - compiler
    - the frequency of execution of each statement
      - property of software
      - input
  - develop a mathematical model of running time reduces the following steps:
    - develop a input model, including a definition of problem size;
    - identify the inner loop;
    - define a cost model that includes operations in the inner loop;
    - determin the frequency of execution of those operations for input

  - basic steps
    - understand the problem

    - try a example

    - focus on algorithm an data structure
      - maybe long and need aditional examples
      - interactivity, talk what you are doing
      - resist the temptation to begin code before think

    - explain solution after you figure out your algorithm and how to implement it
      - get an opportunity to evaluate your solution
    
    - while coding, explain what you are doing

    - ask propriately when neccessary

    - after coding finished, immediately verify with a example
      - demonstrate your code is correct at least one case
      - illustrate a logical thought processing and intention to check your work and search for bugs

    - make sure you check for all ERROR and SPECIAL case, especially conditions boundaries

    - analyzing your solution, volunteer the information:
      - running time
      - alternative implements
      - complexity

    - when get stuck
      - go back to example
      - try different data structure
      - consider less-commonly used or more-advanced aspect of the language


    
      



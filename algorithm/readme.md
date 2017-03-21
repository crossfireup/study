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

    
      



# CS300 Portfolio

Dennis James Stelmach

- Summarize the project and what problem it was solving.
  - This project required a method to load and display a list of courses and their prerequisites using an efficient data structure.
- How did I approach the problem?
  - In requiring a way to store and retrieve the list of courses in an efficient manner, I performed analysis on several data structures: vectors, hash tables, and trees. In doing so, I was torn between selecting a hash table or a tree for my datastructure, as hash tables perform excellently for retrieval and insertion operations, with a time-complexity of O(1), while trees are excellent for providing inherit sorting based on keys and perform very well in retrieval and insertion. I ultimately chose a hash map as I believed the time-complexity savings for use in a large system would be beneficial, especially if caching is used in the task of printing the list of courses in alphanumeric order, since hash maps do not provide inherit sorting on keys.
- How did you overcome any roadblocks you encountered while going throught the activities or project?
  - Reading the input file to load the courses was difficult, as it required the validity of the file to be checked and handled appropriately. This required me to carefully review my logic and test with cases of invalid files to ensure the loading function was loading courses into my data structure correctly and did not when the input file was determined to not be correct.
- How has your work on this project expanded your approach to designing software and developing programs?
  - I enjoyed these activities and projects because they reinforce the need for due-diligence in code planning and execution. By doing prior research into time and space complexity of a particular feature of the project, we can see how this choice will influence the rest of the application.
- How did you make this program maintainable, readable, and adaptable?
  - By using comments in an efficient manner, we can document what a function or a particular section of code does and why it was chosen at a glance instead of having to put our minds in the headspace of the original programmer and not understanding what is happening, even if that original programmer is you.
  - By utilizing structs, classes, and small and reusable functions, we can understand the sectioning and logic of the program much more easily than a single large function with no separation of logic.

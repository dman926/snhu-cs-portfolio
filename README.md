# CS210 Portfolio

- Summarize the project and what problem it was solving.
  - This project required a way to search a list of words by their frequency counts.
- What did you do particularly well?
  - I created the FrequencyCounter class to analyze a list of words and their frequencies in O(n) and retrieve frequency counts in O(1).
  - All code is well-commented.
- Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?
  - Testing can be put in place to ensure that every aspect is working as expected.
- Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?
  - Reading the input file to count word frequencies was the most difficult as variable line endings were causing unexpected errors when displaying due to some line endings not being stripped before being used to set a map key. I resolved this by manually stripping unwanted characters from the map keys before setting them.
- What skills from this project will be particularly transferable to other projects or course work?
  - Creating CLI applications.
  - File I/O.
  - Utilizing efficient data structures.
- How did you make this program maintainable, readable, and adaptable?
  - I added comments where neccessary to explain method functionality and design choices.
  - I followed best styling practices to improve readability.
  - The FrequencyCounter class is generic enough to work in other applications.

## Flyweight Pattern
Avoid redundancy when storing data

- If there are a lot of identical field inputs (e.g. first/last names in an mmo), then instead of storing all their names, you can store a list of names in one table and a list of pointers to names in another table
- Can be applied to bold or italic (or otherwise styled) text in console. You don't want each character in styled text to have a styling tag, you instead want to store ranges for which styles operate!

Formally:
__Flyweight__ : A space optimization technique that lets us use less memory by storing externally the data associate with similar objects.

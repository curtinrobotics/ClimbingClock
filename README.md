![*CRoC Logo Missing*](https://github.com/curtinrobotics/ClimbingClock/blob/doc_update/CRoC_docs/CRoC_Logo_with_Text_Medium_Quality.png "CRoC Logo")

# Climbing Clock Project

Welcome to the Climbing Clock project!

Here is where we store all our code and code backups.

## Getting Started

Please make sure you read the following to get a grasp on the project's code.

More importantly, remember to have fun!

#### Table of Contents

**[Project Details](#project-details)**<br>
**[Progress Made](#progress-made)**<br>
**[Prerequisities](#prerequisities)**<br>
**[Programming Standards](#programming-standards)**<br>


## Project Details

**Organisation:** Curtin Robotics Club (CRoC)<br>
**Institute:** Curtin University (Bentley Campus)<br>
**Location:** Ground floor, building  204, Curtin University<br>
**Time:** Most Thursdays 6pm onwards (see CRoC personel for more details)<br>
**Project Lead:** Harrison G. Outram<br>
**Project Founder:** Ilke Dincer<br>
**Difficulty:** Easy to moderate (depends on exact task)

### Overall Project Goal

To make one or more robots climb in a manner that allows us to tell the time of day.

### Project Requirements

1. Must be able to tell the time of day within 5 minutes from a distance of up to 10 metres
2. Strict budget to stay under (see Project Lead for more details)
3. Robots must move using internal mechanics (E.g. pulley systems are not allowed)
4. Entire system must hang from second floor catwalk in Engineering Pavilion (building 204). See project lead for exact location
5. Entire system cannot be more than 2.4 metres tall
6. Entire system cannot be more than 1 metre wide
7. System must be able to run automonously (i.e. without supervision)
8. It has to look cool (subject to interpretation)

## Progress Made

As evident by our latest versions and physical devices, we have made several strides into getting our project on track.

However, there is still much more to be done!

Please see our Kanban board or talk with us to get an idea of where you can fit in.

## Prerequisities

While everyone is welcome to join, CRoC has designed this project to be as first-year friendly as possible.
To promote and upload this standard, no experience nor knowledges are necessary to join!

To get you started, the project lead can update on where exactly the project is at. If the project lead is not available you can contact him/her through the club's Discord or on Facebook. If you need an answer immediately, please refer to the Kanban board, project overview (*pending*), and other Climbing Clock members present.

Whether it be learning CAD software or using an Arduino for the first time, feel free to ask anyone anytime if you need help.

Don't worry if your first week or two seemed slow; even the project leads have spent entire build nights just researching how-to guides.

## Programming Standards

The Climbing Clock project demands a diverse team of programmers to tackle all nuances as they come.

Whether a novice or an advanced user, a standard must be established to keep the project on track. This are, in no particular order,

1. Write code to fit the design documentation

   a. If the design can be improvement, is internally contradictory, or inpractical/impossible to implement, speak with the project lead to change the design

2. All code must be documented internally via document code blocks for public and protected functions and methods (see [Doxygen](http://doxygen.nl/))
3. Whenever it is not obvious within 5 seconds as to what a block of code is supposed to do a comment should be placed
4. All libraries must come with a README.md file, formatted as per [Markdown](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet#code "Markdown Cheat Sheet")
5. Avoid floats, division, trig functions and other computationally expensive operations and functions, unless otherwise no better alternative exist
6. Use bitwise operators whenever applicable for max performance, e.g. use `num = input >> 2` instead of `num = input / 2`
7. All operators and operands should have a single space inbetween

   a. This excludes spaces after an opening round bracket, before a closing round bracket, subscript notation (square brackets), before a semi-colon, and the double colon operator
   
   b. Opening curly brackets should either be on their own line or the end of a line after a space, and closing curly brackets should be on their own line, excluding empty curly brackets (requires a single space inbetween) and curly brackets with a single short statement
   
   c. `temp=a-3/((beta[2]*10.0)-2)+calcGamma(lemma,0);` and `Foo::getColour(){return _colour;};` are unacceptable
   
   d. `temp = a - 3 / ( (beta[2] * 10.0) - 2 ) + calcGamma(lemma, 0);` and `Foo::getColour() { return _colour; }` are acceptable

8. All functions and methods should use as few operators as possible to achieve its task while retaining readability

   a. If a function/methods is too large (> 50 lines) split it into multiple functions/methods

9. All code written should be reviewed by a non-author programmer

If in doubt, ask a fellow Climbing Clock programmer or the project lead

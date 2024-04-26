Programming project
Programação (L.EIC009)

1 Overview
1.1 Summary
1.2 SVG format outline
1.3 References
2 Constraints & logistics
2.1 Deadline
2.2 Group work
2.3 Evaluation criteria
2.4 Plagiarism
3 Code project
3.1 Getting started
3.2 Project files
3.3 Programs
3.3.1 The svgtopng program
3.3.2 The test program
3.3.3 The xmldump program
4 Tasks
4.1 The <svg> root element
4.2 Geometrical elements to consider
4.3 Element transformations
4.4 Groups (<g> elements)
4.5 Element duplication (<use> elements)
1 Overview
1.1 Summary
This project concerns the conversion of images from the SVG vectorial format to the PNG raster format. You will need to define a hierarchy of C++ classes corresponding to SVG elements and code for reading these elements from the SVG format.

A skeleton is provided for development with the structure detailed below in this document, including support already given to read XML files (the format in which SVG is expressed) using the TinyXML2 library, and to write PNG files.

1.2 SVG format outline
SVG is a vectorial image format encoded in XML. The example in Listing 1 (below) illustrates a 200 x 200 image containing several <circle> elements.

You can write a SVG file with these contents (use the .svg file extension) and view it using the Firefox or Chrome web browsers for instance. It should look as illustrated by the PNG file shown in Figure 1 (below).

<svg width="200" height="200" xmlns="http://www.w3.org/2000/svg">
    <circle cx="100" cy="100" r="95" fill="red"/>
    <circle cx="100" cy="100" r="80" fill="#A00000"/>
    <circle cx="50" cy="50" r="25" fill="white"/>
    <circle cx="50" cy="50" r="10" fill="black"/>
    <circle cx="150" cy="50" r="25" fill="white"/>
    <circle cx="150" cy="50" r="10" fill="black"/>
    <circle cx="100" cy="150" r="40" fill="white"/>
    <circle cx="100" cy="150" r="30" fill="black"/>
</svg>
Listing 1. Example SVG file.

Figure 1. Visualization of SVG file from Listing 1.
Figure 1. Visualization of SVG file from Listing 1.
1.3 References
SVG
Reference (mozilla.org)
W3 Schools tutorial
W3 Schools Try It editor
TinyXML2 library documentation.
2 Constraints & logistics
2.1 Deadline
The deadline for project delivery is May 17, 2024, until 23:59.

Near the deadline, a form will be made available in Moodle for project delivery. You will need to deliver a ZIP file named delivery.zip, containing files README.md, SVGElements.hpp, SVGElements.cpp, and readSVG.cpp. To generate the ZIP file run make delivery.zip in the project folder.

$ make delivery.zip
rm -f delivery.zip
zip -9r delivery.zip README.md SVGElements.hpp SVGElements.cpp readSVG.cpp
  adding: README.md (deflated 39%)
  adding: SVGElements.hpp (deflated 78%)
  adding: SVGElements.cpp (deflated 78%)
  adding: readSVG.cpp (deflated 78%)
2.2 Group work
Groups must be formed by 3 students of the same practical class. You must use the Moodle group selection pages to form groups.

An exception is made for working students (“trabalhadores estudantes”) or students without a practical class. These students may work alone if they prefer.

All the group members must collaborate for the development of the project.

2.3 Evaluation criteria
Your code must compile with the given Makefile and be correct taking into account the requirements detailed in this document.
Use the provided test program to validate your implementation.
In addition to functional aspects, the code must not have memory usage problems, for example in terms of buffer overflows, dangling references, or memory leaks.
Your code must be well structured and as simple as possible, in particular the class hierarchy corresponding to SVG elements.

Your code should be clearly indented and include comments. Comments should be used to describe the flow of SVG reading in readSVG.cpp. Additionally, Doxygen-style comments should provide simple descriptions of each class function in SVGElements.hpp, e.g.:

//! Describe what the function does.
//! @param p_1 Description of parameter 1
//! @param p_2 Description of parameter 2
//! ...
//! @param p_n Description of parameter n
//! @return Describe what the function returns (if it is not void or a constructor).
return_type some_function(type_1 p1, type_2 p_2, ... , type_n p_n)
2.4 Plagiarism
Your code will be analyzed for plagiarism. Remember that this is a group project, not a “group-of-groups” project. Inter-group discussions are healthy, code sharing is not.

Plagiarism will result in the annulment of the project for involved groups and other possible disciplinary measures.

If you use code repositories (e.g. on GitHub), make sure your repository for the project is private to avoid unintended dissemination of your work.

All group elements must be able to explain all the code submitted by their group. Code that the group members are not able to explain will be treated as plagiarism.

3 Code project
3.1 Getting started
Download the ZIP archive available at Moodle. Unzip the archive, then run make to verify that compilation runs without errors.

$ unzip project.zip
...
$ cd project
$ make
g++ -std=c++11  -pedantic -Wall -Wuninitialized -Werror -g -fsanitize=address -fsanitize=undefined -c -o svgtopng.o svgtopng.cpp
g++ -std=c++11  -pedantic -Wall -Wuninitialized -Werror -g -fsanitize=address -fsanitize=undefined -c -o Color.o Color.cpp
g++ -std=c++11  -pedantic -Wall 
...
g++ -std=c++11  -pedantic -Wall -Wuninitialized -Werror -g -fsanitize=address -fsanitize=undefined -o xmldump xmldump.o libproj.a
Three programs are generated:

svgtopng: SVG to PNG conversion program;
test: for validating your code using automated tests; and
xmldump: example illustrating the use of the TinyXML2 library.
If you wish to recompile everything from scratch, execute make clean all.

$ make clean all
3.2 Project files
The project files and directories are divided in two sets: those that you should change (Table 1 below), and others that must not be changed (Table 2).

Table 1. Files/directories that can be changed.
File(s)/directory	Description
SVGElements.hpp
SVGElements.cpp	Header and implementation files for svg::SVGElement and its derived classes.
readSVG.cpp	Implementation file for svg::readSVG function.
README.md	Identifies group members and provides a summary of the work.
output directory	Initially empty, output PNG images will be placed here.
Table 2. Files/directories that must not be changed/removed.
Files/directory	Description
input directory	Directory containing SVG images used as input for PNG conversion.
expected directory	Directory containing PNG files that correspond to the expected outputs of SVG translation.
Makefile	Makefile to use for compilation.
test.cpp
svgtopng.cpp
xmldump.cpp	Source code of programs (they have a main function).
convert.cpp	Implementation of svg::convert function.
Color.hpp
Color.cpp	Header and implementation file for the Color type.
Point.hpp
Point.cpp
Header and implementation file for the Point type.
PNGImage.hpp
PNGImage.cpp
Header and implementation file for PNGImage class.
external/stb directory	stb source code necessary for PNG support.
external/tinyxm2 directory	TinyXML2 source code necessary for XML support.
3.3 Programs
3.3.1 The svgtopng program
The convert program can be invoked to process one SVG files and convert it to PNG e.g.,

$ ./svgtopng x.svg x.png
Performing conversion ... x.svg --> x.png
Done
3.3.2 The test program
The test program can be invoked to execute one or more automated tests. It will output a report of passed and failed tests, and also generate a test_log.txt file containing information regarding test failures.

Run test x to test PNG conversion for all SVG images in the input directory that have the prefix x. The x prefix may refer to an element name (e.g., ellipse) or transformation type (e.g., translate).

$ ./test ellipse
== 2 tests to execute  ==
[1] ellipse_1: pass
[2] ellipse_2: pass
== TEST EXECUTION SUMMARY ==
Total tests: 2
Passed tests: 2
Failed tests: 0
See test_log.txt for details.
You can also run test with no arguments to execute all tests:

$ ./test
In all cases, the program will produce a test_log.txt file containing detailed test failure information.

3.3.3 The xmldump program
The xmldump program can be invoked to print the structure of an XML file. Reading the source code may be helpful to understand how the TinyXML2 library works.

$ ./xmldump input/group_3.svg
svg --> [ width="530" height="530" xmlns="http://www.w3.org/2000/svg" ] 
  g --> [ transform="translate(10 10)" ] 
    circle --> [ cx="250" cy="250" r="250" fill="red" ] 
    circle --> [ cx="250" cy="250" r="200" fill="white" ] 
    circle --> [ cx="250" cy="250" r="150" fill="red" ] 
    circle --> [ cx="250" cy="250" r="100" fill="blue" ] 
    polygon --> [ fill="white" points="250,150 280,209 346,219 298,265 309,330 250,300 192,330 203,265 155,219 221,209" ]
4 Tasks
The project considers a small subset of the SVG standard, and in some cases only approximately with a few deviations to the SVG standard. A summary is now provided of the relevant SVG features and the associated tasks.

4.1 The <svg> root element
SVG images are expressed in XML by a <svg> root element illustrated in Listing 2. The width and height attributes express integer values for the image width and height respectively. As in other image formats (e.g., also PNG), the established convention is that the upper-left corner has coordinates (0,0) and the lower-right corner has coordinates (width-1, height-1). This type of coordinate system is illustrated in Figure 2 below.

<svg width="..." height="..." ... >
... 
</svg>
Listing 2. The <svg> root node in SVG files.

Figure 2. XY coordinate system for an image.
Figure 2. XY coordinate system for an image.
Note: In the project examples, SVG elements also contain the xmlns attribute. This has no impact on the geometric definition of elements, but it is required for viewing SVG files in browsers such as Chrome or Firefox.

SVG reading logic in readSVG.cpp

The SVG-to-PNG conversion function is given in convert.cpp. As indicated previously, this file should not be changed. Instead, you need to add the SVG reading logic in the readSVG function implemented in file readSVG.cpp. The convert function calls readSVG to obtain the image dimensions (width and height) and a vector of SVGElement* pointers to dynamically allocated instances of SVGElement.

The initial version of readSVG() illustrates how the width and height arguments are parsed in the top-level <svg> node in a SVG file. You need to add code to traverse the XML child nodes (see xmldump.cpp for an example of how to do it) and parse the SVG elements that are defined. Per each child node, an object should be dynamically allocated using new for the corresponding type of SVGElement, and be stored in the elements vector.

Note: To read colors you may use the Color parse(std::string) function (see Color.hpp/Color.cpp).

4.2 Geometrical elements to consider
SVG can express standard geometrical elements, some of which are considered in the project, and detailed next. In addition to these elements, the project also considers <g> and <use> elements discussed later in this document.

The subset of SVG geometrical elements and corresponding (subset of) attributes to consider for each element are as follows:

<ellipse> - an ellipse defined by:
cx and cy: XY coordinates for the ellipse’s center point;
rx and ry: ellipse radiuses in the X and Y axes;
fill: fill color to use;
<circle> - a circle defined by:
cx and cy: XY coordinates for the circle’s center point;
r: radius;
fill: fill color;
<polyline> - a sequence of connected lines defined by:
points: a comma-separated sequence of XY coordinates;
stroke: line color;
<line> - a line segment defined by:
x1 and y1 : XY coordinates of the start point;
x2 and y2 : XY coordinates of the end point;
stroke: line color;
<polygon> - a polygon defined:
points: a comma-separated sequence of XY coordinates;
fill: fill color;
<rect> - a rectangle defined by:
x and y: XY coordinates of the upper left corner of the rectangle;
width and height: width and height of the rectangle;
fill: fill color;
Additionally, each of the elements can optionally have the following attributes explained below:

an id attribute in support of elements duplication through <use> (see below);
transform and transform-origin attributes, to support transformations (discussed in this document below).
Tasks

For each geometrical element e you need to provide the SVG reading logic in readSVG.cpp and define a corresponding class in SVGElements.hpp / SVGElements.cpp. The class:

must be a derived class of SVGElement or of another class you have defined, and implement abstract operation draw appropriately;
should have a constructor in line with the arguments previously listed previously for each element type;
implement draw() using the available operations in PNGImage should be used to render the element in PNG format.
you should reflect geometrical element relationships in the class hierarchy - note that a <circle> element can be seen particular type of <ellipse>, <line> as a particular type of <polyline>, and <rect> a particular type of <polygon>.
An initial version (you may change it) of Ellipse class is provided to illustrate the above points. For the PNG conversion to work however with <ellipse> elements, you also need to add SVG reading code in the readSVG() function.

4.3 Element transformations
SVG elements can be transformed with one or more operations specified through the transform attribute. Some of these operations are affected by the transformation origin set through transform-origin. An example is given in Listing 3, and corresponding image in Figure 3. As shown in the example, only 3 transformation operations are considered. These are translate, rotate, and scale. Their meaning is as follows:

translate(x y) translates an element by x and y units in the X and Y axes respectively;
rotate(v) rotates an element with angle v, (clockwise for a positive value and anti-clockwise for a negative value) in relation to the rotation origin, where the rotation origin is set by the value of the transform-origin attribute or (0,0) if that attribute is absent;
scale(v) scales an element by a factor v in relation to a scaling origin, where the scaling origin is set by the value of the transform-origin attribute or (0,0) if that attribute is absent. In the project we consider only values for v that are integer and greater or equal than 1.
<svg width="180" height="260"  xmlns="http://www.w3.org/2000/svg">
  <polygon points="0,0 0,50 50,50" fill="red"/>
  <polygon points="0,0 0,50 50,50" fill="blue"
   transform="translate(75 0)"/>
  <polygon points="0,75 0,125 50,125" fill="red"/>
  <polygon points="75,75 75,125 125,125" fill="blue"
    transform-origin="100 100" transform="rotate(180)"/>
  <polygon points="0,150 0,200 50,200" fill="red"/>
  <polygon points="75,150 75,200 125,200" fill="blue"
    transform-origin="75 150" transform="scale(2)" />
</svg>
Listing 3. Transformation examples.

Figure 3. Transformation examples.
Figure 3. Transformation examples.
Deviations to the SVG standard

Adherence to the SVG standard is not strict. The following deviations are considered in the project:

For polyline and line the scale transformation is supposed to scale the thickness of drawn lines (stroke-width). We will ignore this requirement. Instead, all lines will be drawn in PNG format with a thickness of 1 pixel.

For ellipse the rotate transformation applies geometrically to all points of an ellipse points, possibly changing the orientation of the ellipse. For simplicity, we consider only rotating the ellipse’s center in relation to the rotation origin.

Suggestions

Use the base functions defined for the Point type, allowing the coordinates point to be translated, or scaled/rotated in relation to an origin.

It may be also helpful to define abstract operations (virtual pure functions) in SVGElement corresponding to each transformation. This may let you parse and apply transformations with a common logic for all elements, and then delegate the element transformations on the SVGElement abstract operations.

Additional examples

Additional examples of scale and rotate without transform_origin set are given in Listings/Figures 4 and 5 respectively. When the transform-origin is not set, its default value is (0,0) (the top-left corner of the image).

<svg width="210" height="210"  xmlns="http://www.w3.org/2000/svg">
  <polygon points="25,25 50,25 50,50" fill="red"/>
  <polygon points="25,25 50,25 50,50" fill="blue" transform="scale(2)"/>
  <polygon points="25,25 50,25 50,50" fill="green" transform="scale(4)"/>
</svg>
Listing 4. scale without transform-origin.

Figure 4. scale without transform-origin.
Figure 4. scale without transform-origin.
<svg width="300" height="300"  xmlns="http://www.w3.org/2000/svg">
  <rect x="50" y="50" width="200" height="200" transform="rotate(10)" fill="blue"/>
  <rect x="50" y="50" width="200" height="200" transform="rotate(-10)" fill="green"/>
  <rect x="50" y="50" width="200" height="200" fill="red"/>
</svg>
Listing 5. rotate without transform-origin.

Figure 5. rotate without transform-origin.
Figure 5. rotate without transform-origin.
4.4 Groups (<g> elements)
A <g> element represents a group of other elements, expressed by the XML child nodes. Groups may have the following attributes:

transform: expresses transformations that should be applied to all group elements;
transform-origin: sets the transformation origin for transformations expressed by transform;
id: identifier (can be referred to by <use> elements described below).
An example is given in Listing/Figure 6.

<svg width="300" height="300" xmlns="http://www.w3.org/2000/svg">
  <g transform="rotate(10)">
    <rect x="50" y="50" width="50" height="25" transform="scale(2)" fill="blue"/>
    <rect x="50" y="50" width="50" height="25" transform="scale(3)" fill="green"/>
    <rect x="50" y="50" width="50" height="25" fill="red"/>
    <rect x="50" y="50" width="50" height="25" transform="translate(25 25)" fill="red"/>
  </g>
</svg>
Listing 6. Example of a <g> element.

Figure 6. Example of a <g> element.
Figure 6. Example of a <g> element.
Task

You should define a subclass of SVGElement to represent groups, such that the internal state of a group object stores the elements in the group. Element operations over the group, e.g. draw() or others that you define, should be recursively applied to all group elements. Note however that contained elements can be of any kind, even other sub-groups, therefore you should refer to group elements through the SVGElement* type (pointers to SVGElement). Be careful also regarding the correct use of dynamic memory.

4.5 Element duplication (<use> elements)
A <use> element represents the duplication of an element, optionally affected by independent transformations. The attributes to consider are:

href is mandatory and has a value of the form #identifier (note the use of # as a prefix), where identifier should refer to a previously defined element with that identifier through the id attribute;

transform and transform-origin, if defined, defines transformations that should be applied to the copy of the original element (but not the original element); and

id may define an identifier for the element itself, as it may be also subsequently duplicated.

An example is given in Listing/Figure 7.

<svg width="120" height="200" xmlns="http://www.w3.org/2000/svg">
  <circle id="c1" cx="40" cy="40" r="25" fill="red"/>
  <circle id="c2" cx="40" cy="40" r="25" fill="blue" transform="translate(50 0)"/>
  <!-- Copies of c1 and c2, translated- -->
  <use href="#c1" transform="translate(50 60)"/>
  <use id="c3" href="#c2" transform="translate(-50 60)"/>
  <!-- Copy of c3, translated -->
  <use href="#c3" transform="translate(50 60)"/>
</svg>
Listing 7. Example of <use> elements.

.

Figure 7. Example of <use> elements.
Figure 7. Example of <use> elements.
Suggestions

In the SVG reading logic (readSVG.cpp), you will need to maintain a record for the association between identifiers and elements. An abstract operation for element duplication/“cloning” in the SVGElement class may be helpful too!

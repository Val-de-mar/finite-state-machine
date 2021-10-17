# finite-state-machine
edges regexes must be written in polish notation with * - prefix kleene star, . - prefix concatination, + - prefix union
example +.\*abc = (a\*)b + c; .\*+.aa.bb\*..+.ab.ba\*+.aa.bb.+.ab.ba\*+.aa.bb =(aa+bb)\*((ab+ba)(aa+bb)\*(ab+ba)(aa+bb)\*)\*

task 17: executable file longestSuffixPolish
    enter regex then line, program will print longest suffix length, then longest prefix length 

coverage files appears in directory "coverage" after buld by
$mkdir build
$cd build
$cmake ..
$make


# finite-state-machine
all regexes must be written in polish notation with * - prefix kleene star, . - prefix concatination, + - prefix union
example +.\*abc = (a\*)b + c; .\*+.aa.bb\*..+.ab.ba\*+.aa.bb.+.ab.ba\*+.aa.bb =(aa+bb)\*((ab+ba)(aa+bb)\*(ab+ba)(aa+bb)\*)\*

coverage files appears in directory "coverage" after buld by
$mkdir build
$cd build
$cmake ..
$make


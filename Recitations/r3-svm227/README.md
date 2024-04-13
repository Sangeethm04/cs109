[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/n3X8XMgb)
# r3

You are given the same starter code as for P1, with one exception. There is now an fprintf statement in the portion of main that is to print out the addition of two FP numbers passed in hex form. You'll want to comment out the fprintf statement after the call to genHex function so you can match the expected output.

Your job is to generate code to pass the following tests, which are in the grade.sh file.

    add2float   # no arguments passed, should result in return code (rc) of 99
    add2floats -r 1.0 1.0   # should result in rc of 97
    add2floats -x 3f800000 BF80000z   # should result in rc of 98
    add2floats -X 3f800000 BF800000   # should result in rc of 0 and output of
                                      # 1.000000e+00 + -1.000000e+00 = 0.000000e+00

To get a score of 100, you cannot have any compilation errors (of course!) or warnings.

Take a look at grade.sh for details. To run grade.sh, simply enter "grade.sh". This is automatically run each time you push, and you can see your score by navigating to the Actions tab in GitHub.

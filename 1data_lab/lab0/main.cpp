#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <time.h>
#include "SparseMatrix.h"

const int num_case = 3;
std::string grade_cases[num_case];

void compare_res(std::string test_case) {
    std::ifstream stu, ans;
    std::stringstream errstring;
    std::string s_stu, s_ans;
    int lineno = 0;

    std::string name = "output/" + test_case + ".yourans";
//    std::string name = "F:\\SJTU\\CLion project\\1data_lab\\lab0\\output\\" + test_case + ".yourans";
    stu.open(name, std::ios::in);
    if (!stu.is_open()) {
        throw std::runtime_error("Failed to open file: " + name);
    }

    name = "output/" + test_case + ".ans";
//    name = "F:\\SJTU\\CLion project\\1data_lab\\lab0\\output\\" + test_case + ".ans";
    ans.open(name, std::ios::in);
    if (!ans.is_open()) {
        throw std::runtime_error("Failed to open file: " + name);
    }

    while (getline(stu, s_stu) && getline(ans, s_ans)) {
        lineno++;
        if (s_stu != s_ans) {
            errstring << "line " << lineno << " mismatch: " << s_stu << "(stu) vs. "
                      << s_ans << "(ans)" << std::endl;
            throw std::runtime_error(errstring.str());
        }
    }

    stu.close();
    ans.close();
}

void grade_test(std::string test_case) {
    SparseMatrix left = SparseMatrix("input/" + test_case + ".left");
//    SparseMatrix left = SparseMatrix("F:\\SJTU\\CLion project\\1data_lab\\lab0\\input\\" + test_case + ".left");
    SparseMatrix right = SparseMatrix("input/" + test_case + ".right");
//    SparseMatrix right = SparseMatrix("F:\\SJTU\\CLion project\\1data_lab\\lab0\\input\\" + test_case + ".right");

    SparseMatrix ans = left * right;
    ans.to_file("output/" + test_case + ".yourans");
//    ans.to_file("F:\\SJTU\\CLion project\\1data_lab\\lab0\\output\\" + test_case + ".yourans");

    try {
        compare_res(test_case);
    } catch (std::exception &e) {
        throw std::runtime_error("Failed to pass " + test_case + ":\n\t" +
                                 e.what());
    }
}


class Matrix{
    int col,row;
    int **matrix;
public:
    Matrix(int k,int m){
        row = k;
        col = m;
        matrix = new int*[row];
        for (int i = 0; i < row; ++i)
            matrix[i] = new int[col];
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j)
                matrix[i][j] = 0;
    }
    Matrix(const std::string input_file) {
        /* TODO: Your code here. */
        std::ifstream file;
        file.open(input_file, std::ios::in);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + input_file);
        }

        file >> row; file >> col;
        int _row, _col, val;
        if(file.peek() == EOF)
            return;

        matrix = new int*[row];
        for (int i = 0; i < row; ++i)
            matrix[i] = new int[col];
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j)
                matrix[i][j] = 0;

        while(file.peek() != EOF) {
            file >> _row >> _col >> val;
            matrix[_row][_col] = val;
        }

    }
    ~Matrix(){
        for (int i = 0; i < row; ++i)
            delete []matrix[i];
        delete matrix;
    }

    void to_file(const std::string name) {
        /* TODO: Your code here. */
        std::ofstream output(name, std::ios::out);
        std::stringstream errstring, ss;

        if (!output) {
            throw std::runtime_error("Failed to open file: " + name);
        }
        output.clear();

        output << row <<" "<< col << endl;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (matrix[i][j])
                    output << i << j << matrix[i][j]<<endl;
            }
        }

    }

    Matrix operator*(const Matrix &right) {
        /* TODO: Your code here. */
        Matrix ans(row,right.col);

        for (int i = 0; i < row; ++i)
            for (int j = 0; j < right.col; ++j)
                for (int k = 0; k < col; ++k)
                    ans.matrix[i][j] += matrix[i][k] * right.matrix[k][j];

        return ans;
    }

};
int main(int argc, char *argv[]) {
//    for (int i = 0; i < num_case; i++) {
//        grade_cases[i] = "test" + std::to_string(i + 1);
//    }
//
//    try {
//        if (argc == 2) {
//            grade_test(argv[1]);
//        } else if (argc == 1) {
//            for (auto test_case : grade_cases) {
//                grade_test(test_case);
//            }
//        } else {
//            throw std::runtime_error("[usage]: ./sparsematrix [test_case_name]");
//        }
//    } catch (std::exception &e) {
//        std::cerr << e.what() << std::endl;
//        return 1;
//    }
//
//    std::cout << "Congratulations! You've passed all test(s)." << std::endl;
    clock_t start, finish;
    std::string test_case = "test11";

    start = clock();
    SparseMatrix left = SparseMatrix("F:\\SJTU\\CLion project\\1data_lab\\lab0\\input\\" + test_case + ".left");
    SparseMatrix right = SparseMatrix("F:\\SJTU\\CLion project\\1data_lab\\lab0\\input\\" + test_case + ".right");

    SparseMatrix ans = left * right;
    ans.to_file("F:\\SJTU\\CLion project\\1data_lab\\lab0\\output\\" + test_case + ".yourans");
    finish = clock();
    std::cout << "SparseMatrix:: cost of time is "<<(double)(finish-start)/CLOCKS_PER_SEC<<endl;


    start = clock();
    Matrix left1("F:\\SJTU\\CLion project\\1data_lab\\lab0\\input\\" + test_case + ".left");
    Matrix right1("F:\\SJTU\\CLion project\\1data_lab\\lab0\\input\\" + test_case + ".right");

    Matrix ans1 = left1 * right1;
    ans1.to_file("F:\\SJTU\\CLion project\\1data_lab\\lab0\\output\\" + test_case + ".yourans1");
    finish = clock();
    std::cout << "OrdinaryMatrix:: cost of time is "<<(double)(finish-start)/CLOCKS_PER_SEC<<endl;

    return 0;
}


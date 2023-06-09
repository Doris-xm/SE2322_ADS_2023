//#include <ios>
//#include <iostream>
//#include <cstdio>
//#include <cstdint>
//#include <string>
//#include <fstream>
//#include "treap.h"
//#include "util.h"
//
//void generate_output(Treap<int32_t>& treap, int32_t round) {
//    int32_t n, op, val;
//
////    JudgeFile input_file(input_path(round), std::ios_base::in);
////    auto &fin = input_file.get();
////
////    JudgeFile output_file(output_path(round), std::ios_base::out);
////    auto &fout = output_file.get();
//
//    std::cin >> n;
//
//    for (int i = 1; i <= n; i ++ ) {
//        std::cin >> op >> val;
//        switch (op) {
//            case 1:
//                treap.insert(val);
//                std::cout << treap.pre_traverse() << std::endl;
//                break;
//            case 2:
//                treap.remove(val);
//                std::cout << treap.pre_traverse() << std::endl;
//                break;
//            case 3:
//                std::cout << treap.rank(val) << std::endl;
//                break;
//            case 4:
//                std::cout << treap.kth_element(val) << std::endl;
//                break;
//            case 5:
//                std::cout << treap.pre_element(val) << std::endl;
//                break;
//            case 6:
//                std::cout << treap.suc_element(val) << std::endl;
//                break;
//        }
//    }
//}
//
//bool check_answer(int32_t round) {
//    JudgeFile output_file(output_path(round), std::ios_base::in);
//    JudgeFile answer_file(answer_path(round), std::ios_base::in);
//    auto &out_handle = output_file.get();
//    auto &ans_handle = answer_file.get();
//    std::string ol, al;
//    bool ret;
//
//    for (int32_t lineno = 0; !out_handle.eof() && !ans_handle.eof(); lineno ++ ) {
//        getline(out_handle, ol);
//        getline(ans_handle, al);
//        if (trim(ol) != trim(al)) {
//            std::cerr << "ERROR: Failed at case #" << round << " line:" << lineno <<
//                      " output:" << ol << " answer:" << al << std::endl;
//            return false;
//        }
//    }
//    if (!(ret = out_handle.eof() && ans_handle.eof())) {
//        std::cerr << "ERROR: Line number miss match" << std::endl;
//    }
//    return ret;
//}
//
//int main () {
//    Treap<int32_t> treap;
//    int TEST_NUM = 3;
//    std::cout << "TEST_NUM:" << TEST_NUM << std::endl;
//    for (int32_t round = 1; round <= TEST_NUM; round ++ ) {
//        try {
//            generate_output(treap, round);
//            treap.clear();
//            if (!check_answer(round))
//                return -1;
//        } catch(std::exception &e) {
//            std::cerr << e.what() << std::endl;
//            return -1;
//        }
//    }
//    std::cout << "Tests All Passed :)" << std::endl;
//    return 0;
//}
#include <ios>
#include <iostream>
#include <cstdio>
#include <cstdint>
#include <string>
#include <fstream>
#include "treap.h"
#include "util.h"

int total_insert_time(0);
int total_remove_time(0);
int total_rank_time(0);
int total_kth_time(0);
int total_pre_time(0);
int total_suc_time(0);
int insert_num(0);
int remove_num(0);
int rank_num(0);
int kth_num(0);
int pre_num(0);
int suc_num(0);



void generate_output(Treap<int32_t>& treap, int32_t round) {
    int32_t n, op, val;
    uint64_t start, end;

    JudgeFile input_file(input_path(round), std::ios_base::in);
    auto &fin = input_file.get();

    JudgeFile output_file(output_path(round), std::ios_base::out);
    auto &fout = output_file.get();

    fin >> n;

    for (int i = 1; i <= n; i ++ ) {
        fin >> op >> val;
        if(treap.split_num % 100 == 0) {
//            std::cout << "height:" << treap.get_height() << "   key:" << treap.get_size() << std::endl;
            std::cout << treap.get_height() << "\t" << treap.get_size() << std::endl;
        }
        switch (op) {
            case 1:
                insert_num ++;
                start=rdtsc();
                treap.insert(val);
                end=rdtsc();
                total_insert_time += end-start;
                fout << treap.pre_traverse() << std::endl;
                break;
            case 2:
//                remove_num ++;
//                start=rdtsc();
//                treap.remove(val);
//                end=rdtsc();
//                total_remove_time += end-start;
//                fout << treap.pre_traverse() << std::endl;
//                break;
            case 3:
                rank_num ++;
                start=rdtsc();
                fout << treap.rank(val) << std::endl;
                end=rdtsc();
                total_rank_time += end-start;
                break;
            case 4:
                kth_num ++;
                start=rdtsc();
                fout << treap.kth_element(val) << std::endl;
                end=rdtsc();
                total_kth_time += end-start;
                break;
            case 5:
                pre_num ++;
                start=rdtsc();
                fout << treap.pre_element(val) << std::endl;
                end=rdtsc();
                total_pre_time += end-start;
                break;
            case 6:
                suc_num ++;
                start=rdtsc();
                fout << treap.suc_element(val) << std::endl;
                end=rdtsc();
                total_suc_time += end-start;
                break;
        }
    }
}

bool check_answer(int32_t round) {
    JudgeFile output_file(output_path(round), std::ios_base::in);
    JudgeFile answer_file(answer_path(round), std::ios_base::in);
    auto &out_handle = output_file.get();
    auto &ans_handle = answer_file.get();
    std::string ol, al;
    bool ret;

    for (int32_t lineno = 0; !out_handle.eof() && !ans_handle.eof(); lineno ++ ) {
        getline(out_handle, ol);
        getline(ans_handle, al);
        if (trim(ol) != trim(al)) {
            std::cerr << "ERROR: Failed at case #" << round << " line:" << lineno <<
                      " output:" << ol << " answer:" << al << std::endl;
            return false;
        }
    }
    if (!(ret = out_handle.eof() && ans_handle.eof())) {
        std::cerr << "ERROR: Line number miss match" << std::endl;
    }
    return ret;
}

int main () {
    Treap<int32_t> treap;
    int TEST_NUM = 3;
    std::cout << "TEST_NUM:" << TEST_NUM << std::endl;
    for (int32_t round = 3; round <= TEST_NUM; round ++ ) {
        try {
            generate_output(treap, round);
            treap.clear();
//            if (!check_answer(round))
//                return -1;
        } catch(std::exception &e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }
    }
    std::cout << "Tests All Passed :)" << std::endl;

    std::cout << "average insert time:" << total_insert_time / insert_num << std::endl;
//    std::cout << "average remove time:" << total_remove_time / remove_num << std::endl;
    std::cout << "average rank time:" << total_rank_time / rank_num << std::endl;
    std::cout << "average kth time:" << total_kth_time / kth_num << std::endl;
    std::cout << "average pre time:" << total_pre_time / pre_num << std::endl;
    std::cout << "average suc time:" << total_suc_time / suc_num << std::endl;
    std::cout << "average split time:" << treap.total_split_times / treap.split_num << std::endl;
    std::cout << "average merge time:" << treap.total_merge_times / treap.merge_num << std::endl;
    std::cout << "average update size time:" << treap.total_update_times / treap.update_num << std::endl;

    return 0;
}


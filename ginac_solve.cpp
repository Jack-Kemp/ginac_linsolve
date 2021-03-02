#include <iostream>
#include <fstream> 
#include <string>
#include <ginac/ginac.h>

using namespace GiNaC;

/*
 * 
 */
int main(int argc, char** argv) {
    std::ifstream file;
    lst to_invert_lst, rhs_lst;
    std::string to_invert_str, rhs_str;
    matrix to_invert, rhs, vars, sols;
    realsymbol V("V"), f("f"), X("X"), Y("Y"), J2("J2"), J("J"), Vy("Vy"),
      h1("h1"), h2("h2"),J1("J1"),K("K");
    symtab table;
    table["V"] = V; table["J2"] = J2; table["f"] = f; table["X"] = X; 
    table["Y"] = Y; table["J"] = J; table["Vy"] = Vy; table["J1"] = J1;
    table["h1"] = h1; table["h2"] = h2; table["K"] = K;
    
    parser reader (table);

    std::string iName = std::string(argv[1]);

    file.open(iName.c_str());
    if (file) {
        std::getline(file, to_invert_str);
        std::getline(file, rhs_str);
        file.close();
        //std:: cout << to_invert_str << rhs_str << std::endl;
        to_invert_lst = ex_to<lst>(reader(to_invert_str));
        rhs_lst = ex_to<lst>(reader(rhs_str));
        //std::cout << to_invert_lst << std::endl << rhs_lst << std::endl;
        to_invert = ex_to<matrix>(lst_to_matrix(to_invert_lst));
        rhs = ex_to<matrix>(lst_to_matrix(rhs_lst));
        //std::cout << to_invert << std::endl << rhs << std::endl;
        
        vars = ex_to<matrix>(symbolic_matrix(to_invert.cols(), 1, "F"));
        //std::cout << vars << std::endl;
        sols = to_invert.solve(vars, rhs, solve_algo::markowitz);
        std::cout << sols << std::endl;
    } else std::cout << "Could not open file: " << iName << std::endl;



    return 0;
}


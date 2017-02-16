#include "../arff/include/arff.h"
#include "../CmdParser/cmdparser.hpp"

#include <fstream>

struct Parser : cli::Parser
{
    Parser(int argc, char* argv[]) : 
        cli::Parser{ argc, argv }
    {
        this->set_required<std::string>("o", "out", "Output ARFF file's name");
        this->set_required<std::string>("i", "in", "Input text file's name");
    }

    std::string in() const 
    {
        return this->get<std::string>("i");
    }
    std::string out() const
    {
        return this->get<std::string>("o");
    }
};

struct Record
{
    double ax, ay, az, gx, gy, gz;
    double smva, smvg, sma30a, sma30g, angle;
};


int main(int argc, char* argv[])
{
    Parser p{ argc, argv };
    p.run_and_exit_if_error();

    std::ifstream fin{p.in()};
    std::ofstream fout{ p.out() };

    {
        using namespace arff;


        auto model =
            arff::define(
                numeric{ "ax" }, numeric{ "ay" }, numeric{ "az" },
                numeric{ "gx" }, numeric{ "gy" }, numeric{ "gz" },
                numeric{ "SMVAcc" }, 
                numeric{ "SMVGyro" },
                numeric{ "SMA30Acc" },
                numeric{ "SMA30Gyro" },
                numeric{ "Angle" });
        using ModelType = decltype(model);

        document<ModelType> doc{ "out.txt", model };
        doc.name = p.in();

        while (fin) {
            char c;
            Record r{};
            fin >> r.ax >> c >> r.ay >> c >> r.az >> c
                >> r.gx >> c >> r.gy >> c >> r.gz >> c
                >> r.smva >> c >> r.smvg >> c
                >> r.sma30a >> c >> r.sma30g >> c
                >> r.angle;
            auto d = model.make(
                r.ax, r.ay, r.az, r.gx, r.gy, r.gz,
                r.smva, r.smvg, r.sma30a, r.sma30g,
                r.angle);
            doc.data.push_back(d);
        }

        fout << doc << std::endl;
    }

    return EXIT_SUCCESS;
}
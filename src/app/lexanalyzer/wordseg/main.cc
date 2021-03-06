#include <iostream>
#include <cstring>  // strcmp
#include "utils/logging.h"
#include "app/lexanalyzer/wordseg/opt.h"
#include "app/lexanalyzer/wordseg/opt_utils.h"
#include "app/lexanalyzer/wordseg/pipe.h"

#define APP "transition-based Chinese word segmentor"
#define EXE "wordseg"

namespace po = boost::program_options;
namespace cws = ZuoPar::LexicalAnalyzer::ChineseWordSegmentor;
namespace fe = ZuoPar::FrontEnd;

int multi_learn(int argc, char** argv) {
  std::cerr << "Not implemented." << std::endl;
  return 1;
}

int learn(int argc, char** argv) {
  std::string usage = "Training component of ZuoPar::" APP ".\n";
  usage += "usage: " EXE " learn [options]\n";
  usage += "options";

  po::options_description optparser = fe::build_learn_optparser(usage);

  if (argc == 1) {
    std::cerr << optparser << std::endl;
    return 1;
  }

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, optparser), vm);

  fe::LearnOption opts;
  if (!parse_learn_option(vm, opts)) {
    std::cerr << optparser << std::endl;
    return 1;
  }

  cws::Pipe pipe(opts);
  pipe.run();
  return 0;
}

int test(int argc, char** argv) {
  std::string usage = "Testing component of ZuoPar::" APP ".\n";
  usage += "usage: " EXE " test [options]\n";
  usage += "options";

  po::options_description optparser = fe::build_test_optparser(usage);

  if (argc == 1) {
    std::cerr << optparser << std::endl;
    return 1;
  }

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, optparser), vm);

  fe::TestOption opts;
  if (!parse_test_option(vm, opts)) {
    std::cerr << optparser << std::endl;
    return 1;
  }
  cws::Pipe pipe(opts);
  pipe.run();

  return 0;
}

#include "frontend/template/main.h"
MAIN(APP, EXE)
